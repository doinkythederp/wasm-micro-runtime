# VEXos WAMR

## Building

Here's what it was like on macOS. As long as you have `git`, `cmake`, `ninja`, `clang` and the ARM Embedded Toolchain installed, you should
be able to build this project.

```shell
brew install osx-cross/arm/arm-gcc-bin@14
mkdir build
cd build
cmake .. -DGCC_ARM_TOOLCHAIN=/opt/homebrew/opt/arm-gcc-bin@14
make
```

Then you can compile the AOT compiler:

```shell
cd wamr-compiler
python3 -m venv venv
source venv/bin/activate
python3 ../build-scripts/build_llvm.py --extra-cmake-flags=-DLLVM_CCACHE_BUILD=OFF
mkdir build
cd build
cmake ..
make
```