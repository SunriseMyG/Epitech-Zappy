#!/bin/sh

cd build/ &&
cmake .. &&
make &&
cd .. &&
./zappy_gui 4242 127.0.0.1