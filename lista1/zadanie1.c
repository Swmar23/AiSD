//Marek Świergoń 261750 L1Z1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// KOLEJKA LIFO - IMPLEMENTACJA STATYCZNA
struct Stos {
  int szczyt;
  int pojemnosc;
  int* s;
};

struct Stos* nowyStos(int poj) {
  struct Stos* stos = (struct Stos*)malloc(sizeof(struct Stos));
  stos->pojemnosc = poj;
  stos->szczyt = -1; // pusty stos
  stos->s = (int*)malloc(stos->pojemnosc * sizeof(int));
  return stos;
}

int czyPelny(struct Stos* stos) {
  if(stos->szczyt == (stos->pojemnosc - 1)) {
    return true;
  }
  return false;
}

int czyPusty(struct Stos* stos) {
  if(stos->szczyt == -1) {
    return true;
  }
  return false;
}

void dodaj(struct Stos* stos, int element) {
  if(czyPelny(stos)) {
    printf("Stos jest pełny!\n");
    return;
  }
  stos->szczyt++;
  stos->s[stos->szczyt] = element; 
  printf("Dodano element %d. (Stos LIFO)\n", element);
}

int zabierz(struct Stos* stos){
  if (czyPusty(stos)) {
    printf("Stos jest pusty! Zwracam liczbę -1 (error).\n");
    return -1;
  }
  int element = stos->s[stos->szczyt];
  stos->szczyt--;
  printf("Zabrano element %d. (Stos LIFO)\n", element);
  return element;
}

int podejrzyj(struct Stos* stos){
  if (czyPusty(stos)) {
    printf("Stos jest pusty! Zwracam liczbę -1 (error).\n");
    return -1;
  }
  int element = stos->s[stos->szczyt];
  return element;
}


// KOLEJKA FIFO - IMPLEMENTACJA STATYCZNA, CYKLICZNA (implementacja modyfikacji pseudokodu z notatek)
struct Kolejka {
  int poczatek;
  int koniec;
  int obecny_rozmiar;
  int pojemnosc;
  int* q;
};

struct Kolejka* nowaKolejka(int poj) {
  struct Kolejka* kolejka = (struct Kolejka*)malloc(sizeof(struct Kolejka));
  kolejka->pojemnosc = poj;
  kolejka->obecny_rozmiar = 0;
  kolejka->poczatek = kolejka->obecny_rozmiar; // pusta kolejka
  kolejka->koniec = poj - 1;
  kolejka->q = (int*)malloc(kolejka->pojemnosc * sizeof(int));
  return kolejka;
}

int czyKolejkaPelna(struct Kolejka* kolejka) {
  if(kolejka->obecny_rozmiar == kolejka->pojemnosc) {
    return true;
  }
  return false;
}

int czyKolejkaPusta(struct Kolejka* kolejka) {
  if(kolejka->obecny_rozmiar == 0) {
    return true;
  }
  return false;
}

void dodajDoKolejki(struct Kolejka* kolejka, int element) {
  if(czyKolejkaPelna(kolejka)) {
    printf("kolejka jest pełna!\n");
    return;
  }
  if (kolejka->koniec == (kolejka->pojemnosc - 1)) {
    kolejka->koniec = 0;
  }
  else {
    kolejka->koniec++;
  }
  kolejka->q[kolejka->koniec] = element;
  kolejka->obecny_rozmiar++;
  printf("Dodano element %d. (Kolejka FIFO)\n", element);
}

int zabierzZKolejki(struct Kolejka* kolejka){
  if (czyKolejkaPusta(kolejka)) {
    printf("Kolejka jest pusta! Zwracam liczbę -1 (error).\n");
    return -1;
  }
  int element = kolejka->q[kolejka->poczatek];
  if (kolejka->poczatek == (kolejka->pojemnosc - 1)){
    kolejka->poczatek = 0;
  }
  else {
    kolejka->poczatek++;
  }
  kolejka->obecny_rozmiar--;
  printf("Zabrano element %d. (Kolejka FIFO)\n", element);
  return element;
}

int podejrzyjKolejke(struct Kolejka* kolejka){
  if (czyKolejkaPusta(kolejka)) {
    printf("kolejka jest pusta! Zwracam liczbę -1 (error).\n");
    return -1;
  }
  int element = kolejka->q[kolejka->poczatek];
  return element;
}

int main() {
  struct Kolejka* kolejka = nowaKolejka(100);
  struct Stos* stos = nowyStos(100);
  printf("DODAWANIE 100 ELEMENTOW DO KOLEJKI I STOSU:\n");
  for(int i = 1; i<= 100; i++) {
    dodajDoKolejki(kolejka, i);
    dodaj(stos, i);
  }

  printf("\n\nProba przepelnienia kolejki i stosu:\n");
  //proba przepelnienia stosu i kolejki:
  dodajDoKolejki(kolejka, 2100);
  dodaj(stos, 37);

  printf("\n\nZABIERANIE ELEMENTOW Z KOLEJKI I STOSU:\n");
  for(int i = 1; i<= 100; i++) {
    zabierzZKolejki(kolejka);
    zabierz(stos);
  }

  printf("\n\nProba zabrania elementow z pustej kolejki i pustego stosu:\n");
  zabierzZKolejki(kolejka);
  zabierz(stos);
  return 0;
}
