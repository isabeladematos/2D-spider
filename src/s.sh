#!/bin/sh

echo "file1 $1.cpp file2 $2.cpp"
g++ -c $2.cpp -lglut -lGLU -lGL -lm
echo "$2.o generated"
g++ -c $1.cpp -lglut -lGLU -lGL -lm
echo "$1.o generated"
g++ -o $1 $1.o $2.o -lglut -lGLU -lGL -lm
echo "$1 executable"
