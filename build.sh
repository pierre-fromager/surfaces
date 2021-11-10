#!/bin/bash
make doc
make clean
make cleantest
make
make lib
make test
./surfaces_test