#include "malloc.c"

#define MSR_EFER        0xC0000080
#define MSR_STAR        0xC0000081
#define MSR_LSTAR       0xC0000082
#define MSR_FMASK       0xC0000084

#define uint32_t __CHAR32_TYPE__
#define uint64_t LONG

extern void syscall_entry();
extern void syscall_handler();

// Write MSR (Model-Specific Register)
static inline void wrmsr(uint32_t msr, uint64_t value) {
    uint32_t lo = value & 0xFFFFFFFF;
    uint32_t hi = value >> 32;
    asm volatile ("wrmsr" :: "c"(msr), "a"(lo), "d"(hi));
}

void init_syscall() {
    wrmsr(MSR_EFER, 1);  // Enable syscall/sysret (SCE bit in EFER)
    
    // STAR: kernel CS = 0x08, user CS = 0x18
    uint64_t star = ((uint64_t)0x0018 << 48) | ((uint64_t)0x0008 << 32);
    wrmsr(MSR_STAR, star);

    // LSTAR: syscall entry point
    wrmsr(MSR_LSTAR, (uint64_t)syscall_entry);

    // FMASK: clear IF (bit 9)
    wrmsr(MSR_FMASK, (1 << 9));
}
