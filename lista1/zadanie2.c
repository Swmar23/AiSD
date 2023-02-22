//Marek Świergoń 261750 L1Z2
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

struct timeval tvalBefore, tvalAfter;

struct ElementListy {
  int wartosc;
  struct ElementListy* nastepny;
};

typedef struct ElementListy* Lista;

Lista nowaLista(int i){
  Lista nowa = malloc(sizeof(struct ElementListy));
  nowa->wartosc = i;
  nowa->nastepny = NULL;
  return nowa;
}

void wyswietlElementy(Lista lista) {
  if(lista == NULL) {
    printf("lista pusta\n");
  }
  while(lista != NULL) {
    printf("%d\n", lista->wartosc);
    lista = lista->nastepny;
  }
}

Lista dodajElementPoczatek(Lista lista, int wart) {
  Lista nowa = nowaLista(wart);
  nowa->nastepny = lista;
  return nowa;
}

void dodajElementKoniec(Lista* lista, int wart) {
  Lista nowa = nowaLista(wart);
  Lista pomocnicza;
  if((*lista) == NULL) {
    (*lista) = nowa;
  }
  else {
    pomocnicza = *lista;
    while(pomocnicza->nastepny != NULL) {
      pomocnicza = pomocnicza->nastepny;
    }
    pomocnicza->nastepny = nowa;
  }
}

int getWartosc(Lista lista, int indeks) {
  int i = 0;
  while(lista != NULL) {
    if(i == indeks) {
      return lista->wartosc;
    }
    lista = lista->nastepny;
    i++;
  }
  printf("error: brak elementu o indeksie i=%d", i);
  return -1;
}

void usunListe(Lista* lista) {
  Lista temp;
  while(*lista != NULL) {
    temp = (*lista)->nastepny;
    free(*lista);
    *lista = temp;
  }
}

//funkcja merge laczy obie listy - wskazanie na element listy lista_a i lista_b
//po wywolaniu merge(lista_a, lista_b) dzialaja wewnatrz duzej listy ab
void merge(Lista lista_a, Lista lista_b) {
  while(lista_a->nastepny != NULL) {
    lista_a = lista_a->nastepny;
  }
  lista_a->nastepny = lista_b;
}

int main() {
  //z braku lepszego generatora pseudolosowego - rand, niepolecany
  srand(time(NULL));
  Lista lista = nowaLista(rand()%10000);
  for(int i = 0; i<1000; i++) {
    dodajElementKoniec(&lista, rand()%10000);
  }
  //wyswietlElementy(lista);
  FILE *out_file = fopen("wyniki_zadanie2.txt", "w");
  fprintf(out_file, "Test sredniego czasu dostepu do elementow o indeksach i = 0,50,...,950 (i;sr_czas[ms]):\n");
  long suma;
  int element = -1;
  double sredni_czas = -1.0;
  for(int i = 0; i < 1000; i += 50) {
    suma = 0;
    for(int j=0; j < 100; j++) {
      gettimeofday (&tvalBefore, NULL);
      element = getWartosc(lista, i);
      gettimeofday (&tvalAfter, NULL);
      suma += ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L+tvalAfter.tv_usec) - tvalBefore.tv_usec;
      element = -1;
    }
    sredni_czas = (double)suma/100.0;
    fprintf(out_file, "%d;%lf\n",i,sredni_czas);
  }

  //TEST FUNKCJI MERGE
  Lista lista_a = nowaLista(rand());
  for(int i = 0; i<5; i++) {
    dodajElementKoniec(&lista_a, rand()%1000);
  }
  printf("Elementy listy a:\n");
  wyswietlElementy(lista_a);

  Lista lista_b = nowaLista(rand());
  for(int i = 0; i<3; i++) {
    dodajElementKoniec(&lista_b, rand()%1000);
  }
  printf("Elementy listy b:\n");
  wyswietlElementy(lista_b);

  merge(lista_a, lista_b);

  printf("Elementy złączenia ab:\n");
  wyswietlElementy(lista_a);

  usunListe(&lista);
  printf("\n\nCzy zawartosc listy zostala usunieta?\n");
  wyswietlElementy(lista);
  return 0;
}

//WNIOSEK:
//IM DALEJ ELEMENT, DO KTÓREGO CHCESZ MIEĆ DOSTĘP, LEŻY OD ELEMENTU
//POCZĄTKOWEGO LISTY, TYM DŁUŻSZY JEST CZAS POTRZEBNY DO UZYSKANIA
//ŻĄDANEGO ELEMENTU.

//CZAS TEN ROŚNIE LINIOWO (THETA(n), gdzie n to odleglosc elementu
//szukanego od elementu poczatkowego)