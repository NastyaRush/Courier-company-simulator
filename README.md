# Courier-company-simulator

Compile program with g++:

  g++ Firm.cpp Storage.cpp updated_delivery_simulator.cpp Garage.cpp Test.cpp Map_info.cpp
  
Then run:

  chmod +x a.out;./a.out

Milestones:

1) Zdefiniowanie podstawowych klas.
2) Zdefiniowanie atrybutów i metod podstawowych klas.
    Podstawowe klasy to klasy, nad którymi wykonują
    operacje inne klasy, to znaczy klasy sterujące.
3) Wymyślenie algorytmu działania programu.
    Jest to najtrudniejsza część realizacji programu
    ponieważ ten algorytm musi rozwiązywać problem
    komiwojażera uwzględniając róźne właściwości.
4) Zdefiniowanie klas sterujących podstawowymi klasami na podstawie algorytmy.
5) Realizacja programu.
6) Przemyślenie i tworzenie programów testujących.


Założenia projektu:

• przedstawienie działania firmy kurierskiej, która za pomoca różnych pojazdów rozwozi przesyłki między miejscami w mieście i
między kilkoma miastami

• symulacja przesyłu paczek i ruchu pojazdy oraz przesyłek uwzględniając właściwości pojazdów i miast, przy czym żeby paczki byli przesłane najszybciej i najtaniej


Założenia programu:

1) Możliwość dodania i usunięcia paczki mającej nazwę, miejsce dostawy i objętość do przesyłu.
2) Możliwość dodania i usunięcia pojazdu mającego nazwę, prędkość, pojemność, ilość zużycia paliwa na 100 km jazdy i wynagrodzenie kierowcy.
3) Wybór optymalnej drogi do dostarczenia większej ilości paczek przy niższym koszcie.
4) Tekstowa symulacja ruchu pojazdów i dostarczenia przesyłek.


Klasy:

• Klasa Paczka (Package):

Atyrybuty podawane są z wejścia (nadanie paczki - add package) przez użytkownika:
nazwa (name), miejsce dostawy (destination) objętość (size, żeby program wiedział jaki pojazd wystosować).


• Klasa Pojazd (Vehicle):

Atyrybuty podawane są z wejścia (nadanie pojazdu - add vehicle) przez użytkownika:
nazwa (name), prędkość (speed), pojemność (capacity), zużycie paliwa (gas_consumption),
wynagrodzenie kierowcy prowadzącego ten pojazd (drivers_salary). Ostatnie cztery atrybuty
są potrzebne do późniejszego obliczenia kosztów dostawy do innych miast.


• Klasa Firma (Firm):

Klasa zarządzająca klasami Package i Vehicle.

Atrybuty:
1) Nazwa i indeks głównego miasta
2) Nazwy miast dostawy
3) Indeksy miast
4) Nazwy punktów dostawy w głównym mieście
5) Indeksy punktów dostawy
6) Odległości między miastami
7) Lista paczek do dostawy w punkty dostawy głównego miasta
8) Lista paczek do dostawy w inne miasta
9) Lista pojazdów

Metody:
1) Dodanie paczki (add_package)
2) Dodanie pojazdu (add_vehicle)
3) Wyświetlanie listy paczek (show_packages_list)
4) Wyświetlanie listy pojazdów (show_vechicles_list)
5) Wyświetlanie listy (miejsc dostawy lub miast) (show_list)
6) Rozpoczęcie dostawy do punktów dostawy w głównym mieście (start_delivery_for_main_city)
7) Rozpoczęcie dostawy do innych miast (start_delivery_for_cities)
8) Wyświetlanie informacji o procesie dostawy (delivering)
9) Obliczenie przebytej odległości (calculate_way)
10) Obliczenie kosztu podróży (calculate_cost)
11) Reorganizacja miejsc dostawy do odwiedzenia (reorganize_destinations)
12) Wybór pojazdu (choose_vehicle)
13) Zbieranie indeksów punktów dostawy do odwiedzenia (collect_destinations)
14) Usuwanie pojazdu (delete_vehicle)
15) Przejście do menu głównego (main_menu)


Szczegóły realizacji:

Do znalezienia optymalnej drogi między miastami wykorzystywany jest algorytm najbliższego sąsiada.
Do tego istnieje dwuwymiarowa tablica, która zawiera odległości między wszystkimi miastami w programie.
Nie udało się zrealizować klasę Delivery ze względu na złożoną komunikację pomiędzy nią a klasą Firm,
więc będzie ona zrealizowana w ramach następnego zadania.

W ciągu realizacji programu zostało uznane że klasa Miasto (City) i dziedziczenie od klasy Vehicle
(które były płanowane do zrobienia) są zbędne, bo nadmiarowo komplikują program.


Korzystanie z programu:

Ten program jest symulacją działania firmy kurierskiej, która dostarcza paczki z Warszawy
(oznaczoną jako główne miasto) do Krakowa, Gdańska, Białostoku i Wrocławia oraz do 4 punktów dostawy w Warszawie.

