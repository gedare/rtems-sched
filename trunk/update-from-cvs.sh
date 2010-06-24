#!/bin/bash

cd rtems
./bootstrap -c
svn up
svn st
cvs up -Pd 2>&1 | grep -v ^cvs 
cd ..

echo "Fix any conflicts, then run commit-to-svn.sh"

