#!/bin/bash

rm -fr build/
rm -fr qsz/
mkdir qsz
mkdir build && cd build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX:PATH=/home/bigyang/amg-compress/SZ3/qsz ..

# Use all available CPU cores for faster build
make -j$(nproc)

make install
