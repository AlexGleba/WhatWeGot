#!/bin/sh
current_directory="$(cd "$(dirname "$0")" && pwd)"
project_root_dir=$current_directory


echo "Hello Friend! Let's try and build this application together :D"


mkdir -p "${project_root_dir}/third_party"
cd "${project_root_dir}/third_party"
if [ ! -d "glew" ]; then
    git clone https://github.com/Perlmint/glew-cmake.git glew
    cd "${project_root_dir}/third_party/glew"
    cd build
    cmake -DCMAKE_INSTALL_PREFIX="${project_root_dir}/third_party/glew/install" -DCMAKE_INSTALL_LIBDIR=lib -DBUILD_SHARED_LIBS:BOOL=ON -DBUILD_UTILS:BOOL=ON ./cmake
    #rm -rf build install
    #mkdir -p build && mkdir -p install && cd build
    #cmake -DCMAKE_INSTALL_PREFIX=${project_root_dir}/third_party/glew/install -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build . -j 4 --config Debug
    cmake --build . --config Debug --target glew_s
    cmake --build . --config Debug --target INSTALL
    cmake --install . --config Debug
    cp -r lib/* ../install/lib
    cp -r lib/Debug/* ../install/lib
fi

cd "${project_root_dir}/third_party"
if [ ! -d "glfw" ]; then
    git clone https://github.com/glfw/glfw.git glfw
    cd "${project_root_dir}/third_party/glfw"
    rm -rf build install
    mkdir -p build && mkdir -p install && cd build
    cmake -DCMAKE_INSTALL_PREFIX="${project_root_dir}/third_party/glfw/install" -DCMAKE_INSTALL_LIBDIR=lib -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_WAYLAND:BOOL=OFF ..
    cmake --build . -j 4 --config Debug
    cmake --build . --config Debug --target INSTALL
    cmake --install . --config Debug
fi

# compile the rest of the application
cd "${project_root_dir}"

# remove the build directory that has the current code in it
echo "deleting the BUILD directory"
rm -rf "${project_root_dir}/build"
rm -rf "${project_root_dir}/install"

echo "make a new BUILD directory to start the compiling process"
mkdir -p "${project_root_dir}/build"
cd "${project_root_dir}/build"

echo "cmake engage!"
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

echo "convert this to an executable application -- let's go!!"
cmake --build . -j 4 --config Debug
cmake --install . --config Debug
cd "${project_root_dir}"
echo "declare success -- hooray!"

echo "running the executable with some default parameters"
echo "./build/main -c config.inp > results.txt 2>&1"
echo "  the 2>&1 redirects the stderr to a 1 so we don't see the gnuplot problems"
#mkdir -p ${project_root_dir}/results
#./build/main -c config.inp > results/results.txt 2>&1
#./build/main


