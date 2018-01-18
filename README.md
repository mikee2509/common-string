# Wspólny napis
Michał Sieczkowski   
Analiza Algorytmów, semestr 17Z


## Opis problemu
> Dany jest skończony zbiór **S={s1, s2, …, sm}** napisów długości **n** nad alfabetem **Σ={0,1,∗}**. Odnaleźć napis **x=x1x2…xn** nad alfabetem **Σ1={0,1}** taki, że dla każdego **sj ∈ S** mamy zgodność **x** oraz **sj** na co najmniej jednej pozycji. Należy porównać rozwiązanie dokładne z heurystyką.


## Budowanie
Aby zbudować program należy wykonać poniższe komendy. CMake automatycznie pobierze framework Google Test.
```
cd common-string
mkdir cmake-build-release && cd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```


## Uruchamianie
W katalogu `cmake-build-release` pojawią się następujące pliki wykonywalne:
* `AAL`
* `AALtests`
* `AALgenerator`

### AAL
Główny program korzystający z dwóch algorytmów rozwiązujących zadany problem: algorytm typu brute-force oraz heurystyka.

**Dostępne są 4 tryby wykonania:**
* `AAL -t1 [-i]` - Wczytaj dane ze strumienia wejściowego, wypisz wyniki do strumienia wyjściowego
* `AAL -t2 [-i] <gen_options>` - Generuj losowe dane, wypisz wyniki do strumienia wyjściowego
* `AAL -t3 <gen_options> <test_params>` - Generuj losowe dane, wykonaj pomiary czasu wykonania, wypisz wyniki do strumienia wyjściowego
* `AAL -t4 -r NUM_RUNS` - Wczytaj dane ze strumienia wejściowego, wykonaj pomiary czasu wykonania, wypisz wyniki do strumienia wyjściowego

Opcjonalny argument:
* `-i` - Uruchom heurystykę w trybie interaktywnym

Ustawienia generatora `<gen_options>`:
* `-n STRING_LEN` - Długość generowanych napisów
* `-m NUM_STRINGS` - Liczba generowanych napisów

Parametry testów `<test_params>`:
* `-k NUM_GEN_SET` - Liczba różnych ustawień generatora
* `-step_n INC_STR_LEN` - Przyrost w długości generowanych napisów
* `-step_m INC_NUM_STR` - Przyrost w liczbie generowanych napisów
* `-r NUM_RUNS` - Liczba testowanych instancji problemu dla każdego ustawienia generatora

### AALtests
Uruchamiane są testy parametryczne:
* sprawdzające poprawność wyników heurystyki
* pokazujące wskaźnik sukcesu dla różnych wielkości problemu

### AALgenerator
Generator danych testowych na potrzeby algorytmu.

**Użycie:**
* `AALgenerator -g1 STRING_LEN NUM_STRINGS` - Generuj dane o zadanych parametrach, wypisz do strumienia wyjściowego

Ustawienia generatora:
* `STRING_LEN` - Długość generowanych napisów
* `NUM_STRINGS` - Liczba generowanych napisów


## Dane wejściowe

Dane testowe muszą być zapisane w sposób analogiczny do przykładu poniżej. Program waliduje poprawność danych i automatycznie określa długość i liczbę napisów.
```
0*011*11
00*1*111
*0000*10
**10*11*
1*0*0*1*
```

Przykładowe dane testowe można znaleźć w katalogu [`test_data`](test_data/). 


## Algorytmy

### Rozwiązanie dokładne (brute-force):
1. Inicjalizuj klucz o długości n samymi zerami. Mamy 2^n możliwości, w najgorszym wypadku trzeba będzie sprawdzić każdą z nich.
2. Sprawdzaj po kolei wszystkie napisy ze zbioru, w momencie gdy znajdziesz w napisie literę pasującą do klucza przejdź do następnego wyrazu. W przypadku gdy żadna litera w wyrazie nie pasuje, zmień klucz i rozpocznij sprawdzanie od nowa. Zmiana klucza polega na zwiększeniu jego wartości o 1 (traktowany jest jak liczba binarna).
3. Jeżeli w każdym wyrazie znaleziono pasującą literę, aktualny klucz jest szukanym rozwiązaniem. Jeżeli sprawdzono już wszystkie warianty klucza i za każdym razem, któryś wyraz nie pasuje - rozwiązanie nie istnieje.

### Rozwiązanie heurystyczne:
1. Zainicjalizuj klucz do wartości pierwszego wyrazu ze zbioru. Dla każdej pozycji w kluczu zapamiętywana będzie informacja, które wyrazy pasują na danej pozycji (mają taką samą literę co klucz na danej pozycji) - nazwiemy to 'pamięcią klucza'. Dla każdego wyrazu będzie zapamiętywana ilość liter, które pasują do klucza - nazwiemy to 'pamięcią wyrazu'.
2. Sprawdzaj kolejno wyrazy ze zbioru. Dla każdego z nich aktualizuj 'pamięć klucza' oraz 'pamięć wyrazu'. Gdy co najmniej jedna litera w wyrazie pasuje do klucza, przejdź do następnego wyrazu. Gdy żadna litera nie pasuje rozpoczynij procedurę zmiany klucza, a następnie przejdź do następnego wyrazu. Gdy sprawdzone są już wszystkie wyrazy aktualny klucz jest szukanym rozwiązaniem.

* Procedura zmiany klucza:
   1. Rozpatrywana będzie zmiana klucza na tylko tych pozycjach, które w niepasującym wyrazie mają 1 lub 0.
   2. Znajdź korzystając z 'pamięci klucza' na której literze w kluczu polega najmniej wyrazów, tzn. która litera w kluczu ma najmniej pasujących wyrazów na tej pozycji.
   3. Przejdź kolejno po tych wyrazach i sprawdź korzystając z 'pamięci wyrazów' czy każdy z nich ma co najmniej 2 pasujące do klucza litery. Jeżeli tak to zmień literę klucza na tej pozycji, zaktualizuj obie 'pamięci' (przechodząc po wszystkich rozpatrzonych do tej pory w pkt 2 algorytmu wyrazach, ale tylko na jednej pozycji) i wyjdź z procedury. Jeżeli nie, to wyklucz tą pozycję i przejdź do kroku 2 procedury. Gdy sprawdzono już wszystkie pozycje w kluczu i żadnej nie da się zmienić zakończ algorytm - heurystyka nie znalazła rozwiązania.

W kodzie programu 'pamięć klucza' reprezentuje zmienna `matchingStrings`, a 'pamięć wyrazu' zmienna `matchingLetters`.

## Struktura katalogów
Pliki źródłowe:
* [`main.cpp`](main.cpp) - główny program
* [`DataTypes.h`](DataTypes.h) - plik nagłówkowy z definicjami wykorzystywanych typów danych
* [`algorithm/`](algorithm/) - klasy realizujące algorytmy i pomiar czasu
* [`data/`](data/) - klasy realizujące strukture danych wykorzystywaną przez algorytm i generator danych
   * [`generator_main.cpp`](data/generator_main.cpp) - program generatora
* [`tests/`](tests/) - testy algorytmów

Dane testowe:
* [`test_data/`](test_data/)

