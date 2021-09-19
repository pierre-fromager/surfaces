# Surfaces

Surfaces illustrates howto fast calculate order 1 function integral.  


## Build

``` 
make
```

## Doc
Doc will be generated in the doc/html folder.

``` 
make doc
```

## Usage

Overview
``` 
./surfaces 
```
Detail
```
./surfaces -?
```

## Performance

Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.

## Accuracy

Here we are dealing with double type.  

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
./surfaces_test <options>
```
