# cut
Simple cpu usage tracker written in C for linux platforms.

## Setup
You need clang and cmake (at least 3.14) to build and run this program.
You can find clang under this link: https://clang.llvm.org/
and cmake under this link: https://cmake.org/

To run this project locally, create build directory then build project in this directory and run it:
```
mkdir build
cd build
cmake ..
cmake --build .
./cut
````

To check program using valgrind (https://valgrind.org/) run this command from build directory:
```
vlagrind --leak-check=full ./cut
````

To run all tests from build directory (they can take about 6 seconds because of simulating program usage):
```
ctest
```
