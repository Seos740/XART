#define uint8_t __CHAR16_TYPE__
#define uint32_t __CHAR32_TYPE__

#include "malloc.c"  

// Kernel memory configuration
#define THREAD_MANAGER_MEMORY_SIZE (512 * 1024)  // 512KB of memory for thread manager
#define THREAD_MANAGER_START_PAGE 1024  // Start at page 1024
#define PAGE_SIZE 4096  // Each page is 4KB

// Global memory configuration
extern uint8_t kernel_memory[THREAD_MANAGER_MEMORY_SIZE];  // Kernel memory region
extern uint32_t thread_manager_offset;  // Offset within thread manager memory

// External declaration for process registration
extern int GLOBAL_REGISTER_PROC(long *proc_name, long *mem_start_addr, long *malloc_length_pages);

// Thread Control Block (TCB) structure
typedef struct thread {
    void (*entry)(void*);     // Function to run in the thread
    void* arg;                // Argument to pass to the function
    void* stack;              // Pointer to stack memory
    unsigned int stack_pages; // Number of pages for the stack
    unsigned int stack_start_page; // Start page for the stack
    unsigned short pid;       // Process ID for the thread
    struct thread* next;      // For the thread queue
    int state;                // 0 = ready, 1 = running
} thread_t;

unsigned short pid_counter = 1;  // Starting PID for the first thread (PID 1 is the kernel)

// Malloc function for thread manager's memory allocation
void* malloc(unsigned int *pages, unsigned short *page_size_bytes, unsigned int *start_page, unsigned short *pid) {
    unsigned int memory_needed = (*pages) * (*page_size_bytes);

    // Check if enough memory is available
    if (thread_manager_offset + memory_needed > THREAD_MANAGER_MEMORY_SIZE) {
        return 0;  // Not enough memory
    }

    // Allocate memory and update the start page
    void* allocated_mem = &kernel_memory[thread_manager_offset];
    *start_page = thread_manager_offset / *page_size_bytes;
    thread_manager_offset += memory_needed;

    return allocated_mem;
}

// Prepare the thread stack and initialize it for execution
void prepare_initial_stack(thread_t* t) {
    unsigned char* stack_top = (unsigned char*)t->stack + (t->stack_pages * PAGE_SIZE);

    // Simulate pushing the thread function and its argument onto the stack
    stack_top -= sizeof(void*);  // Space for return address (function)
    *((void**)stack_top) = (void*)t->entry;

    stack_top -= sizeof(void*);  // Space for argument
    *((void**)stack_top) = t->arg;

    t->stack = stack_top;  // Update stack pointer
}

// Create a new thread
thread_t* create_thread(void (*func)(void*), void* arg) {
    // Allocate memory for the thread's control block (TCB)
    unsigned int tcb_pages = 1;
    unsigned short page_size = PAGE_SIZE;
    unsigned int tcb_start_page = 0;
    thread_t* t = (thread_t*) malloc(&tcb_pages, &page_size, &tcb_start_page, &pid_counter);
    
    if (!t) return 0;  // Allocation failed

    // Allocate stack for the thread (2 pages should suffice)
    unsigned int stack_pages = 2;
    unsigned int stack_start_page = 0;
    void* stack = malloc(&stack_pages, &page_size, &stack_start_page, &pid_counter);
    
    if (!stack) return 0;  // Stack allocation failed

    // Initialize the thread's control block
    t->entry = func;
    t->arg = arg;
    t->stack = stack;
    t->stack_pages = stack_pages;
    t->stack_start_page = stack_start_page;
    t->pid = pid_counter++;
    t->next = 0;
    t->state = 0;  // Thread is initially ready

    // Register the thread with the kernel (this handles PID and memory registration)
    long proc_name = (long)t->pid;
    long mem_start_addr = (long)t->stack;
    long malloc_length_pages = stack_pages;
    int result = GLOBAL_REGISTER_PROC(&proc_name, &mem_start_addr, &malloc_length_pages);

    if (result != 0) {
        // If registration fails, return NULL
        return 0;
    }

    // Prepare the stack to call the thread function with the provided argument
    prepare_initial_stack(t);

    return t;
}

// Simulate a context switch to the thread (simplified)
void switch_to_thread(thread_t* t) {
    // Simulate changing the stack pointer to the thread's stack
    asm volatile (
        "mov %0, %%rsp\n"  // Set stack pointer to the thread's stack
        :
        : "r"(t->stack)
        : "%rsp"
    );
    t->state = 1;  // Mark the thread as running
    t->entry(t->arg);  // Call the thread's function
}

// A simple scheduler function to round-robin between threads
void simple_scheduler(thread_t* thread_list) {
    thread_t* current_thread = thread_list;
    while (current_thread) {
        if (current_thread->state == 0) {
            switch_to_thread(current_thread);  // Switch to the next ready thread
        }
        current_thread = current_thread->next;
    }
}

// A simple example thread function
void example_thread_func(void* arg) {
    // The thread does some work here (example: just an infinite loop)
    while (1);
}

// Main entry for the thread manager
int main() {
    // Create two example threads
    thread_t* thread1 = create_thread(example_thread_func, (void*)"Thread 1");
    thread_t* thread2 = create_thread(example_thread_func, (void*)"Thread 2");

    if (thread1 && thread2) {
        // Link the threads in a simple list for the scheduler
        thread1->next = thread2;

        // Start the scheduler
        simple_scheduler(thread1);
    }

    return 0;
}
