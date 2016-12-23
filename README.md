#extfs
**NOTE:** this library is in very early development

**extfs** is a simple implementation of the ext family (2/3/4) of file systems.

#Disclaimer
I take no responsibility for any damage done to your main file system or other
data.

#Requirements
  - [base] Probably some flavor of Linux (tested on **Arch**)
  - [build] A C++17 capable compiler (e.g modern **GCC** or **Clang**)
  - [build] **CMake** (tested on 3.6, should work down to 3.2)
  - [build] Some build tool supported by cmake (**GNU Autotools**, **Ninja**, etc.)
  - [build] **Conan**
  - [testing] **e2fsprogs**

#Building
```bash
$ git clone https://github.com/fmorgner/extfs.git
$ cd extfs/build
$ cmake ..
$ cmake --build . -- -j$(nproc)
```

##Build options
| Option                   | Default | Description                        |
| ------------------------ | ------- | ---------------------------------- |
| EXTFS_BUILD_STATIC       | On      | Build libextfs as a static library |
| EXTFS_ENABLE_RTTI        | On      | Enable runtime type information    |
| EXTFS_ENABLE_EXCEPTIONS  | On      | Enable C++ exceptions              |
