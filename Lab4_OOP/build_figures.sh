#!/bin/bash

echo "Building Figures Template Project..."

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

cmake ..
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    cd ..
    exit 1
fi

cmake --build .
if [ $? -ne 0 ]; then
    echo "Build failed!"
    cd ..
    exit 1
fi

echo "Build successful!"
echo ""
echo "To run the program:"
echo "  cd build"
echo "  ./figures_main"
echo ""
echo "To run tests:"
echo "  cd build"
echo "  ctest"
echo "  or"
echo "  ./figures_tests"

cd ..

