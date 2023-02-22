#!/bin/bash

for i in {10000..100000..10000}
do
	for k in {1..20}
	do
		./generator_randinsert_randdel $i | ./bst >> "results_bst_rand_rand.txt"
		./generator_ascinsert_randdel $i | ./bst >> "results_bst_asc_rand.txt"
	done
done
 
