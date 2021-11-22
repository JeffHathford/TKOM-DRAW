# TKOM-DRAW

Kompilacja interpretera:
g++ \*.cpp -o <**nazwa_pliku_wynikowego**>

Uruchamianie (przyjmując nazwę pliku inter.exe):
./inter.exe <**tryb wyświetlania**> <**nazwa pliku do wczytania**>
**lub**
./inter.exe test

Tryb wyświetlania (domyślnie 1):
  0 - moduł lexera nie wypisuje informacji
  1 - moduł wypisze na ekran tokeny w takiej kolejności, w jakiej przekazałby je parserowi
  2 - moduł wypisze dodatkowo informacje o przetwarzanych słowach, indeksy tokenów w kodzie oraz indeks obecnie przetwarzanego znaku
  
Wczytywanie pliku:
  Gdy program otrzyma poprawną nazwę pliku umieszczonego w tym samym katalogu, przetworzy on na tokeny kod źródłowy znaleziony w pliku zamiast czytać dane z klawiatury.
  Przewidziane jest jedynie uruchamianie plików tekstowych.

Parametr "test":
  Uruchomienie programu z parametrem "test" spowoduje, że program przejdzie jedynie przez funkcję zawartą w pliku **unit_tests.cpp** i wykona testy jednostkowe. 
