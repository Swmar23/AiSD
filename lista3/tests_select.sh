#!/bin/bash

for i in {100..10000..100}
do
	for k in {1..100}
	do
		./generator $i | ./select $(($i / 2)) >> "results_select_div2.txt"
		./generator $i | ./select $(($i / 4)) >> "results_select_div4.txt"
		./generator $i | ./select $(($i / 4 * 3)) >> "results_select_3div4.txt"
		./generator $i | ./randomized_select $(($i / 2)) >> "results_rselect_div2.txt"
		./generator $i | ./randomized_select $(($i / 4)) >> "results_rselect_div4.txt"
		./generator $i | ./randomized_select $(($i / 4 * 3)) >> "results_rselect_3div4.txt"
		./generator $i | ./kselect $(($i / 2)) 3 >> "results_kselect3_div2.txt"
		./generator $i | ./kselect $(($i / 4)) 3 >> "results_kselect3_div4.txt"
		./generator $i | ./kselect $(($i / 4 * 3)) 3 >> "results_kselect3_3div4.txt"
		./generator $i | ./kselect $(($i / 2)) 5 >> "results_kselect5_div2.txt"
		./generator $i | ./kselect $(($i / 4)) 5 >> "results_kselect5_div4.txt"
		./generator $i | ./kselect $(($i / 4 * 3)) 5 >> "results_kselect5_3div4.txt"
		./generator $i | ./kselect $(($i / 2)) 7 >> "results_kselect7_div2.txt"
		./generator $i | ./kselect $(($i / 4)) 7 >> "results_kselect7_div4.txt"
		./generator $i | ./kselect $(($i / 4 * 3)) 7 >> "results_kselect7_3div4.txt"
		./generator $i | ./kselect $(($i / 2)) 9 >> "results_kselect9_div2.txt"
		./generator $i | ./kselect $(($i / 4)) 9 >> "results_kselect9_div4.txt"
		./generator $i | ./kselect $(($i / 4 * 3)) 9 >> "results_kselect9_3div4.txt"	
	done
done
 
