# Loli language

> The Loli programming language

## Building

Install ``CMake`` 3.6 or later and execute commands:

```bash
mkdir ./build               # make build directory
cmake -S ./ -B ./build      # genirate make file to build directiry
cd build && make            # compile loli
```

Then in the build folder you can find files: ``loli`` & ``libloli.so`` (``loli.exe`` & ``libloli.dll`` on windows)