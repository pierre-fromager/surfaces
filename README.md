# Polyregress

Polyregress is a c99 portage from initial [python polyregress solver](https://arachnoid.com/polysolve/).  
It provides polynomial equation from a cloud of points.  
Higher is the polynomial degree, higher is the accuracy for data fitting.  
Keep in mind one degree of polynome represents one inflexion.  

## Build

to build simply make

``` 
make
```

## Doc

to build doc

``` 
make doc
```

Then doc will be generated in the doc/html folder.

## Usage

Overview
``` 
./polyregress 
```
Detail
```
./polyregress -?
```

The first number of the serie is the higher degree.  
The following numbers are XY points and should be paired.  
Degree can't be higner than the number of XY points.  

``` 
echo "4 1 0 2 2 3 1 4 4 5 2" | ./polyregress -
```
or
``` 
./polyregress - <<< "4 1 0 2 2 3 1 4 4 5 2"
```
or changing instream separator
``` 
./polyregress -s ',' - <<< "4,1,0,2,2,3,1,4,4,5,2"
```
or changing instream separator with debug
``` 
./polyregress -d -s ',' - <<< "4,1,0,2,2,3,1,4,4,5,2"
```

## Performance

It can perform from x3 upto x20 faster than the initial script, depending on **gcc** flags.  
Default setup is designed for x20.

``` 
time echo "4 1 0 2 2 3 1 4 4 5 2" | ./polyregress -
```

Removing the # line 14 in Makefile, will enforce security adding sanitizers but downperf to x3.  

Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.

## Accuracy

Here we are dealing with double type.  
You can change the solution accuracy from the solution.h file.  

``` 
#define SOL_ACCURACY_FMT "14"
``` 

## Limitations

Input buffer is limited to 2048 bytes but you can change it in main.

## Tests

Tests are based on [CUnity/Cunit framework](https://gitlab.com/cunity/cunit).  
Setup from Debian package (old release ...v2.1)   
``` 
sudo apt-get install libcunit1 libcunit1-dev 
```
Or build from source (fresh release v3.2.7), clone repo and follow the Readme.  
Then
``` 
make
sudo make install
```
I recommend to build from source because setup and teardown can be done both on suite and test.

Build tests from root project.  

``` 
make
make test
```
to run tests with or without options (bci)
``` 
./polyregress_test <options>
```

## Todo

* Add features from arguments flags (WIP).
* Populate data from various file format (csv,..).

## Links

* [C++ polyreg](https://gogs.pier-infor.fr/pf.pier-infor.fr/polyreg) to reuse result and play with the gnuplot renderer.
* [Array Pointer](https://www.geeksforgeeks.org/pointer-array-array-pointer/) to understand how to use a 2D matrix with a 1D array and pointers.
* [Matrices and Linear Algebra](http://www.mymathlib.com/matrices/) to find most common practices on matrices.