#!/bin/bash

PREFIX=`pwd`

cd jpeg-9c

./configure --disable-shared --prefix=${PREFIX}

make clean
make
make install

cd ..
