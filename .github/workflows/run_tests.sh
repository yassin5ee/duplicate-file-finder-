#!/bin/bash

# Compile the C code
gcc -o my_program main.c
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Directory for test cases
TEST_DIR="test_cases"
PASSED=0
FAILED=0

# Loop through each input/output pair
for INPUT_FILE in "$TEST_DIR"/input*.txt; do
    BASE_NAME=$(basename "$INPUT_FILE" .txt)
    EXPECTED_FILE="$TEST_DIR/${BASE_NAME/output/input}.txt"

    # Run the program with the input file
    ./my_program < "$INPUT_FILE" > temp_output.txt

    # Compare the output
    if diff -q temp_output.txt "$EXPECTED_FILE" > /dev/null; then
        echo "Test $BASE_NAME: PASSED"
        ((PASSED++))
    else
        echo "Test $BASE_NAME: FAILED"
        ((FAILED++))
    fi
done

# Clean up temporary files
rm -f temp_output.txt

# Summary
echo "Passed: $PASSED"
echo "Failed: $FAILED"
exit $FAILED
