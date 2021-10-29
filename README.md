# Polynomial surface

Polynomial surface is a factory based on higher degree best effort.  

For polynomial max order higher than 48 gmp(int) or mpfr(float) is used.  

Default precision is 64bits but you have to consider mpfr requires 256UL * 16 to get relevant accuracy on x^4096.
  
## Requirements

* [gmp](https://gmplib.org/)
* [mpfr](https://www.mpfr.org/)
* [CUnity/Cunit](https://gitlab.com/cunity/cunit)

## Releases

### v1.0
* Highest tested order 48.

### v2.0
* Highest tested order gmp(mpz_t) 4096.

### v2.1.0 (prerelease)
* Highest tested order mpfr(mpfr_t) wip.

## Build
all
``` 
./build.sh
```
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
Note on multiple precision (max order > 48) you can change :
* AP engine (0 for gmp int or 1 for mpfr float) with -e option
* Precision with -p option

You can display the raw result with -v0 option.  
Typically messed up with exp greater than POLY_MAX_ORDER leading to buffer overflow
```
./surfaces -l-10 -h10 3+4x^2+x^16384
munmap_chunk(): invalid pointer
Abandon
```
or for french people
```
./surfaces -l-10 -h10 3+4x^2+x^16384
Exception en point flottant
```

Change related define in main to allow higher exp.  

## Performance
Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.  

If you activate the sanitizer options on compiler for debug purpose you will see some LeakSanitizer errors, it's a false positive because gmp lib allocation/free process is asm based and not managed by libasan.  

## Accuracy
Polynomial surface is optimized from higher order as below :
* o < 2 => middle point method.
* o < 4 => simpson method (aka rk4).
* o < 48 => antiderivative(primitiv) delta method.
* o > 48 => antiderivative(primitiv) delta method with multiple precision.

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
     Asserts      :   229471         0       n/a       n/a
     Tests        :       61         0         0         0
```

## Extra

Alternatives methods with no reliability are tested here.  

* Riemann sums(left,right,rect,trapezoid,midpoint).
* Simpson rules.
* Newton-cote.  

## Todo
* implement integral factory tests for mpfr.
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
* [Online integral calculator](https://www.integral-calculator.com/)
* [Symbolab online IC with ratios result](https://www.symbolab.com/solver/integral-calculator)

## Tools
To validate results while testing I used these tools :
* the powerfull [bc](https://en.wikipedia.org/wiki/Bc_(programming_language))
* [geogebra](https://en.wikipedia.org/wiki/GeoGebra)