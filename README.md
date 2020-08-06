# MCMLSD-CPP
A CPP port of the MCMLSD line detection method by James H. Elder, Emilio J. Almazàn, Yiming Qian and Ron Tal.

Described in the pre-release article "MCMLSD: A Probabilistic Algorithm and Evaluation Framework for Line Segment Detection" (arxIv:2001.01788v1 [cs.CV] 6 Jan 2020)

## Makefile
A custom makefile is provided. It contains a `$CONFIGURATION` variable that changes the build type to either `Debug` (uses `-g` for easy debugging) or `Release` (uses `-O2` for best performance). It should be set as `Debug` on the `develop` branch and `Release` on the `master` branch.

To build the project, simply use the `make` command.

To clean the build , use the `make clean` command.

You can also get intermediates files by using the `make intermediates` command to have unlinked executable code and assembly code.

## Eigen
This implementation uses the Eigen library (version 3.3.7) for matrices and vectors.

Due to size constrain (over 300+ files), it is not included in this project. You will need to download it [here](https://gitlab.com/libeigen/eigen/-/releases), extract it, and copy the `Eigen` subfolder from the extracted `eigen-x.x.x` folder in the `lib` folder of this project.

You should end up with this hierarchy in the `lib` folder:
```
lib
 |-Eigen
 | |- All Eigen subfolders and files
 |
 |-Instrumentor.h
```

Evyerthing else should work out of the box.

NOTE: if you are using Visual Studio Code, you might need to add `"{workspaceFolder}/lib"` in your `IncludePath` variable to have a working code insight.

## OpenCV
This implementation uses OpenCV (version 2.4.9) to read an image and downscale it with a bilinear filter, exactly as in the original MATLAB implementation.

The recommended way to install OpenCV is by using your distribution's packet manager.

You might need to do some adjustments in the `main.cpp` and/or in the `makefile` files to use your OpenCV version.

## Cherno's Visual Benchmarking
This project uses Visual Benchmarking to benchmark the execution time of various functions.

To use it, turn `#define PROFILING` to `1` in the `Instrumentor.h` file in the `lib` folder.
This will create a `Profile.json` file in the main folder of the project once the program is run.

To open this file, you need either Google Chrome or Chromium, and open the `chrome://tracing/` page. Then, drag and drop the `Profile.json` file in the window.

More informations [here](https://www.youtube.com/watch?v=xlAH4dbMVnU&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=82).
