#!/bin/bash

if [ $EUID != 0 ]; then
    sudo "$0" "$@"
    exit $?
fi

if [ -d build  ]; then
    rm -rf build
fi

mkdir build
cd build
cmake ..
make -j $(nproc)
make package
cd ..
