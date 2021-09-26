# Surfaces

Surfaces illustrates how to fast calculate surface from a polynomial.  
A factory design pattern let an exact calculus for polynomial with order lower than 2,
otherwise an iterative approximation will be applied from riemann sum algorithm with a partitioning factor.  

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

## Links

* [Méthodes numériques de résolution d’équations différentielles](https://www.fresnel.fr/perso/stout/Anal_numer/Cours4.pdf)
* [Taylor Series](https://2k8618.blogspot.com/2011/05/taylor-series-c-program.html)
* [Runge-Kutta Methods](https://www.bragitoff.com/2017/09/runge-kutta-methods-c-program/)
* [Fourth Order Runge-Kutta](https://www.patnauniversity.ac.in/e-content/science/physics/RungeKuttaIVmethod(PG)_CC05&09_Physics_SanjayKumar.pdf)
* [Calcul intégral](https://lyceesgisors.spip.ac-rouen.fr/IMG/pdf/integration-2.pdf)
* [Riemann sum](https://en.wikipedia.org/wiki/Riemann_sum)
* [Calcul numérique d'une intégrale](https://fr.wikipedia.org/wiki/Calcul_num%C3%A9rique_d%27une_int%C3%A9grale)
* [Calcul numérique intégrale - exercicce](https://ressources.unisciel.fr/ramses/517-3-calcul-integral/co/fe701_1.html)
* [Area Under a Curve](https://revisionmaths.com/advanced-level-maths-revision/pure-maths/calculus/area-under-curve)
* [integral-calculator](https://github.com/arasgungore/integral-calculator)