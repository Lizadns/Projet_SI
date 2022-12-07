#!/usr/bin/bash


make -s cleancsv 

#mesures performances Producteurs/consommateurs
THREADS=(2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresProd.csv
for thread in "${THREADS[@]}"; do
    thread1=$(($thread/2))
    for i in {1..5}; do
        make PC -s
        /usr/bin/time -f "$thread,$i,%e" ./PC $thread1  &>>mesuresProd.csv 
        make clean -s
    done
done

#mesures performances Philosophe
THREADS=(1 2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresPhilosophe.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make Philosophe -s
        /usr/bin/time -f "$thread,$i,%e" ./Philosophe $thread  &>>mesuresPhilosophe.csv 
        make clean -s
    done
done

#mesures performances Ecrivains/lecteurs
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

#mesures performances Test_and_set
echo "thread,i,time" &>>mesuresTestAndSet.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make tas -s
        /usr/bin/time -f "$thread,$i,%e" ./tas $thread  &>>mesuresTestAndSet.csv 
        make clean -s
    done
done

#mesures performances test_and_test_and_set
echo "thread,i,time" &>>mesuresTestAndTestAndSet.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make tatas -s
        /usr/bin/time -f "$thread,$i,%e" ./tatas $thread  &>>mesuresTestAndTestAndSet.csv
        make clean -s
    done
done

#mesures performances Producteurs/consommateurs avec attente active
THREADS=(2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresPC2.csv
for thread in "${THREADS[@]}"; do
    thread1=$(($thread/2))
    for i in {1..5}; do
        make PC2 -s
        /usr/bin/time -f "$thread,$i,%e" ./PC2 $thread1  &>>mesuresPC2.csv
        make clean -s
    done
done

#mesures performances Philosophe avec attente active
THREADS=(1 2 4 8 16 32 64)
echo "thread,i,time" &>>mesuresPhilosophe2.csv
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
        make Philosophe2 -s
        /usr/bin/time -f "$thread,$i,%e" ./Philosophe2 $thread  &>>mesuresPhilosophe2.csv
        make clean -s
    done
done

#mesures performances Ecrivains/lecteurs avec attente active
echo "thread,i,time" &>>mesuresEL2.csv
for thread in "${THREADS[@]}"; do
    thread1=$((($thread+$thread%2)/2))
    thread2=$((($thread-$thread%2)/2))
    for i in {1..5}; do
        make EL2 -s
        /usr/bin/time -f "$thread,$i,%e" ./EL2 $thread1 $thread2  &>>mesuresEL2.csv
        make clean -s
    done
done

#./script.sh
#bash script.sh