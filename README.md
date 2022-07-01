[![License][license-image]][license-url]

# FileReceivingServer
A UDP server that can receive data, write it to RAM and calculate a checksum from it

## Build project
`cmake -B build -DCMAKE_BUILD_TYPE=Debug -DFIND_TESTS=ON -DENABLE_TIDY=ON`

`cmake --build build/ -j4`

## Run tests
`cd build`

`ctest`

## Related project
[Cmake scripts for build c++ projects](https://github.com/nicledomaS/cmake/blob/master/README.md)

[license-image]: https://img.shields.io/badge/License-Apache%202.0-blue.svg
[license-url]: LICENSE
