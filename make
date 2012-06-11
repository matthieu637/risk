#!/bin/bash

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
cmake ..
make -j3

cd ../../communsce/build
cmake ..
make -j3

cd ../../editeur/build
cmake ..
make -j3


