#!/usr/bin/bash


make -s cleancsv
THREADS=(1 2 3 4)


echo "thread,i,time" &>>mesuresProd.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
    make PC -s
    /usr/bin/time -f "$thread,$i,%e" ./fec $thread $thread -s &>>mesuresProd.csv 
    make -s clean
    done
done

echo "thread,i,time" &>>mesuresPhilosophe.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
    make fec -s #-s ne print pas dans le terminal
	/usr/bin/time -f "$thread,$i,%e" ./fec $thread -s &>>mesuresPhilosophe.csv #-f specifier le format
    make -s clean
    done
done

#./script.sh
#bash script.sh