#!/bin/bash

# === CONFIG ===
SOURCE="$1"                      # Input C file
BASENAME=$(basename "$SOURCE" .c)
OBJ="$BASENAME.o"
RAW="$BASENAME.bin"
OUTPUT="$BASENAME.xarto"

CODE_OFFSET=256  # 0x100
ARCH_ID=1        # XART Virtual Machine architecture

# === Step 1: Compile C to object file ===
echo "🔧 Compiling $SOURCE..."
gcc -nostdlib -ffreestanding -fno-stack-protector -fno-pic -o "$OBJ" -c "$SOURCE"
if [ $? -ne 0 ]; then
    echo "❌ Compilation failed."
    exit 1
fi

# === Step 2: Link the object file to create a raw binary ===
echo "📦 Creating raw binary from $OBJ..."
gcc -nostdlib -ffreestanding -fno-stack-protector -fno-pic -o "$RAW" "$OBJ"
if [ $? -ne 0 ]; then
    echo "❌ Linking failed."
    exit 1
fi

# === Step 3: Build XART-O file ===
echo "🧵 Weaving the XART-O executable: $OUTPUT..."

CODE_SIZE=$(stat -c %s "$RAW")
HEADER=$(mktemp)
SECT=$(mktemp)
PADDING_SIZE=$((CODE_OFFSET - 24 - 9))  # 24-byte header + 9-byte section table
PADDING=$(mktemp)

# Header layout: magic(5), ver(1), arch_id(2), reserved(2), code_off(4), data_off(4),
# entry_point(4), flags(4), section_count(4)
printf "XARTO" > "$HEADER"
printf "\x01" >> "$HEADER"                               # version
printf "\x01\x00" >> "$HEADER"                           # arch_id
printf "\x00\x00" >> "$HEADER"                           # reserved
printf "\x00\x01\x00\x00" >> "$HEADER"                   # code_offset (0x100)
printf "\x00\x00\x00\x00" >> "$HEADER"                   # data_offset
printf "\x00\x00\x00\x00" >> "$HEADER"                   # entry_point
printf "\x00\x00\x00\x00" >> "$HEADER"                   # flags
printf "\x01\x00\x00\x00" >> "$HEADER"                   # section_count

# Section: type(1), length(4), offset(4)
printf "\x01" > "$SECT"                                  # code section
printf "$(printf '%08x' $CODE_SIZE | sed 's/../\\x&/g' | tac -rs .)" >> "$SECT"
printf "$(printf '%08x' $CODE_OFFSET | sed 's/../\\x&/g' | tac -rs .)" >> "$SECT"

# Padding to align to CODE_OFFSET
dd if=/dev/zero of="$PADDING" bs=1 count="$PADDING_SIZE" 2>/dev/null

# === Assemble the final .xarto ===
cat "$HEADER" "$SECT" "$PADDING" "$RAW" > "$OUTPUT"
echo "✅ Done: $OUTPUT created."

# === Clean up ===
rm "$HEADER" "$SECT" "$PADDING" "$OBJ" "$RAW"

