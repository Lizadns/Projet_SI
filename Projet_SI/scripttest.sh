#!/usr/bin/bash

make -s cleantest

THREADS=(1 2 3 4 5 6)
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
        make tas -s
        /usr/bin/time -f "$thread,$i,%e" ./tas $thread  &>>mesuresTestAndTestAndSet.csv
        make clean -s
    done
done