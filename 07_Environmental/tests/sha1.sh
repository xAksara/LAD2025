#!/bin/sh
expected=$(printf "%s" "world" | sha1sum | cut -d' ' -f1)
output=$(printf "SHA1 \"world\"\n" | ./rhasher)
if [ "$output" = "$expected" ]; then
    echo "sha1 test passed"
    exit 0
else
    echo "sha1 test failed: expected $expected, got $output"
    exit 1
fi
