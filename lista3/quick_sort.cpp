//MAREK ŚWIERGOŃ 261750

#include <iostream>
#include <chrono>

using namespace std;

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

void quickSort(int array[], int start, int end) {
  if(start < end) {
    int pivotIndex = lomutoPartition(array, start, end);
    quickSort(array, start, pivotIndex-1);
    quickSort(array, pivotIndex+1, end); 
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

int main() {
  cin >> n;
  int array[n] = {0};
  int element = 0;
  int i = 0;
  while(cin >> element) {
    array[i] = element;
    i++;
  }
  if(n<50) printArrayStatus(array);
  printArray(array);
  auto start = chrono::high_resolution_clock::now();
  quickSort(array, 0, n-1);
  auto finish = chrono::high_resolution_clock::now();
  int time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  if(n<50) printArrayStatus(array);
  cout << n << ";" << no_comparisons << ";" << time << endl;
  return 0;
}