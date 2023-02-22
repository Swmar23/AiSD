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

// global variables used in `print_BST`
char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size

void printHeap( int rootIndex, int heapSize, int array[], int depth, char prefix) {
  if( rootIndex >= heapSize ) return;
  if( 2 * rootIndex + 1 < heapSize ){
    printHeap(2 * rootIndex + 1, heapSize, array, depth+1, '/');
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) {
      printf("| ");
    } else {
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  printf("[%d]\n", array[rootIndex]);
  left_trace[depth]=' ';
  if( 2 * rootIndex + 2 < heapSize ){
    right_trace[depth]='|';
    printHeap(2 * rootIndex + 2, heapSize, array, depth+1, '\\');
  }
}

void heapify (int heapArray[], int heapSize, int rootIndex) {
  int largest = rootIndex;
  int left = 2 * rootIndex + 1; // tak jest przy numerowaniu od zera; od jedynki by było 2 * rootIndex
  int right = 2 * rootIndex + 2;
  if (left < heapSize && compare(heapArray[left], heapArray[rootIndex])) {
    largest = left;
  }
  if (right < heapSize && compare(heapArray[right], heapArray[largest])) {
    largest = right;
  }
  if (largest != rootIndex) {
    swap(heapArray[rootIndex], heapArray[largest]);
    heapify(heapArray, heapSize, largest);
  }
}

void buildHeap (int heapArray[], int heapSize) {
  for (int i = n/2 - 1; i >= 0; i--)
    heapify(heapArray, heapSize, i);
}

void heapSort(int array[], int arraySize) {
  buildHeap(array, arraySize);
  for (int i = arraySize-1; i >= 1; i--) {
    swap(array[i], array[0]);
    heapify(array, i, 0);
    if(arraySize < 50)
      printArray(array);
    if(arraySize < 15)
      printHeap(0, i, array, 0, '-');
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

  left_trace = (char*)malloc( n*sizeof(char) );
  right_trace = (char*)malloc( n*sizeof(char) );

  if(n<50) printArrayStatus(array);
  printArray(array);
  heapSort(array, n);
  if(n<50) printArrayStatus(array);
  cout << n << ";" << no_assigns << ";" << no_comparisons << endl;
  return 0;
}