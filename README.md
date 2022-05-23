# cut
Simple cpu usage tracker written in C for linux platforms.

## Setup
You need clang and make to build and run this program.
You can find clang under this link: https://clang.llvm.org/get_started.html
and make under this link: https://www.gnu.org/software/make/

To run this project locally, compile it using make then run compiled binary:
```
make
./main
````

To check program using valgrind (https://valgrind.org/) run this command:
```
make dev
````

To run all tests (they can take about 10 seconds because of simulating program usage):
```
make test
```
