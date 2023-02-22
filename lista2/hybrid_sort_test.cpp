//MAREK ŚWIERGOŃ 261750

#include <random>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
using namespace std;

static random_device rd;
static mt19937 rng{rd()}; 

int dice(int size)
{
  static uniform_int_distribution<int> uid(0,2*size-1); 
  return uid(rng);
}

int n = 0;
int no_assigns = 0;
int no_comparisons = 0;


void assignKey(int& i, int& j) {
  i = j;
  no_assigns++;
}

void swap(int& i, int& j) {
  int help;
  assignKey(help, i);
  assignKey(i, j);
  assignKey(j, help);
}

bool compare(int i, int j) {
  no_comparisons++;
  if(i > j) {
    return true;
  }
  return false;
}

void printArray(int array[]) {
  if(n < 50) {
    for(int i = 0; i < n; i++) {
      cout << array[i] << " ";
    }
    cout << endl;
  }
}

int lomutoPartition(int array[], int start, int end) {
  int pivot = array[start];
  int i = start;
  for(int j = start+1; j <= end; j++) {
    if(compare(pivot, array[j])) {
      i++;
      swap(array[i], array[j]);
    }
  }
  swap(array[i], array[start]);
  printArray(array);
  return i;
}

void insertionSort(int array[], int start, int end) {
  int key, i;
  for(int j = start+1; j <= end; j++) {
    key = array[j];
    i = j-1;
    while (i >= 0 && compare(array[i], key)) {
      assignKey(array[i+1], array[i]);
      i--;
    }
    array[i+1] = key;
    printArray(array);
  }
}

void hybridSort(int array[], int start, int end, int max_insert_size) {
  if((start + max_insert_size - 1) < end) {
    int pivotIndex = lomutoPartition(array, start, end);
    hybridSort(array, start, pivotIndex-1, max_insert_size);
    hybridSort(array, pivotIndex+1, end, max_insert_size);
  }
  else if(start < end) {
    insertionSort(array, start, end);
  }
}

bool isArraySorted(int array[]) {

  for(int i = 0; i < n; i++) 
  if(i > 0) {
    if(array[i-1] > array[i]) {
      return false;
    }
  }

  return true;
}

void printArrayStatus(int array[]) {
  if(isArraySorted(array)) {
    cout << "Tablica jest posortowana" << endl;
  }
  else {
    cout << "Tablica nie jest posortowana" << endl;
  }
}

int main(int argc, char **argv) {
  if(argc > 1) {
    if (strlen(argv[1]) == 0) {
      return 1; 
    }
    char* p;
    errno = 0;
    long arg = strtol(argv[1], &p, 10);
    if (*p != '\0' || errno != 0) {
      return 1;
    }
    if (arg < INT_MIN || arg > INT_MAX) {
      return 1;
    }
    n = arg;
    for(int i = 1; i <= 100; i++) {
      double avg_assigns = 0.0;
      double avg_comparisons = 0.0;
      for(int k = 0; k < 1000; k++) {
        int array[n] = {0};
        for(int i = 0; i < n; i++) {
          array[i] = dice(n);
        }
        no_assigns = 0;
        no_comparisons = 0;
        hybridSort(array, 0, n-1, i);
        avg_assigns += no_assigns;
        avg_comparisons += no_comparisons;
      }
      avg_assigns = avg_assigns / 1000.0;
      avg_comparisons = avg_comparisons / 1000.0;
      cout << i << ";" << avg_assigns << ";" << avg_comparisons << endl;
    }
  }
  else {
      cout << "Usage: ./hybrid_sort_test size" << endl;
  }
  return 0;
}