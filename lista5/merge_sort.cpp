//MAREK ŚWIERGOŃ 261750

#include <iostream>

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

void merge(int array[], int left, int mid, int right) {
  int subarrayOneLength = mid - left + 1;
  int subarrayTwoLength = right - mid;

  int *leftArray = new int[subarrayOneLength];
  int *rightArray = new int[subarrayTwoLength];

  for(int i = 0; i < subarrayOneLength; i++)
    assignKey(leftArray[i],array[left+i]);
  for(int j = 0; j < subarrayTwoLength; j++)
    assignKey(rightArray[j],array[mid+1+j]);
  int i_one = 0;
  int i_two = 0;
  int i_merged = left;
  while(i_one < subarrayOneLength && i_two < subarrayTwoLength) {
    if(compare(rightArray[i_two], leftArray[i_one])) {
      assignKey(array[i_merged], leftArray[i_one]);
      i_one++;
    }
    else {
      assignKey(array[i_merged], rightArray[i_two]);
      i_two++;
    }
    i_merged++;
  }

  while(i_one < subarrayOneLength) {
    assignKey(array[i_merged], leftArray[i_one]);
    i_one++;
    i_merged++;
  }

    while(i_two < subarrayTwoLength) {
    assignKey(array[i_merged], rightArray[i_two]);
    i_two++;
    i_merged++;
  }

  printArray(array);
}

void mergeSort(int array[], int start, int end) {
  if(start >= end) 
    return;
  int mid = start + (end - start) / 2;
  mergeSort(array, start, mid);
  mergeSort(array, mid+1, end);
  merge(array, start, mid, end);
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
  mergeSort(array, 0, n-1);
  if(n<50) printArrayStatus(array);
  cout << n << ";" << no_assigns << ";" << no_comparisons << endl;
  return 0;
}