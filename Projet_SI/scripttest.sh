#!/usr/bin/bash

make -s cleantest

THREADS=(1 2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresTestAndSet.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make tas -s
        /usr/bin/time -f "$thread,$i,%e" ./tas $thread  &>>mesuresTestAndSet.csv 
        make clean -s
    done
done

echo "thread,i,time" &>>mesuresTestAndTestAndSet.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make tatas -s
        /usr/bin/time -f "$thread,$i,%e" ./tatas $thread  &>>mesuresTestAndTestAndSet.csv
        make clean -s
    done
done

echo "thread,i,time" &>>mesuresPC2.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make PC2 -s
        /usr/bin/time -f "$thread,$i,%e" ./PC2 $thread  &>>mesuresPC2.csv
        make clean -s
    done
done