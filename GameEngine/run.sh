#!/bin/bash

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    if [ -w "$BUILD_DIR" ]; then
        rm -rf "$BUILD_DIR"
    else
        sudo rm -rf "$BUILD_DIR" || exit 1;
    fi
fi

mkdir "$BUILD_DIR"

cd "$BUILD_DIR"

cmake ..

make -j "$(nproc)"

./samurai_ecs

cd ..
