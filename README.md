<h1 align="center"> System Obsługi Hotelu</h1> <br>
<p align="center">
System Obsługi Hotelu (SOH) jest to projekt zaliczeniowy jednego z kursów na studiach. Ów projekt napisany jest w C++ przy pomocy Qt. Baza danych stworzona jest za pomocą SQliteStudio (format pliku to .db).
  <br>
  <b>Przedstawienie programu – https://youtu.be/zgWtCumOy2A</b>
</p>

## Logowanie
<p align="center">
<img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/logowanie.png"/><br><br>
Login i hasło to „a”. Jest to zaimplementowane w klasie logowanie.cpp (nie w bazie danych).
</p>

## Baza danych
<p align="center">
<img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/bazadanych.png"/><br><br>
Następnie po zalogowaniu pojawia się okno w celu wprowadzenia ścieżki do <a target="_blank" rel="noopener noreferrer" href =https://github.com/kacperpasnik/System-Obslugi-Hotelu/tree/master/baza>bazy danych</a>.
</p>

## Menu Główne
<p align="center">
<img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/menuglowne.png"/><br><br>
Jeżeli ścieżka do bazy danych została dodana prawidłowo, to w prawym górnym rogu okna powinnen pojawić się napis „Połączono z bazą danych”. W przeciwnym wypadku pojawi się napis „Brak połączenia z bazą danych”. <br>
Menu główne zawiera również aktualnie odświeżający się czas.
</p>

## Dodaj
<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/dodaj.png"/><br><br>
  W sekcji dodawania rezerwacji należy podać imię, nazwisko (pola nie mogą być puste), okres trwania rezerwacji oraz numer pokoju. <br>
  Program automtycznie wyszukuje w bazie danych czy podany okres w konkretnym pokoju jest wolny czy zarezerwowany.
</p>

## Pokaż
<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/pokaz.png"/><br><br>
  Ta sekcja pozwala nam na pokazanie rezerwacji danego pokoju. Można również wyszukać ją poprzez konkretne nazwisko.
</p>

## Sprawdź
<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/sprawdz.png"/><br><br>
  Tutaj możemy sprawdzić czy podczas jakiegoś okresu jest zajęty lub wolny pokój. Dodatkowa możliwość to zmiana lub usunięcie rezerwacji.
</p>

## Zmień
<p align="center">
 <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/zmien.png"/><br><br>  
W tym oknie można zmienić rezerwację. W tym celu należy znać ID rezerwacji.
</p>

## Usuń
<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/usun.png"/><br><br>   
W tym oknie można usunąć rezerwację. W tym celu należy znać ID rezerwacji.
</p>

## Wygląd bazy danych
<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/sqlite.PNG"/><br><br><img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/sqlite2.PNG"/><br><br><img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/sqlite3.PNG"/> <br> <br><img align="center" src="https://raw.githubusercontent.com/kacperpasnik/System-Obslugi-Hotelu/master/screens/sqlite4.PNG"/>
  <br><br>
Oprócz zwykłej tabeli (Klient) z danymi i informacjami o rezerwacji jakiegoś klienta, baza danych posiada również osobną tabelę o nazwie Pokoje (3 zdjęcie). Zapisywane są w niej poszczególne dane do każdego zarezerwowanego dnia w konkretnym pokoju, gdzie ów dzień (dzien_rezerwacji) oznacza ilość dni, które minęły od 01.01.2000. Za pomocą takich oznaczeń z łatwością można sprawdzać czy jakiś dzień jest już zarezerwowany.
</p>

## Zmiany

### Wersja 1.0:

### Wersja 2.0:

– dodano klasę BazaDanych, która przetrzymuje ścieżkę do bazy danych potrzebną dla wszystkich innych klas;<br>
– dodano możliwość podania ścieżki do bazy danych po zalogowniu;<br>
– naprawiono niektóre bugi.

### Wersja 2.1:

– usprawniono zamykanie bazy danych (w niektórych przypadkach było to pomijane);<br>
– usunięto bug zmiany rezerwacji w sekcji Pokaż i Sprawdź.
