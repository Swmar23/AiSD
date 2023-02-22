//MAREK ŚWIERGOŃ 261750

#include <random>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;

static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
// initialize Mersennes' twister using rd to generate the seed
static std::mt19937 rng{rd()}; 

int arrayRand(int size)
{
  static std::uniform_int_distribution<int> uid(0,2*size-1);
  return uid(rng); //rng jako generator
}

int indexRand(int size) {
  if(size > 0) {
    static uniform_int_distribution<int> uid(0,size-1);
    return uid(rng); //rng jako generator
  }
  else {
    return 0;
  }
}

int main(int argc, char **argv)
{
  if(argc > 2) {
    if (strlen(argv[1]) == 0) {
      return 1; // pusty string
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
    int n = arg;
    cout << n << " ";
    vector<int> data;
    for(int i = 0; i < n; ++i)
      data.push_back(arrayRand(n));
    sort(data.begin(), data.end()); 
    for (auto& e : data) {
      cout << e << " ";
    }
    int valueIndex;
    if(strcmp(argv[2], "-l") == 0) {
      valueIndex = indexRand((int)(n/100));
    }
    else if(strcmp(argv[2], "-h") == 0) {
      valueIndex = n - indexRand(n/100) - 1;
    }
    else if(strcmp(argv[2], "-m") == 0) {
      valueIndex = (n/2) - (n/200) + indexRand(n/100);
    }
    else if(strcmp(argv[2], "-r") == 0) {
      valueIndex = indexRand(n);
    }
    else if(strcmp(argv[2], "-o") == 0) {
      valueIndex = -1;
    }
    else {
      cout << "Wywołanie: ./generator_binary <number> <mode>" << endl;
      cout << "Tryby <mode> :" << endl;
      cout << "-l - wartość znajdująca się blisko początku tablicy" << endl;
      cout << "-h - wartość znajdująca się blisko końca tablicy" << endl;
      cout << "-m - wartość znajdująca się blisko środka tablicy" << endl;
      cout << "-r - wartość znajdująca się w losowym miejscu tablicy" << endl;
      cout << "-o - losowa wartość nie znajdująca się w tablicy" << endl;
      return 0;
    }
    int value;
    if(valueIndex >= 0) {
      value = data.at(valueIndex);
    }
    else {
      value = arrayRand(n);
        while(binary_search(data.begin(), data.end(), value)) {
          value = arrayRand(n);
        }
    }
    cout << value;
  }
  else {
    cout << "Wywołanie: ./generator_binary <number> <mode>" << endl;
    cout << "Tryby <mode> :" << endl;
    cout << "-l - wartość znajdująca się blisko początku tablicy" << endl;
    cout << "-h - wartość znajdująca się blisko końca tablicy" << endl;
    cout << "-m - wartość znajdująca się blisko środka tablicy" << endl;
    cout << "-r - wartość znajdująca się w losowym miejscu tablicy" << endl;
    cout << "-o - losowa wartość nie znajdująca się w tablicy" << endl;
  }
}