#!/bin/sh
sudo apt-get update -qq
sudo apt-get install -y libftdi1 libftdi-dev libconfuse0 libconfuse-dev
wget http://download.telldus.se/TellStick/Software/telldus-core/telldus-core-2.1.2.tar.gz -O /tmp/telldus-core.tar.gz
cd /tmp
tar -xvf telldus-core.tar.gz
cd telldus-core-2.1.2
cmake .
make 
sudo make install 
