#!/bin/bash

debug='-D CMAKE_BUILD_TYPE=Debug'    # debug='' pour build en release

#Trouve le nombre de core
core=`grep -c ^processor /proc/cpuinfo`
jobs=`expr $core + 1`

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

if [ ! -e client/build ]; then
	mkdir client/build
fi

cd biblio/build
cmake $debug ..
if [ $? -ne 0 ]; then exit 1 ; fi 
make -j$jobs
if [ $? -ne 0 ]; then exit 1 ; fi 

cd ../../communsce/build
cmake $debug ..
if [ $? -ne 0 ]; then exit 1 ; fi 
make -j$jobs
if [ $? -ne 0 ]; then exit 1 ; fi 

cd ../../editeur/build
cmake $debug ..
if [ $? -ne 0 ]; then exit 1 ; fi 
make -j$jobs
if [ $? -ne 0 ]; then exit 1 ; fi 

cd ../../client/build
cmake $debug ..
if [ $? -ne 0 ]; then exit 1 ; fi
make -j$jobs
if [ $? -ne 0 ]; then exit 1 ; fi

