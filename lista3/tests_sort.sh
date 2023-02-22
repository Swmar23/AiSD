#!/bin/bash

for i in {100..10000..100}
do
	for k in {1..100}
	do
		./generator $i | ./quick_sort >> "results_quick_sort.txt"
		./generator $i | ./dual_pivot_quicksort >> "results_dual_pivot_quicksort.txt"
		./generator_asc $i | ./quick_sort >> "results_quick_sort_worst.txt"
		./generator_asc $i | ./dual_pivot_quicksort >> "results_dual_pivot_quicksort_worst.txt"
		./generator $i | ./quick_sort_select >> "results_quick_sort_select.txt"
		./generator $i | ./dual_pivot_quicksort_select >> "results_dual_pivot_quicksort_select.txt"
		./generator_asc $i | ./quick_sort_select >> "results_quick_sort_select_worst.txt"
		./generator_asc $i | ./dual_pivot_quicksort_select >> "results_dual_pivot_quicksort_select_worst.txt"
	done
done
 
