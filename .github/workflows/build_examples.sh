#!/bin/bash

echo Building examples for $1

set -x
set -e

mkdir /examples
make 
make dist 
find -type f -name \"*.elf\" -exec cp {} /examples \; 
cd / 
tar -czf output/examples-$1.tar.gz examples
ls -la output
