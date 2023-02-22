#!/bin/bash

for i in {10000..100000..10000}
do
	for k in {1..100}
	do
		./generator $i | ./priority_queue >> "results_priority_queue.txt"
		echo "$i | $k"
	done
done
 
