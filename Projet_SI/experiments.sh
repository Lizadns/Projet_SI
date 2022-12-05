#!/usr/bin/bash


make -s cleancsv 

THREADS=(1 2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresProd.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make PC -s
        /usr/bin/time -f "$thread,$i,%e" ./PC $thread  &>>mesuresProd.csv 
        make clean -s
    done
done

echo "thread,i,time" &>>mesuresPhilosophe.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make fec -s
        /usr/bin/time -f "$thread,$i,%e" ./fec $thread  &>>mesuresPhilosophe.csv 
        make clean -s
    done
done


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

echo "thread,i,time" &>>mesuresPhilosophe2.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make fec2 -s
        /usr/bin/time -f "$thread,$i,%e" ./fec2 $thread  &>>mesuresPhilosophe2.csv
        make clean -s
    done
done

echo "thread,i,time" &>>mesuresEL2.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make EL2 -s
        /usr/bin/time -f "$thread,$i,%e" ./EL2 $thread $thread  &>>mesuresEL2.csv
        make clean -s
    done
done

#./script.sh
#bash script.sh