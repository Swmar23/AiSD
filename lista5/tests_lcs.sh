#!/bin/bash

for i in {1000..5000..1000}
do
	for k in {1..100}
	do
		./generator_lcs $i | ./lcs >> "results_lcs.txt"
	done
done
 
