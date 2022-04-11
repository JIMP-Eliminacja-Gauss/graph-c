# PROGRAM GRAPH

Wiktor Nasierowski\
Adam Smerdzyński


## SPECYFIKACJA FUNKCJONALNA

### 1. Cel projektu
Stworzenie programu graph, generującego graf z możliwością wybrania przez użytkownika liczby kolumn lub wierszy, z którego ma się składać. Program losuje wartości wag krawędzi w grafie z przedziału domkniętego <x, y>, który może być wybrany przez użytkownika.  Graph umożliwia użytkownikowi wybór jednej z dwóch funkcji, która zostanie wykonana na już wygenerowanym grafie tj. sprawdzenie czy graf jest grafem spójnym oraz wyznaczenie najkrótszej ścieżki pomiędzy wierzchołkiem źródłowym, a innymi wierzchołkami. Program obsługuje również odczyt grafu z pliku o podanej przez użytkownika nazwie oraz zapis do plików wskazywanych przez użytkownika.

### 2. Opis funkcji udostępnianych przez program
1.	Generowanie grafu o zadanej liczbie wierszy i kolumn oraz o ważonych krawędziach.
    -	Wybór liczby wierszy i kolumn do wygenerowania.
    - Wybór przedziału, z którego losowane będą wagi krawędzi.
    - Wybór pliku, do którego wygenerowany graf zostanie zapisany.
    -	Określenie prawdopodobieństwa z jakim mają być generowane połączenia między wierzchołkami w grafie.

2.	Wczytywanie grafu z odpowiednio sformatowanego pliku.

3.	Wykonywanie operacji na grafie.
    -	Sprawdzenie spójności grafu.
    - Wyznaczenie najkrótszej ścieżki pomiędzy wierzchołkami.

### 3. Lista dostępnych flag sterujących programem

1. Generowanie grafu o zadanej liczbie wierszy i kolumn oraz o ważonych krawędziach.\
   \
   -r liczba_wierszy\
   Stwórz graf o podanej liczbie wierszy. Liczba wierszy musi być liczbą naturalną.\
   \
   -c liczba_kolumn\
   Stwórz graf o podanej liczbie kolumn. Liczba kolumn musi być liczbą naturalną.\
   \
   -x dolna_granica\
   Wylosowane wagi krawędzi nie będą mniejsze niż podana dolna granica. Dolna granica musi być liczbą rzeczywistą większą od 0. [domyślnie 1]\
   \
   -y górna_granica\
   Wylosowane wagi krawędzi nie będą większe niż podana górna granica. Górna granica musi być liczbą rzeczywistą nie mniejszą niż granica dolna. [domyślnie dolna_granica + 10]\
   \
   -w plik\
   Wygenerowany graf zostanie zapisany w podanym pliku.\
   \
   -d prawdopodobieństwo\
   Połączenia między wierzchołkami w grafie będą generowane z określonym prawdopodobieństwem z przedziału <0; 1>. [domyślnie 1]


2.	Wczytywanie grafu z odpowiednio sformatowanego pliku.\
    \
    -o plik\
    Program wczyta graf zapisany w podanym pliku.


3.	Wykonywanie operacji na grafie.\
	\
	-b [indeks_wierzchołka_źródłowego]\
Program sprawdzi, czy graf jest spójny. Przeszukiwanie grafu program rozpocznie od wskazanego wierzchołka źródłowego, który jest liczbą całkowitą nieujemną i zawiera się w grafie. [domyślnie wierzchołek 0]\
	\
  -p [indeks_wierzchołka_źródłowego]\
  Program wyznaczy najkrótsze ścieżki od podanego wierzchołka źródłowego do wszystkich innych wierzchołków grafu (o ile dla danego wierzchołka taka ścieżka istnieje) z poszanowaniem wag krawędzi i wypisze ich długości. Wskazane przez użytkownika wierzchołki są liczbami całkowitymi nieujemnymi oraz zawierają się w grafie.

### 4. Format w jakim program przyjmuje dane i w jakim je generuje
Format plików jaki obsługuje program to plik tekstowy, w którym w pierwszej linijce są liczby kolumn i wierszy, a w kolejnych linijkach zapisywane są indeksy wierzchołków i wagi krawędzi tych wierzchołków z wierzchołkiem o indeksie będącym numerem aktualnie odczytywanej linijki pliku, gdzie zaczynamy liczyć od 0.

