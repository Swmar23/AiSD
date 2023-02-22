#!/bin/bash

for i in {10000..100000..10000}
do
	for k in {1..20}
	do
		./generator_randinsert_randdel $i | ./rbt >> "results_rbt_rand_rand.txt"
		echo "$i | $k"
	done
done
 
