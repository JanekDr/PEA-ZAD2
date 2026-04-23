Projektowanie efektywnych algorytmów Zadanie 2

# 1. Temat

Zadanie polega na:
- Opracowaniu i implementacji algorytmu opartego
    o metodę podziału i ograniczeń (branch-and-bound)
    z trzema metodami przeglądania przestrzeni rozwią-
    zań.
- Wykonaniu badania złożoności obliczeniowej i efek-
    tywności algorytmu w każdym z wariantów do roz-
    wiązania problemu komiwojażera (TSP).

# 2. Cel zadania

Należy zaimplementować (samodzielnie) trzy me-
tody przeglądania przestrzeni rozwiązań:

- przeszukiwanie wszerz (breadth-first-search – BFS),
- przeszukiwanie wgłąb (depth-first-search – DFS),
- przeszukiwanie najniższy koszt lowest-cost
    (best-first-search).

# 3. Badania

- Dla każdego sposobu przeglądania należy wykonać
    badania na co najmniej 7 rozmiarach instancji loso-
    wych TSP i 7 rozmiarach instancji losowych ATSP.
    Algorytmy należy badać na tych samych instancjach
    nie tylko co do rozmiaru, ale również zawartości. Dla
    każdego rozmiaru należy wygenerować 20 instancji
    TSP i 20 ATSP.
- Dla każdego sposobu przeglądaia należy wykonać
    badania dla co najmniej 5 TSP i 5 ATSP instancji
    z bazy TSPLIB załączonej na eportalu.
- Określić maksymalny rozmiar instancji, dla której
    można znaleźć rozwiązanie w tzw. rozsądnym cza-
    sie – 15 min. Jeżeli taka instancja jest niedostępna
    (w wygenerowanych, TSPLIB), to należy oszacować
    jej rozmiar w opraciu o oszacowanie złożoności cza-
    sowej na podstawie przebiegu algorytmu i wyników
    badań otrzymanych dla dostępnych instancji.
- Wyznaczyć zależność czasu potrzebnego na uzy-
    skanie rozwiązania od rozmiaru instancji algorytmu
    B-and-B dla każdej z metod przeglądania przestrzeni
    rozwiązań.
- Sprawdzić wpływ zastosowania górnego ogranicze-
    nia (wyznaczonego korzystniejszą metodą zbadaną
    w zadaniu 1), na złożoność czasowoą (w oparciu
    o wyniki badań) oraz złożóność pamięciową (w opra-
    ciu o wyniki badań oraz oszacowania teoretyczne).
    Metody wyznaczania górnego ograniczenia to: lo-
    sowa, najbliższych sąsiadów (NN), wielokrotna naj-
    bliższych sąsiadów (RNN) bez badania remisów,
    z badaniami remisów.
- Porównać złożoność obliczeniową, maksymalny roz-
    miar instancji rozwiązywanej w rozsądnym czasie,
    wszystkich trzech metod przeszukiwania z podzia-
    łem na instacje symetryczne i asymetryczne.
- Scharakteryzować zbadane algorytmy (dotyczy rów-
    neiż tych z zadania 1) w kontekście ich efektywności
    rozwiązywania TSP i odpowiedzieć na pytanie, kiedy
    i dlaczego się do tego nadają, a kiedy nie.

# 4. Materiały

- Clausen Jens, Branch and Bound Algorithms - Prin-
    ciples and Examples. 1999
- Łyczek Mateusz, Metoda podziału i ograniczeń,
    2011
- David R. Morrisona, Sheldon H. Jacobsonb, Jason
    J. Sauppec, Edward L. Sewelld, Branch-and-bound
    algorithms: A survey of recent advances in sear-
    ching, branching, and pruning, Discrete Optimiza-
    tion 19 (2016) 79–

Wydział Inormatyki i Telekomunikacji 1 Wrocław, 4 marca 2026 r.


