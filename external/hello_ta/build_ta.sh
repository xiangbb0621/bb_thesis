#!/bin/bash
# Build Hello World TA using OP-TEE TA dev kit

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
AOSP_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
OPTEE_OS="$AOSP_ROOT/optee_os"
# 使用 OP-TEE OS 編譯後產生的 TA dev kit路徑
TA_DEV_KIT="$OPTEE_OS/out/arm-plat-rockchip/export-ta_arm64"

# Check if TA dev kit exists
if [ ! -d "$TA_DEV_KIT" ]; then
    echo "Error: TA dev kit not found at $TA_DEV_KIT"
    echo "Please build OP-TEE OS first."
    exit 1
fi

# Cross compiler
CROSS_COMPILE="$AOSP_ROOT/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-"

echo "=== Building Hello World TA ==="
echo "TA Dev Kit: $TA_DEV_KIT"
echo ""

cd "$SCRIPT_DIR/ta"

# Clean previous build to avoid circular dependency issues
rm -rf out

# Build TA (use absolute path for O to avoid path conflicts)
make \
    CROSS_COMPILE="$CROSS_COMPILE" \
    TA_DEV_KIT_DIR="$TA_DEV_KIT" \
    O="$SCRIPT_DIR/ta/out" \
    -j$(nproc)

echo ""
echo "=== Build Complete ==="
echo "TA binary: $SCRIPT_DIR/ta/out/8aaaf200-2450-11e4-abe2-0002a5d5c51b.ta"
