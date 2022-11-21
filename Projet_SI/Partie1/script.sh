#!/usr/bin/bash

gcc -o philo Philosophe.c -lpthread
THREADS=(1 2 3 4)

echo "thread,i,time"
for thread in "${THREADS[@]}"; do
    for i in {1..5}; do
	/usr/bin/time -f "$thread,$i,%E" ./philo $thread
	rm -f philo
    done
done

#./script.sh &>mesures.csv
#bash script.sh