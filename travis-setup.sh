#!/bin/sh
export OLD_CXX=$CXX
export CXX=gcc
wget http://download.telldus.se/TellStick/Software/telldus-core/telldus-core-2.1.2.tar.gz -O /tmp/telldus-core.tar.gz
cd /tmp
tar -xvf telldus-core.tar.gz
cd telldus-core-2.1.2
cmake .
make 
sudo make install 
export CXX=$OLD_CXX
