#!/bin/bash

debug='-D CMAKE_BUILD_TYPE=Debug'    # debug='' pour build en release

#Trouve le nombre de core
core=`grep -c ^processor /proc/cpuinfo`
jobs=`expr $core + 1`
echo $jobs

if [ ! -e ./biblio ]; then
	echo "Placez vous dans risk/"
	exit 1
fi

if [ ! -e biblio/build ]; then
	mkdir biblio/build
fi

if [ ! -e communsce/build ]; then
	mkdir communsce/build
fi

if [ ! -e editeur/build ]; then
	mkdir editeur/build
fi

cd biblio/build
cmake $debug ..
make -j$jobs

cd ../../communsce/build
cmake $debug ..
make -j$jobs

cd ../../editeur/build
cmake $debug ..
make -j$jobs


