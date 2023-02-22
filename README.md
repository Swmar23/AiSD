# AiSD - Algorytmy i Struktury Danych
Zbiorcze repozytorium rozwiązań zadań z przedmiotu Algorytmy i Struktury Danych. Kurs prowadzony przez dra inż. Zbigniewa Gołębiewskiego na kierunku Informatyka Algorytmiczna, Wydział Informatyki i Telekomunikacji Politechniki Wrocławskiej. Same zajęcia laboratoryjne prowadzone były przez dra Marcina Kika. Autorem zadań jest dr Marcin Kik.

Programy napisane w językach C i C++. Dodatkowo utworzyłem parę skryptów uruchamiających programy na potrzeby testów - napisane są one pod powłokę Linuksową. Ponadto działanie zadań zostało udokumentowanie programem `asciinema`. Instalacja programu: 

`sudo apt-get install asciinema` (na Ubuntu i innych dystrybucjach Debianowych). Szczegóły instalacji na innych systemach: [link](https://asciinema.org/docs/installation)

Aby wyświetlić sprawozdanie należy wprowadzić w terminalu polecenie

`asciinema play -i 0.05 nazwa_pliku.cast` (flaga -i decyduje o szybkości wyświetlania - im większa wartość, tym wolniejsze odtwarzanie)

## Lista 1
Implementacja kolejki FIFO, stosu (LIFO), listy jednokierunkowej wraz z funkcją `merge(lista l1, lista l2)` łączącą dwie listy. Implementacja dwukierunkowej listy cyklicznej wraz z funkcją `merge(lista l1, lista l2)` łączącą dwie listy. Testy złożoności wstawiania losowych elementów.

## Lista 2
Implementacja algorytmów sortowania: Insertion Sort, Merge Sort, Quick Sort. Implementacja generatorów na standardowe wyjście ciągów losowych kluczy, losowych ciągów posortowanych rosnąco albo malejąco. Specyfikacja generatorów w treści zadania 1. 

Testy średniej liczby porównań między kluczami [c(n)], przestawień kluczy [s(n)] dla ciągów generowanych generatorami oraz ilorazy c(n)/n i s(n)/n.

Algorytm Dual-Pivot Quicksort i testowanie ich implementacji. Propozycja własnego hybrydowego algorytmu sortowania (połączenie Quick Sort z Insertion Sort) i testowanie implementacji tego algorytmu.

## Lista 3
Implementacja algorytmów szukania statystyk pozycyjnych: Randomized Select i Select. Badanie liczby porównań i przestawień elementów tablic dla implementacji. Sprawdzenie wpływu liczby grup, na którą dzielona jest tablica w kroku wyszukiwania mediany median, na złożoność algorytmu Select (k-Select).

Algorytm rekurencyjnego wyszukiwania binarnego. Testy złożoności obliczeniowej algorytmu i porównanie wyników z teoretycznym rezultatem z Master Theorem.

Wykorzystanie algorytmu Select w algorytmie Quick Sort i Dual Pivot Quicksort. Testy implementacji analogiczne do tych z listy 2.

## Lista 4
Struktury drzewiaste: wersja podstawowa Binary Search Tree, Red-Black Binary Search Tree (drzewo czerwono-czarne), Splay Tree. Badanie złożoności obliczeniowej wstawiania elmentów z losowego ciągu lub losowego ciągu rosnącego (liczba porównań między kluczami, liczba odczytów i podstawień wskaźników, wysokość drzewa po każdej operacji). Analogiczne testy złożoności usuwania losowego ciągu ze struktur. Koszt zamortyzowany operacji dla Splay Tree.

## Lista 5
Implementacja kopca binarnego i algorytmu Heapsort operującego na tymże kopcu. Testy porównujące działanie algorytmu z algorytmami sortowania z listy 2.

Operacje kolejki priorytetowej dla kopca binarnego: `Insert(S, x)`, `Extract-Max(S)`. Testy złożoności wstawiania i usuwania elementów z kolejki. Demonstracja działania kolejki na małych danych (przedstawienie wizualne tablicy jako kopiec).

Algorytm wyszukiwania najdłuższego wspólnego podciągu dwóch ciągów (LCS, Longest Common Subsequence) - programowanie dynamiczne. Badanie złożoności obliczeniowej zaimplementowanego algorytmu LCS.
