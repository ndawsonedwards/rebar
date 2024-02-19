#! /bin/bash

BUILD_DIR="build"

echo "cmake -B $BUILD_DIR -G "MinGW Makefiles" "
cmake -B $BUILD_DIR -G "MinGW Makefiles" 

echo "make"
(cd $BUILD_DIR && make)
