# Binary-Internet-Protocol
Protokół binarny umożliwiający działania na liczbach


Projekt z przedmiotu Technologie Sieciowe.
Treść zadania:
Temat: Komunikacja pomiędzy klientem a serwerem (n:1), w oparciu o autorski protokół binarny.
Protokół:
 połączeniowy,
 wszystkie dane przesyłane w postaci binarnej,
 pole operacji o długości 2 bitów,
 pola liczb o długości 32 bitów,
 pole statusu o długości 4 bitów,
 pole identyfikatora o długości 6 bitów,
 dodatkowe pola zdefiniowane przez programistę.
Funkcje oprogramowania:
 nawiązanie połączenia,
 uzgodnienie identyfikatora sesji,
 wykonywanie operacji na trzech argumentach:
o 00 – odejmowanie,
o 01 – dzielenie,
o 2 inne, zdefiniowane przez programistę.
 zakończenie połączenia.
Inne:
 identyfikator sesji powinien być przesyłany w trakcie komunikacji,
 serwer powinien obsługiwać i rozróżniać wielu klientów jednocześnie

Zadanie wykonane wraz z Marcinem Siwińskim (https://github.com/msciasteczkowypotwor).
Wykonanie projektu nie byłoby możliwe bez pomocy Sloana Kelly'ego (https://www.youtube.com/user/sloankelly/videos).
