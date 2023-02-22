#!/bin/bash

for i in {10000..100000..10000}
do
	for k in {1..20}
	do
		./generator_ascinsert_randdel $i | ./rbt >> "results_rbt_asc_rand.txt"
		echo "$i | $k"
	done
done
 
