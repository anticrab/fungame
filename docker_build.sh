#!/bin/bash
set -e
mkdir -p build
cd build
rm -rf ./*
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake ..
make
