#!/bin/bash

for i in {90000..100000..10000}
do
	for k in {1..20}
	do
		./generator_randinsert_randdel $i | ./splay >> "results_splay_rand_rand_high.txt"
		echo "$i | $k"
	done
done
 