```
Przykładowy plik dla grafu 2x2:
Linijka 0:			2 2
Linijka 1 (wierzchołek 0): 	1 :8.0	2 :5.0
Linijka 2: 			0 :8.0	3 :1.0
Linijka 3: 			0 :5.0	3 :9.0
Linijka 4:			1 :1.0	2 :9.0
```

Obok indeksu wierzchołka po dwukropku „:” podawana jest waga krawędzi.


### 5. Sytuacje wyjątkowe obsługiwane przez program
1.	Nieprawidłowe dane wejściowe – kod błędu: 1
2.	Brak praw do odczytu podanego pliku – kod błędu: 2
3.	Brak praw do pisania do pliku o podanej nazwie – kod błędu: 3
4.	Niewystarczająca ilość pamięci – brak wystarczającej ilości pamięci na zaalokowanie, kod błędu: 4
5.	Nieprawidłowy format pliku – kod błędu: 5











### Przykłady
1.	graph –r 100\
Wygenerowany graf będzie miał 100 wierszy.

2. graph –r 100 –c 100\
Wygenerowany graf będzie miał 100 wierszy oraz 100 kolumn.

3.	graph –r 100 –c 100 –x 1 –y 200 –w moj_graf.txt\
Wygenerowany graf o 100 wierszach i 100 kolumnach oraz o wagach krawędzi losowanych z przedziału <1, 200> zostanie zapisanych w pliku moj_graf.txt.

4.	graph –o graf_z_pliku.txt\
Program wczyta graf z pliku graf_z_pliku.txt.

5.	graph -o graf_z_pliku.txt -p 0\
Program wczyta graf z pliku graf_z_pliku.txt i wyznaczy najkrótszą ścieżkę od wierzchołka źródłowego o indeksie 0 do wszystkich innych wierzchołków






## SPECYFIKACJA IMPLEMENTACYJNA

### 1. Podział na pliki oraz ich struktura

Plik główny: main.c
Plik obsługujący operacje plikowe: file.c (file.h)
Plik obsługujący generowanie grafu: generator.c (generator.h)
Plik obsługujący operacje na grafie: algorithm.c (algorithm.h)
Plik odpowiedzialny za przetrzymywanie informacji o grafie: store.c (store.h)



### 2. Podział na funkcje
1.	Funkcje w pliku file.c:
    - (wskaźnik na strukturę) file_read – funkcja przyjmuje jako argumenty nazwę pliku, z którego ma odczytać graf, liczbę kolumn, liczbę wierszy. Wykorzystuje funkcję store_init (z pliku store.c), aby zaalokować potrzebną pamięć na struktury. Odczytuje graf z pliku i uzupełnia te struktury. Zwraca wskaźnik na strukturę opisującą graf w przypadku sukcesu lub NULL w przypadku niepowodzenia.
    - int file_create – funkcja przyjmuje jako argumenty nazwę pliku, wskaźnik na opis grafu. Tworzy plik (o nazwie podanej w argumentach), który zawiera opis grafu. Zwraca 0, jeżeli sukces, a w przeciwnym wypadku 1.

2.	Funkcje w pliku store.c:
    - (wskaźnik na strukturę) store_init – funkcja przyjmująca jako argument liczbę kolumn i liczbę wierszy grafu. Alokuje pamięć (rozwinięcie w punkcie 3. Używane struktury danych, rozdziału SPECYFIKACJA IMPLEMENTACYJNA), zwraca wskaźnik na strukturę opisującą graf w przypadku sukcesu bądź NULL w przeciwnym wypadku.
    - int store_add_edge – funkcja przyjmuje jako argumenty wskaźnik na początek miejsca w pamięci zajmowanego przez n (gdzie n – liczba wierzchołków grafu) struktur zawierających krawędzie grafu (rozwinięcie w punkcie 3. Używane struktury danych, rozdziału SPECYFIKACJA IMPLEMENTACYJNA),  indeks wierzchołka, na który przechodzimy, wagę tego przejścia, indeks wierzchołka, z którego przechodzimy. Alokuje pamięć na strukturę (jeżeli potrzeba) i ją uzupełnia o podane w argumentach wartości. Zwraca 0, jeżeli sukces, w przeciwnym wypadku 1.
    - (wskaźnik na strukturę) dijkstra_init – funkcja przyjmująca jako argument liczbę wierzchołków grafu. Alokuje pamięć (rozwinięcie w punkcie 3. Używane struktury danych, rozdziału SPECYFIKACJA IMPLEMENTACYJNA), zwraca wskaźnik na początek miejsca zajmowane w pamięci przez n (gdzie n – liczba wierzchołków grafu) zaalokowanych struktur w przypadku sukcesu bądź NULL w przeciwnym wypadku.
    - void store_free – funkcja przyjmująca jako argumenty wskaźnik na strukturę zawierającą opis grafu. Zwalnia zaalokowaną pamięć.

