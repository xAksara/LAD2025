#!/bin/sh
expected=$(printf "%s" "hello" | md5sum | cut -d' ' -f1)
output=$(printf "MD5 \"hello\"\n" | ./rhasher)
if [ "$output" = "$expected" ]; then
    echo "md5 test passed"
    exit 0
else
    echo "md5 test failed: expected $expected, got $output"
    exit 1
fi
