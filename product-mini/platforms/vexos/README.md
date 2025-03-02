# VEXos WAMR

## Building

Here are the commands you need to run.
As long as you have `git`, `cmake`, `ninja`, `clang` and the ARM Embedded Toolchain installed, you should
be able to build this project.

```shell
brew install osx-cross/arm/arm-gcc-bin@14
mkdir build
cd build

# Mac:
# brew install osx-cross/arm/arm-gcc-bin@14
cmake .. -G Ninja -D GCC_ARM_TOOLCHAIN=/opt/homebrew/opt/arm-gcc-bin@14
# Windows:
# winget install --id=Arm.GnuArmEmbeddedToolchain -e
cmake .. -G Ninja -D "GCC_ARM_TOOLCHAIN=C:\\Program Files (x86)\\Arm GNU Toolchain arm-none-eabi\\13.3 rel1"
# Linux varies, usually `which arm-none-eabi-gcc` will help.

ninja
```

Then you can compile the AOT compiler:

```shell
cd wamr-compiler
python3 -m venv venv
source venv/bin/activate
python3 ../build-scripts/build_llvm.py --extra-cmake-flags=-DLLVM_CCACHE_BUILD=OFF
mkdir build
cd build
cmake .. -G Ninja
ninja
```