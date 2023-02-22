//Marek Świergoń 261750 L1Z2
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

struct timeval tvalBefore, tvalAfter;

struct ElementListy {
  int wartosc;
  struct ElementListy* poprzedni;
  struct ElementListy* nastepny;
};

typedef struct ElementListy* Lista;

Lista nowaLista(int i) {
  Lista nowa = malloc(sizeof(struct ElementListy));
  nowa->wartosc = i;
  nowa->poprzedni = nowa;
  nowa->nastepny = nowa;
  return nowa;
}

void dodajPoczatek(Lista* lista, int wart) {
  if(*lista == NULL) {
    Lista nowy = nowaLista(wart);
    *lista = nowy;
  }
  else {
    Lista nowy = nowaLista(wart);
    nowy->nastepny = *lista;
    nowy->poprzedni = (*lista)->poprzedni;
    (*lista)->poprzedni->nastepny = nowy;
    (*lista)->poprzedni = nowy;
    *lista = nowy;
  }
}

void wyswietlElementy(Lista lista) {
  if(lista == NULL) {
    printf("lista pusta\n");
  }
  else {
    Lista pomoc = lista;
      printf("%d\n", pomoc->wartosc);
    while(pomoc->nastepny != lista) {
      pomoc = pomoc->nastepny;
      printf("%d\n", pomoc->wartosc);
    }
  }
}

bool searchWithoutMove(Lista lista, int wart) {
  if (lista == NULL) {
    printf("lista pusta!");
    return false;
  }
  Lista temp = lista;
  while(lista->nastepny != temp) {
    if(lista->wartosc == wart) {
      return true;
    }
    lista = lista->nastepny;
  }
  return false;
}

bool searchWithMove(Lista* lista, int wart) {
  if (*lista == NULL) {
    printf("lista pusta!");
    return false;
  }
  Lista temp = *lista;
  while((*lista)->nastepny != temp) {
    if((*lista)->wartosc == wart) {
      return true;
    }
    (*lista) = (*lista)->nastepny;
  }
  return false;
}

//przechodze kolejno po elementach listy, zapamietuje kolejny i usuwam obecny
void usunListe(Lista* lista) {
  Lista mem = (*lista);
  if(*lista!=NULL) {
    Lista temp;
    do {
      temp = (*lista)->nastepny;
      printf("usuwam element o kluczu: %d\n", (*lista)->wartosc);
      free(*lista);
      *lista = temp;
    } while(*lista != mem);
    *lista = NULL;
  }
}

//funkcja merge laczy obie listy - wskazanie na element listy lista_a i lista_b
//po wywolaniu merge(lista_a, lista_b) dzialaja wewnatrz duzej listy ab
void merge(Lista lista_a, Lista lista_b) {
  lista_a->nastepny->poprzedni = lista_b->poprzedni;
  lista_b->poprzedni->nastepny = lista_a->nastepny;
  lista_a->nastepny = lista_b;
  lista_b->poprzedni = lista_a;
}

