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

THREADS=(2 3 4 5 6)
echo "thread,i,time" &>>mesuresEL.csv
for thread in "${THREADS[@]}"; do
    thread1=$((($thread+$thread%2)/2))
    thread2=$((($thread-$thread%2)/2))
    for i in {1..5}; do
        make EL -s
        /usr/bin/time -f "$thread,$i,%e" ./EL $thread1 $thread2 &>>mesuresEL.csv 
        make clean -s
    done
done

#./script.sh
#bash script.sh