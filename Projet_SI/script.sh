#!/usr/bin/bash


make -s cleancsv 

THREADS=(1 2 3)
echo "thread,i,time" &>>mesuresProd.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make PC -s
        /usr/bin/time -f "$thread,$i,%e" ./PC $thread  &>>mesuresProd.csv 
        make clean -s
    done
done

THREADS=(2 3 4 5 6)
echo "thread,i,time" &>>mesuresPhilosophe.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make fec -s
        /usr/bin/time -f "$thread,$i,%e" ./fec $thread  &>>mesuresPhilosophe.csv 
        make clean -s
    done
done

#./script.sh
#bash script.sh