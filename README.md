# Polynomial surface

Polynomial surface is a factory based on higher degree best effort.  
Alternatives methods with no reliability are tested here.  

* Riemann sums(left,right,rect,trapezoid,midpoint).
* Simpson rules.
* Newton-cote.  
  

## Version

* v2.0 codename gmpint.  
* Highest tested order 4096.

## Build
build
``` 
make
```
clean
``` 
make clean
```

## Doc
Generate to doc/html folder.
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

## Examples
Default interval [0..5]
```
./surfaces 3+x+2x^3
```
Custom interval [0..10] by short options
```
./surfaces -l0 -h10 3+x+2x^3
```
Custom interval [-10..10] by long options
```
./surfaces --low=-10 --high=10 3+x+2x^3
```
Custom interval [-10..10] with ratios by short options
```
./surfaces -l-10 -h10 1/3+2/3x+2/5x^3
```
Same as previous with raw result output
```
./surfaces -v0 -l-10 -h10 1/3+2/3x+2/5x^3
```
Typically messed up with exp greater than POLY_MAX_ORDER leading to buffer overflow
```
./surfaces -l-10 -h10 3+4x^2+x^16384
munmap_chunk(): invalid pointer
Abandon
```
Change related define in main to allow higher exp.  

## Performance
Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.  

If you activate the sanitizer options on compiler for debug purpose you will see some LeakSanitizer errors, it's a false positive because gmp lib allocation/free process is asm based and not managed by libasan.  

## Accuracy
Polynomial surface is optimized from higher order as below :
* o < 2 => middle point method.
* o < 4 => simpson method (aka rk4).
* o < 48 => antiderivative delta method.
* o > 48 => antiderivative delta method with gmp mpz_t (integer).

## Tests
* Tests are based on [CUnity/Cunit framework](https://gitlab.com/cunity/cunit).  
* I can assert this project to be widely tested.  

Build sources (fresh release v3.2.7), clone repo and follow the Readme.  
Then
``` 
make
sudo make install
```
Build tests from root project.  
``` 
make
make test
```
to run tests with or without options (bci)
``` 
./surfaces_test <options>
```
Clean tests from root project.  
``` 
make cleantest
```
Active tests report from polynomial highest order 0 upto 4096
```
Run Summary       -      Run    Failed  Inactive   Skipped
     Suites       :        6         0         0         0
     Asserts      :   196906         0       n/a       n/a
     Tests        :       53         0         0         0
```

## Todo
* use mpf_t to float result with gmp when max order greater than 48 (will be released in v3.0).
* make a lib (open to contributors).

## Contribute
* open to pull requests, fork then submit.

## Licence
* GNU3 GPL(not LGPL).  
* That means you can reuse a part or the whole for non commercial project.
* For other cases, pls contact me.

## Links
* [Area Under a Curve](https://revisionmaths.com/advanced-level-maths-revision/pure-maths/calculus/area-under-curve)
* [Rieman sum calculator](https://www.emathhelp.net/calculators/calculus-2/riemann-sum-calculator/?f=x%5E3+%2B+0.5x+%2B+3&a=0&b=5&n=4&type=mid)
* [Ratio addition](https://math.icalculator.info/ratio-addition-calculator.html)