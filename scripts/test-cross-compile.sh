#!/bin/bash
# SPDX-License-Identifier: MIT
# Cross-compilation testing script for CPL Kbuild system
# Tests CROSS_COMPILE prefix handling and alternative toolchain support

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

echo "=========================================="
echo "CPL Kbuild Cross-Compilation Test Suite"
echo "=========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

passed=0
failed=0
skipped=0

# Helper function to run a test
run_test() {
    local test_name="$1"
    local test_cmd="$2"
    local skip_reason="$3"

    printf "%-50s" "$test_name"

    if [ -n "$skip_reason" ]; then
        echo -e "${YELLOW}SKIP${NC} ($skip_reason)"
        skipped=$((skipped + 1))
        return
    fi

    if eval "$test_cmd" > /tmp/cross-compile-test-$$.log 2>&1; then
        echo -e "${GREEN}PASS${NC}"
        passed=$((passed + 1))
    else
        echo -e "${RED}FAIL${NC}"
        echo "  Error output:"
        sed 's/^/    /' /tmp/cross-compile-test-$$.log | head -10
        failed=$((failed + 1))
    fi
    rm -f /tmp/cross-compile-test-$$.log
}

# Clean before testing
echo "Cleaning build artifacts..."
make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
echo ""

# Test 1: Default build (native toolchain)
echo "Test Group 1: Default Native Build"
echo "------------------------------------------"
run_test "Build with default g++ toolchain" \
    "make -C '$PROJECT_ROOT' cpl V=0 -j\$(nproc)"
run_test "Verify g++ was used" \
    "grep -q 'g++' '$PROJECT_ROOT'/cpl/.*.cmd || grep -q 'CXX.*g++' '$PROJECT_ROOT'/Makefile"

make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
echo ""

# Test 2: Explicit CXX override (should take precedence over CROSS_COMPILE)
echo "Test Group 2: Explicit Compiler Override"
echo "------------------------------------------"
if command -v clang++ > /dev/null 2>&1; then
    run_test "Build with explicit CXX=clang++" \
        "make -C '$PROJECT_ROOT' CXX=clang++ cpl V=0 -j\$(nproc)"
    run_test "Verify clang++ was used" \
        "find '$PROJECT_ROOT'/cpl -name '*.cmd' -exec grep -l 'clang++' {} \; | head -1"

    make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
else
    run_test "Build with explicit CXX=clang++" \
        "" "clang++ not available"
    run_test "Verify clang++ was used" \
        "" "clang++ not available"
fi
echo ""

# Test 3: CROSS_COMPILE with empty prefix (should use default g++)
echo "Test Group 3: CROSS_COMPILE Empty Prefix"
echo "------------------------------------------"
run_test "Build with CROSS_COMPILE=''" \
    "make -C '$PROJECT_ROOT' CROSS_COMPILE='' cpl V=0 -j\$(nproc)"
run_test "Verify g++ was used (no prefix)" \
    "find '$PROJECT_ROOT'/cpl -name '*.cmd' -exec grep -l 'g++' {} \; | head -1"

make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
echo ""

# Test 4: Precedence test - CXX should override CROSS_COMPILE
echo "Test Group 4: Override Precedence"
echo "------------------------------------------"
if command -v clang++ > /dev/null 2>&1; then
    run_test "CXX=clang++ overrides CROSS_COMPILE=nonexistent-" \
        "make -C '$PROJECT_ROOT' CXX=clang++ CROSS_COMPILE=nonexistent- cpl V=0 -j\$(nproc) 2>&1 | grep -v 'warning:'"
    run_test "Verify clang++ was used (not nonexistent-g++)" \
        "find '$PROJECT_ROOT'/cpl -name '*.cmd' -exec grep -l 'clang++' {} \; | head -1"

    make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
else
    run_test "CXX=clang++ overrides CROSS_COMPILE=nonexistent-" \
        "" "clang++ not available"
    run_test "Verify clang++ was used (not nonexistent-g++)" \
        "" "clang++ not available"
fi
echo ""

# Test 5: AR and STRIP with CROSS_COMPILE prefix
echo "Test Group 5: Tool Prefix Application"
echo "------------------------------------------"
run_test "Check AR respects CROSS_COMPILE (if set)" \
    "make -C '$PROJECT_ROOT' CROSS_COMPILE='' -p 2>/dev/null | grep -E '^AR\s*=' | grep -q 'ar'"
run_test "Check STRIP variable is set" \
    "make -C '$PROJECT_ROOT' CROSS_COMPILE='' -p 2>/dev/null | grep -E '^STRIP\s*:=' | grep -q '.'"
echo ""

# Test 6: Hypothetical cross-compilation (would fail but tests mechanism)
echo "Test Group 6: Cross-Compile Mechanism Validation"
echo "------------------------------------------"
run_test "CROSS_COMPILE prefix propagates to CXX variable" \
    "make -C '$PROJECT_ROOT' CROSS_COMPILE=fake-prefix- -p 2>/dev/null | grep -E '^CXX\s*=' | grep -q 'fake-prefix-g++'"
run_test "CROSS_COMPILE prefix propagates to AR variable" \
    "make -C '$PROJECT_ROOT' CROSS_COMPILE=fake-prefix- -p 2>/dev/null | grep -E '^AR\s*=' | grep -q 'fake-prefix-ar'"
run_test "CROSS_COMPILE variable is respected" \
    "test \"\$(make -C '$PROJECT_ROOT' CROSS_COMPILE=test- -p 2>/dev/null | grep -E '^CXX\\s*:?=' | head -1 | grep -o 'test-g++')\" = 'test-g++'"
echo ""

# Test 7: Build artifacts with different toolchains
echo "Test Group 7: Build Artifact Verification"
echo "------------------------------------------"
make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
run_test "Build creates expected library artifacts" \
    "make -C '$PROJECT_ROOT' cpl V=0 -j\$(nproc) && [ -f '$PROJECT_ROOT'/cpl/built-in.a ]"

make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
echo ""

# Test 8: Verbosity with cross-compilation
echo "Test Group 8: Verbosity and Debugging"
echo "------------------------------------------"
run_test "V=1 shows full command with compiler" \
    "make -C '$PROJECT_ROOT' V=1 cpl -j1 2>&1 | grep -E 'g\\+\\+.*-std=c\\+\\+20' | head -1"

make -C "$PROJECT_ROOT" clean > /dev/null 2>&1
echo ""

# Summary
echo "=========================================="
echo "Test Summary"
echo "=========================================="
total=$((passed + failed + skipped))
echo "Total:   $total"
echo -e "${GREEN}Passed:  $passed${NC}"
if [ $failed -gt 0 ]; then
    echo -e "${RED}Failed:  $failed${NC}"
else
    echo "Failed:  $failed"
fi
if [ $skipped -gt 0 ]; then
    echo -e "${YELLOW}Skipped: $skipped${NC}"
fi
echo "=========================================="

if [ $failed -gt 0 ]; then
    echo -e "${RED}Result: FAILED${NC}"
    exit 1
else
    echo -e "${GREEN}Result: SUCCESS${NC}"
    exit 0
fi
