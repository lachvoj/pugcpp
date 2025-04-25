#!/bin/bash

FILES=$(find -name *.hpp)
for f in $FILES
do
    fname=$(basename "$f" .hpp)
    echo "$fname"
    sed -i "s/#ifndef $fname/#ifndef ${fname}_hpp/" $f
    sed -i "s/#define $fname/#define ${fname}_hpp/" $f
    # echo "#endif" >> $f
    # echo "" >> $f
done