#!/bin/bash

	for k in {1..10}
	do
		./generator_randinsert_randdel 100000 | ./splay >> "results_splay_rand_rand_high_high2.txt"
		echo "100000 | $k"
	done