#!/bin/bash
CURRENT_DATE=$(date +"%Y.%m.%d")
PROJECT_NAME="Samurai-${CURRENT_DATE}"

cmake -S . -B build -DCMAKE_INSTALL_PREFIX="$PROJECT_NAME"
cmake --build build --config Release
cmake --install build --config Release
mkdir -p "$PROJECT_NAME"/Client
cp -r Client/assets "$PROJECT_NAME"/Client
tar -czvf "$PROJECT_NAME".tar.gz "$PROJECT_NAME"