3.	Funkcje w pliku generator.c:
     - (wskaźnik na strukturę) generate – funkcja generująca graf o ustalonej liczbie kolumn oraz wierszy przez wypełnienie odpowiednich pól struktury. Wartości poszczególnych krawędzi są losowane z przedziału domkniętego <x, y>. Funkcja jako argumenty przyjmuje liczbę kolumn, wierszy oraz zarówno dolną jak i górną granicę przedziału    <x, y>. Zwraca wskaźnik na początek miejsca zajmowanego w pamięci przez n (gdzie n – liczba wierzchołków grafu)  zaalokowanych struktur w przypadku sukcesu, bądź NULL w przeciwnym wypadku.

4.	Funkcje w pliku algorithm.c:
    - int bfs - funkcja przyjmująca jako argument wskaźnik na opis grafu, wierzchołek startowy. Wykorzystuje algorytm bfs do sprawdzenia spójności grafu, zwraca 0 jeżeli graf jest spójny lub 1 jeżeli jest niespójny.
    - (wskaźnik na strukturę) dijkstra – funkcja przyjmująca jako argument wskaźnik na opis grafu, wierzchołek startowy. Wykorzystuje algorytm Dijkstry do wyznaczenia najkrótszej drogi od wierzchołka źródłowego do wszystkich innych (o ile taka droga istnieje).  Zwraca wskaźnik na miejsce zajmowane przez n struktur lub ustawia zmienną lastError na odpowiednią wartośći zwraca NULL w razie wystąpienia sytuacji wyjątkowej.



### 3. Używane struktury danych

W pliku store.c (funkcja store_init) alokowana będzie pamięć na strukturę opisującą graf, zawierającą liczbę wierszy i liczbę kolumn grafu oraz wskaźnik na początek miejsca zajmowanego przez n struktur opisujących krawędzie grafu przy czym każda z nich będzie zawierała wierzchołek, na który możemy przejść z wierzchołka o danym indeksie, wagę tego przejścia i wskaźnik na następną strukturę opisującą kolejną krawędź (jeżeli ma więcej krawędzi, w przeciwnym wypadku NULL).  W pliku store.c (funkcja dijkstra_init) również będzie alokowana pamięć na n struktur zawierających długość najkrótszej drogi od wierzchołka źródłowego do danego wierzchołka oraz indeks wierzchołka, z którego wcześniej poprowadzono krawędź do tego wierzchołka (który poprzedza przejście na ten wierzchołek najkrótszą drogą).
Przykładowo: dla wybranego wierzchołka źródłowego - 0, struktura odnosząca się do wierzchołka o indeksie 1 przechowuje długość najkrótszej drogi z wierzchołka źródłowego (0) do wierzchołka o tym indeksie i indeks wierzchołka, z którego wcześniej poprowadzono krawędź do aktualnego wierzchołka. (dla np. wierzchołka o indeksie 3 z obrazka poniżej po wykonaniu algorytmu Dijkstry będzie to 1, bo najkrótsza droga od wierzchołka 0 do wierzchołka 3 to 5 i jest to droga 0-1-3)
Źródło: https://medium.com/@tarcisioma/data-structures-7766d3f93c70







### 4. Język programowania użyty w programie
	
Językiem programowania używanym w programie jest język C w standardzie C99 (ISO/IEC 9899:1999).

