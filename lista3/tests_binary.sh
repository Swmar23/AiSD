#!/bin/bash

for i in {1000..100000..1000./}
do
	for k in {1..100}
	do
		./generator_binary $i -l | ./binary_search >> "results_binary_l.txt"
		./generator_binary $i -o | ./binary_search >> "results_binary_o.txt"
		./generator_binary $i -h | ./binary_search >> "results_binary_h.txt"
		./generator_binary $i -m | ./binary_search >> "results_binary_m.txt"
		./generator_binary $i -r | ./binary_search >> "results_binary_r.txt"
	done
done
 
