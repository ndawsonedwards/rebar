#! /bin/bash

BUILD_DIR="build"

echo "cmake -B $BUILD_DIR -G "Unix Makefiles" "
cmake -B $BUILD_DIR -G "Unix Makefiles" 

echo "make"
(cd $BUILD_DIR && make)
