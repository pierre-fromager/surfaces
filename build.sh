#!/bin/bash
make doc
make clean
make cleantest
make
make test
./surfaces_test