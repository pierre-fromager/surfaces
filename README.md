# Surfaces

Surfaces let fast calculate surface from a polynomial form.  

A factory design pattern optimizes an exact calculus from degree with best effort.  

Riemann sum is exposed an tested here with no reliability purpose, just because it is the basement of integration theory.  
  
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

## Examples
Default interval
```
./surfaces 3+x+2x^3
```
Custom interval
```
./surfaces -l0 -h10 3+x+2x^3
```
Custom interval with ratios
```
./surfaces -l0 -h10 1/3+2/3x+2/5x^3
```

## Caveats parser and arguments

Parser is really minimalistic, when writing eq if first term start with minus sign, escape it as \\'your_poly_eq_here\\' to avoid conflict with args minus options.

## Performance

Read [Security-related flags and options for C compilers](https://airbus-seclab.github.io/c-compiler-security/) to know more.

## Accuracy

Polynomial calculus based on long double type.  

## Tests

Tests are based on [CUnity/Cunit framework](https://gitlab.com/cunity/cunit).  

Build sources (fresh release v3.2.7), clone repo and follow the Readme.  
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

## Links

* [Méthodes numériques de résolution d’équations différentielles](https://www.fresnel.fr/perso/stout/Anal_numer/Cours4.pdf)
* [Calcul intégral](https://lyceesgisors.spip.ac-rouen.fr/IMG/pdf/integration-2.pdf)
* [Riemann sum](https://en.wikipedia.org/wiki/Riemann_sum)
* [Calcul numérique d'une intégrale](https://fr.wikipedia.org/wiki/Calcul_num%C3%A9rique_d%27une_int%C3%A9grale)
* [Calcul numérique intégrale - exercicce](https://ressources.unisciel.fr/ramses/517-3-calcul-integral/co/fe701_1.html)
* [Area Under a Curve](https://revisionmaths.com/advanced-level-maths-revision/pure-maths/calculus/area-under-curve)
* [integral-calculator](https://github.com/arasgungore/integral-calculator)
* [Rieman sum calculator](https://www.emathhelp.net/calculators/calculus-2/riemann-sum-calculator/?f=x%5E3+%2B+0.5x+%2B+3&a=0&b=5&n=4&type=mid)
