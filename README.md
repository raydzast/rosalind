## About
This repository contains solutions to bioinformatics problems from [rosalind.info](http://rosalind.info/) that was done as part of the academic practice in 4th semester.

## Build
The name of problem to build lies in file `CMakeFiles.txt`. That name is defined as compile-time constant `NAME` on line [#6](https://github.com/lipoponi/rosalind/blob/master/CMakeLists.txt#L6)

```shell-script
mkdir -p cmake-build && cd cmake-build
cmake -G "Unix Makefiles" .. && make
```

## Run
Before running it's required to put data into `inputs` folder. Input file for problem should be named as `%problem-name.txt%`.

```shell-script
mkdir -p outputs
./cmake-build/run
```
