# Delete the build folder if it already exists
if [ -d "build" ]; then
    rm -r build
fi

# Create a new build directory and navigate into it
mkdir build && cd build

# Run cmake to generate build files
cmake ..

# Build the project using make with 4 parallel jobs
make -j4
