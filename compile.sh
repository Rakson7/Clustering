#!/bin/sh

g++ -std=c++14 -O3 ./Optics/main.cpp -o optics.out

g++ -std=c++14 -O3 ./DBSCAN/*.cpp -o dbscan.out