Przed tym jak zorganizować dostawę trzeba dodać pojazdy i paczki do dostawy.
Po to w menu głównym znajdują się odpowiednie pozycje ("Add vehicle" i "Add package" odpowiednio).
Te funkcje wymagają wprowadzenia pewnych danych od użytkownika, bo od nich zależy dalsze działanie programu.
Przy dodaniu paczki trzeba wprowadzić indeks punktu docelowego dostawy, indeksy każdego możliwego
punktu dostawy są wyświetlane odrazu po wyborze funkcji dodania paczki, także wszystkie miasta i punkty dostawy
z ich indeksami można zobaczyć wybierając odpowiednie pozycje w głównym menu
("Show list of delivery points" lub "Show list od cities"). Po dodaniu pojazdów i paczek można
zorganizować dostawę do głównego miasta ("Organize delivery for main city") lub do innych miast
("Organize delivery for cities") wybierając odpowiednią pozycje z menu. Także w programie są funkcje
usunięcia pojazdu ("Delete vehicle"), pokazania listy pojazdów, paczek do dostawy w punkty dostawy
i w główne miasto ("Show list of vehicles", "Show packages for main city" i " Show packages for cities" odpowiednio)
i wyjścia z programu ("Exit from program").

Wszystkie wprowadzane liczbowe wartości powinny być integerami, wartości nazw powinny być bez spacji.
Niektóre uwagi na kont używania programu można zobaczyć wywołując opcje "Information".
    
    
    
Wprowadzone zmiany:

1) Dodane klasy Package_for_city i Package_for_cities które dziedziczą po klasie Package.
2) Dodana klasa Garage, która przechowuje wewnętrzną szablonową klasę Vehicle i listę wskaźników na obiekty klasy Vehicle,
które są umieszczone w pamięci dynamicznej. Także w klasie Garage są funkcje do reprezentacji listy obiektów klasy
Vehicle, do ich tworzenia (i umieszczenia ich w pamięci dynamicznej) i do ich usuwania (i zwolnienia pamięci dynamicznej
którą oni zajmowali). Usuwanie obiektów klasy Vehicle i ich wskaźników jest też przed końcem programu, ponieważ jeżeli
nie zwolnić pamięć, którą oni zajmują, może wystąpić wyciek pamięci.
3) Dodana klasa Storage, która przechowuje wewnętrzną klasę Package i listę obiektów klasy Package.
Także w klasie Storage są funkcje do tworzenia i do reprezentacji listy obiektów klasy Package.
4) Została stworzona klasa Map_info, która przechowuje informacje o miastach, odległościach pomiędzy nimi i punktach dostawy.
5) Funkcje wyświetlania listy paczek, wyświetlania informacji o dostawie, wyboru pasującego pojazdu, wyznaczenia miejsc
do odwiedzenia stali się szablonowymi (ponieważ teraz mają przyjmować jako argumenty obiekty róznych klas).
6) Tym razem udało się dorzucić plik na gitlab, niewiadomo z czym jest związane to że czasami zamiast się wrzucić poprostu
otwiera się w przeglądarce jako tekst.
7) Dodane testy do funkcji:
 reorganize_destination,
 calculate_cost,
 calculate_way,
 choose_vehicle,
 collect_destinations 
 (bo oni stanowią główną część algorytmu programu i nie potrzebują wprowadzenia danych od użytkownika).
 Te testy wywołują się przed zakończeniem programu i wypisują do użytkownika odpowiednie komunikaty.
 W testach do testowanych funkcji są wprowadzane rózne dane symulujące różne sytuacje występujące w programie.


Przy implementacji tego zadania pojawili się pewne problemy:

1) Przy próbie umieszczenia w innym pliku nawet dość prostej klasy pojawią się błędy, im klasa jest bardziej skomplikowana,
tym więcej błędów. Ale wędług prowadzącego przedmiot to nie jest obowiązkowe.
3) Nie udało się zrealizować klasę przechowującej funkcje dostawy z powodu błędów przy próbie z obiektu klasy Firm
skierować do niej wskaźnik na aktualny obiekt Firm.


Płanowane są:

1) Rozłączenie klaśow do oddzielnych plików.
2) Obsługa wyjątków.

Uwagi na kont realizacji:

1) W niektórych funkcjach jest dużo argumentów po to żeby nie definiować kilka bardzo podobnych funkcji (zasada DRY).
2) Lista z odległościami od poszególnych miejsc jest wbudowana w program ponieważ przy możliwości dodania nowego miasta
trzeba wprowadzać odległość od niego do każdego już znajdującego w liście miasto, to bardzo komplikuje program i wymaga
wprowadzenia dużej ilości danych od użytkownika.

Wprowadzone zmiany:

1) Symulacja przebycia drogi przy dostawie do innych miast
2) Przy dodaniu paczki lub pojazdu: 
obsługa błędów wprowadzenia nieprawidłowych danych (wprowadzenie ujemnej wartości lub zera w tych miejscach gdzie to jest zabronione),  
obsługa błędów wprowadzenia liter zamiast liczb
3) Zapis informacji o paczkach i pojazdach do plików i możliwość późniejszego wczytania tych danych.
4) Rozłączenie projektu na kilka plików.
