#!/bin/bash

cd /root/acorn
mkdir build
cd build
/usr/local/Qt-5.15.2/bin/qmake ../acorn.pro -spec linux-g++ CONIFG+=release && make -j$(nproc)
