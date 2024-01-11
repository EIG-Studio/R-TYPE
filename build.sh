#!/bin/bash

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    if [ -w "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    else
        sudo rm -rf "$BUILD_DIR" || exit 1;
    fi
fi

conan install . --output-folder=build --build=missing

mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"

cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=/build/Release/generators/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release

make -j "$(nproc)"

sudo make package
