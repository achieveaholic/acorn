#!/bin/bash

cd /root/acorn
qmake acorn.pro -spec linux-g++ CONIFG+=release && make -j$(nproc)
