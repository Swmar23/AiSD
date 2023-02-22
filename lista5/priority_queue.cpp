//MAREK ŚWIERGOŃ 261750

#include <iostream>

using namespace std;

int n = 0;
long no_assigns = 0;
long no_comparisons = 0;


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

void printArray(int array[], int arraySize) {
  for(int i = 0; i < arraySize; i++) {
    cout << array[i] << " ";
  }
  cout << endl;

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

void heapify (int priorityQueue[], int queueSize, int rootIndex) {
  int largest = rootIndex;
  int left = 2 * rootIndex + 1; // tak jest przy numerowaniu od zera; od jedynki by było 2 * rootIndex
  int right = 2 * rootIndex + 2;
  if (left < queueSize && compare(priorityQueue[left], priorityQueue[rootIndex])) {
    largest = left;
  }
  if (right < queueSize && compare(priorityQueue[right], priorityQueue[largest])) {
    largest = right;
  }
  if (largest != rootIndex) {
    swap(priorityQueue[rootIndex], priorityQueue[largest]);
    heapify(priorityQueue, queueSize, largest);
  }
}

void buildHeap (int priorityQueue[], int queueSize) {
  for (int i = n/2 - 1; i >= 0; i--)
    heapify(priorityQueue, queueSize, i);
}

int getMax (int priorityQueue[]) {
  return priorityQueue[0];
}

int extractMax (int priorityQueue[], int& queueSize) {
  if (queueSize < 1) {
    cout << "extractMax: empty queue! returning -1" << endl;
    return -1;
  }
  else {
    int max = priorityQueue[0];
    assignKey(priorityQueue[0], priorityQueue[queueSize - 1]);
    queueSize--;
    heapify(priorityQueue, queueSize, 0);
    return max;
  }
}

void insert (int priorityQueue[], int key, int& queueSize) {
  queueSize++;
  int i = queueSize - 1;
  //heapifyUp
  while (i > 0 && compare(key, priorityQueue[(i-1)/2])) {
    assignKey(priorityQueue[i], priorityQueue[(i-1)/2]);
    i = (i-1)/2;
  }
  assignKey(priorityQueue[i], key);
}

void deleteFromQueue (int priorityQueue[], int indexToDelete, int& queueSize) {
  assignKey(priorityQueue[indexToDelete], priorityQueue[queueSize - 1]);
  queueSize--;
  heapify(priorityQueue, queueSize, indexToDelete);
}

int main() {
  cin >> n;
  left_trace = (char*)malloc( n*sizeof(char) );
  right_trace = (char*)malloc( n*sizeof(char) );
  int array[n] = {0};
  int element = 0;
  int i = 0;
  int queueSize = 0;
  long max_assigns_insert = 0;
  long max_assigns_extract = 0;
  long max_comparisons_insert = 0;
  long max_comparisons_extract = 0;
  long long all_assigns_insert = 0;
  long long all_assigns_extract = 0;
  long long all_comparisons_insert = 0;
  long long all_comparisons_extract = 0;
  double avg_assigns_insert = 0.0;
  double avg_comparisons_insert = 0.0;
  double avg_assigns_extract = 0.0;
  double avg_comparisons_extract = 0.0;

  while (i < n && cin >> element) {
    insert(array, element, queueSize);
    all_assigns_insert += no_assigns;
    all_comparisons_insert += no_comparisons;
    if(no_assigns > max_assigns_insert) {
      max_assigns_insert = no_assigns;
    }
    if(no_comparisons > max_comparisons_insert) {
      max_comparisons_insert = no_comparisons;
    }
    if (n < 50) {
      cout << "insert " << element << endl;
      printArray(array, queueSize);
      printHeap(0, queueSize, array, 0, '-');
    }
    no_assigns = 0;
    no_comparisons = 0;
  }

  avg_assigns_insert = (double)all_assigns_insert / (double)n;
  avg_comparisons_insert = (double)all_comparisons_insert / (double)n;
  no_comparisons = 0;
  no_assigns = 0;

  while(queueSize > 0) {
    int extractedElement = extractMax(array, queueSize);
    all_assigns_extract += no_assigns;
    all_comparisons_extract += no_comparisons;
    if(no_assigns > max_assigns_extract) {
      max_assigns_extract = no_assigns;
    }
    if(no_comparisons > max_comparisons_extract) {
      max_comparisons_extract = no_comparisons;
    }
    if (n < 50) {
      cout << "extractMax " << extractedElement << endl;
      printArray(array, queueSize);
      printHeap(0, queueSize, array, 0, '-');
    }
    no_assigns = 0;
    no_comparisons = 0;
  }

  avg_assigns_extract = (double)all_assigns_extract / (double)n;
  avg_comparisons_extract = (double)all_comparisons_extract / (double)n;
  cout << n << ";" << avg_assigns_insert << ";" << max_assigns_insert << ";" << avg_comparisons_insert << ";" 
  << max_comparisons_insert << ";" << avg_assigns_extract << ";" << max_assigns_extract << ";" << avg_comparisons_extract << ";" << max_comparisons_extract << endl;
  return 0;
}