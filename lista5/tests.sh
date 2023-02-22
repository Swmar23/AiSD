#!/bin/bash

for i in {100..10000..100}
do
	for k in {1..100}
	do
		./generator $i | ./insertion_sort >> "results_insertion_sort.txt"
		./generator $i | ./quick_sort >> "results_quick_sort.txt"
		./generator $i | ./merge_sort >> "results_merge_sort.txt"
		./generator $i | ./heap_sort >> "results_heap_sort.txt"
	done
done
 
