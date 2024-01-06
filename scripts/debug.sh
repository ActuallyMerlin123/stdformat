#!/bin/bash
# -*- coding: utf-8 -*-

cd ../build
rm -rf *
cmake -DCMAKE_BUILD_TYPE=Debug .. &&
make -j4 && # set to cores
cd ../bin
