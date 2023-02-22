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
  int key;
  for(int j = 1; j < n; j++) {
    assignKey(key,array[j]);
    i = j-1;
    while (i >= 0 && compare(array[i], key)) {
      assignKey(array[i+1], array[i]);
      i--;
    }
    assignKey(array[i+1], key);
    printArray(array);
  }
  if(n<50) printArrayStatus(array);
  cout << n << ";" << no_assigns << ";" << no_comparisons << endl;
  return 0;
}