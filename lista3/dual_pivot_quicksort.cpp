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

int partition(int array[], int start, int end, int& leftPivot) {

  if (compare(array[start], array[end]) ) {
    swap(array[start], array[end]);
  }
  int p = array[start];
  int q = array[end];
  int lowIndex = start + 1;
  int highIndex = end - 1;
  for (int j = start+1; j <= highIndex; j++) {

    if (compare(p, array[j])) {
      swap(array[j], array[lowIndex]);
      lowIndex++;
    }
    else if (!compare(q, array[j])) {
      while (compare(array[highIndex], q) && j < highIndex ) {
        highIndex--;
      }
      swap(array[j], array[highIndex]);
      highIndex--;
      if (compare(p, array[j])) {
        swap(array[j], array[lowIndex]);
        lowIndex++;
      }
    }
  }
  lowIndex--;
  highIndex++;

  swap(array[start], array[lowIndex]);
  swap(array[end], array[highIndex]);
  printArray(array);

  leftPivot = lowIndex;
  return highIndex;
}

void dualPivotQuickSort(int array[], int start, int end) {
  if(start < end) {
    int p, q;
    q = partition(array, start, end, p);
    dualPivotQuickSort(array, start, p-1);
    dualPivotQuickSort(array, p+1, q-1);
    dualPivotQuickSort(array, q+1, end);
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
  dualPivotQuickSort(array, 0, n-1);
  auto finish = chrono::high_resolution_clock::now();
  int time = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
  if(n<50) printArrayStatus(array);
  cout << n << ";" << no_comparisons << ";" << time << endl;
  return 0;
}