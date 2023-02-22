#!/bin/bash

for i in {100..1000..100}
do
	for k in {1..100}
	do
		./generator $i | ./insertion_sort >> "results_insertion_sort.txt"
		./generator $i | ./quick_sort >> "results_quick_sort.txt"
		./generator $i | ./merge_sort >> "results_merge_sort.txt"
		./generator $i | ./dual_pivot_quicksort >> "results_dual_pivot_quicksort.txt"
		./generator $i | ./hybrid_sort >> "results_hybrid_sort.txt"
	done
done
 
