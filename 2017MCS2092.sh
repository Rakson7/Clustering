#!/bin/sh

if [ "$1" = "-kmeans" ]
then
  python3 ./KMeans/kmeans.py $2 $3
elif [ "$1" = "-dbscan" ]
then
  ./dbscan.out $2 $3 $4
elif [ "$1" = "-optics" ]
then 
  python3 ./Optics/plot.py $2 $3 $4
fi