int main() {

  //Test funkcji merge, wyswietlania elementow i wyszukiwania
  printf("Próba wyswietlenia elementów listy pustej:\n");
  Lista lista_a = NULL;
  wyswietlElementy(lista_a);
  printf("\n");
  dodajPoczatek(&lista_a, 6);
  dodajPoczatek(&lista_a, 5);
  dodajPoczatek(&lista_a, 4);
  dodajPoczatek(&lista_a, 3);
  printf("Elementy listy a:\n");
  wyswietlElementy(lista_a);
  printf("\n");

  Lista lista_b = nowaLista(10);
  dodajPoczatek(&lista_b, 9);
  dodajPoczatek(&lista_b, 8);
  dodajPoczatek(&lista_b, 7);
  printf("Elementy listy b:\n");
  wyswietlElementy(lista_b);
  printf("\n");

  merge(lista_a, lista_b);

  printf("Elementy złączenia ab:\n");
  wyswietlElementy(lista_a);
  printf("\n");  

  searchWithoutMove(lista_a, 6);
  printf("Elementy listy ab po wyszukiwaniu elementu o kluczu 6 bez (docelowego!) przesuniecia na element:\n");
  wyswietlElementy(lista_a);
  printf("\n");
  searchWithMove(&lista_a, 6);
  printf("Elementy listy ab po wyszukiwaniu elementu o kluczu 6 z docelowym przesunieciem na element:\n");
  wyswietlElementy(lista_a);
  printf("\n");
  printf("Elementy listy ab po wyszukiwaniu elementu o kluczu 6 po raz drugi z\n");
  printf("docelowym przesunieciem na element (brak zmian):\n");
  searchWithMove(&lista_a, 6);
  wyswietlElementy(lista_a);
  printf("\n");
  searchWithMove(&lista_a, 8);
  printf("Elementy listy ab po wyszukiwaniu elementu o kluczu 8 z docelowym przesunieciem na element:\n");
  wyswietlElementy(lista_a);


  //TESTOWANIE SZYBKOŚCI DOSTĘPU DO ELEMENTÓW
  //1. SZYBKOŚĆ DOSTĘPU W ZALEŻNOŚCI OD ODLEGŁOŚCI


  FILE *out_file = fopen("wyniki_zadanie3.txt", "w");

  //wstawienie 1000 elementów - o wartosciach posortowanych rosnąco [0,...,999]
  Lista lista = nowaLista(999);
  for(int i = 998; i>=0; i--) {
    dodajPoczatek(&lista, i);
  }

  int suma = 0;
  double sredni_czas = 0.0;


  //TEST CZASU DOSTĘPU DO TEGO SAMEGO ELEMENTU (dla funkcji z przesuwaniem - przesunięcie na dany
  //element raz i potem za każdym kolejnym razem bezposredni dostep)
  //powtarzam test 1000 razy dla elementow [0, 100, 200, ..., 900]
  fprintf(out_file, "Test sredniego czasu dostepu do tego samego elementu dla funkcji przesuwajacej liste na szukany element\n");
  fprintf(out_file, "1000 powtorzen dla kazdego klucza i, i=0,100,...,900 (i, sr_czas[ms]):\n");
  for (int i = 0; i<1000; i += 100) {
    for (int j = 0; j<1000; j++) {
      gettimeofday (&tvalBefore, NULL);
      searchWithMove(&lista, i);
      gettimeofday (&tvalAfter, NULL);
      suma += ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L+tvalAfter.tv_usec) - tvalBefore.tv_usec;
    }
    sredni_czas = (double)suma/1000.0;
    fprintf(out_file, "%d;%lf\n", i, sredni_czas);
    sredni_czas = 0.0;
    suma = 0;
  }


  //TEST CZASU DOSTEPU DO LOSOWEGO ELEMENTU (dla funkcji z przesuwaniem - choc tu bez znaczenia)
  //10000 powtorzen
  fprintf(out_file, "\nTest sredniego czasu dostepu do losowego elementu (1000 powtorzen) [ms]:\n");
  srand(time(NULL));
  for (int i = 0; i<1000; i++) {
    gettimeofday (&tvalBefore, NULL);
    searchWithMove(&lista, (rand()%1000));
    gettimeofday (&tvalAfter, NULL);
    suma += ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L+tvalAfter.tv_usec) - tvalBefore.tv_usec;
  }
  sredni_czas = (double)suma/1000.0;
  fprintf(out_file, "%lf\n", sredni_czas);

  printf("\n\nUsuwam liste a element po elemencie:\n");
  usunListe(&lista_a);
  printf("Czy zawartosc listy a zostala usunieta?\n");
  wyswietlElementy(lista_a);
  return 0;
}

//WNIOSEK:
//KIEDY UŻYWAMY FUNKCJI Z WYSZUKIWANIEM ELEMENTU Z PRZESUNIECIEM NA NIEGO,
//MAMY BARDZO SZYBKI (BEZPOSREDNI) DOSTEP DO TEGO SAMEGO ELEMENTU Z KAŻDYM KOLEJNYM RAZEM.
//DZIEKI TEMU CZAS WIELOKROTNEGO DOSTEPU DO TEGO SAMEGO ELEMENTU JEST ZNACZNIE NIZSZY
//NIZ CZAS WIELOKROTNEGO DOSTEPU DO ZA KAZDYM RAZEM INNEGO ELEMENTU (PRZYPADEK Z LOSOWYM DOSTEPEM).

//(uwaga, czasem można oczywiscie wylosowac ten sam klucz, ale jest to rzadkie, mówimy o przypadku średnim)