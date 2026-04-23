
### 1. Ogólna zasada działania programu
Program rozwiązuje problem komiwojażera (TSP/ATSP) wykorzystując architekturę drzewa decyzyjnego w oparciu o technikę **Branch and Bound (Podział i Ograniczenia)**. 
Proces dzieli się na następujące etapy:
1. **Inicjalizacja i Pomiar**: Program wczytuje macierz sąsiedztwa i natychmiast uruchamia zewnętrzny zegar (Timer) w bloku głównym `main`. Zapewnia to rzetelny pomiar "black-box" całego algorytmu, łącznie z ewentualnymi narzutami pamięciowymi czy heurystykami.
2. **Górne Ograniczenie (Upper Bound)**: Przed rozpoczęciem właściwego budowania drzewa, program może uruchomić szybką heurystykę (np. *Repetitive Nearest Neighbor - RNN*). Wynik tego zachłannego algorytmu służy jako początkowy punkt odniesienia (rekord). Jeśli go nie używamy, barierą jest nieskończoność.
3. **Dolne Ograniczenie (Lower Bound)**: W każdym węźle w drzewie obliczany jest dotychczasowy koszt pokonanej ścieżki (partial path cost). Stanowi on twarde dolne ograniczenie – wiemy na pewno, że końcowa trasa na dnie tej gałęzi nie będzie tańsza niż to, co wydaliśmy do tej pory.
4. **Odcinanie Gałęzi (Pruning)**: Za każdym razem, gdy algorytm odwiedza węzeł, następuje weryfikacja: `jeśli koszt dotychczasowy >= najlepszy znaleziony koszt globalny`, to cała ta gałąź jest natychmiast porzucana, ponieważ matematycznie nie ma szans na poprawę rekordu. 

---

### 2. Charakterystyka wariantów przeglądania drzewa

#### Przeszukiwanie Wszerz (BB_BFS - Breadth-First Search)
Algorytm bada przestrzeń rozwiązań poziom po poziomie. Używa do tego struktury danych typu kolejka (FIFO – First In, First Out). Wyjmuje węzeł z przodu kolejki, generuje wszystkich jego sąsiadów i wrzuca ich na jej koniec.
* **Zalety:** Systematycznie przegląda drzewo, odnajdując najkrótsze (pod względem liczby krawędzi) drogi jako pierwsze.
* **Wady:** W przypadku problemu TSP jest to wariant skrajnie nieoptymalny pamięciowo. Z uwagi na silnię, szerokość poziomów rośnie wykładniczo, co powoduje odłożenie milionów węzłów w pamięci RAM. Prowadzi to do bardzo szybkiego wyczerpania pamięci (tzw. *Out of Memory*), przez co algorytm załamuje się dla instancji większych niż kilkanaście miast.

#### Przeszukiwanie w Głąb – Rekurencyjnie (BB_DFS_REC - Depth-First Search Recursive)
Algorytm stara się dotrzeć do pełnego rozwiązania (liścia drzewa) najszybciej jak to możliwe, zanurzając się sukcesywnie w jedną konkretną gałąź. Gdy dotrze do końca (lub zostanie odcięty przez *Branch and Bound*), cofa się (backtracking) i wybiera inną drogę.
* **Zalety:** Bardzo niskie zużycie pamięci (przechowuje w niej tylko jedną, aktualnie badaną ścieżkę do liścia). Niezwykle szybko znajduje pierwsze pełne rozwiązania, co pozwala od razu drastycznie obniżyć globalny Upper Bound i ułatwić odcinanie pozostałych gałęzi.
* **Technikalia:** Mechanizm ten opiera się wprost na architekturze procesora – wykorzystuje systemowy "Stos Wywołań" (Call Stack). Działa ułamki sekund szybciej od iteracji, jednak w teorii (dla grafów rzędu kilkudziesięciu tysięcy wierzchołków) mógłby spowodować błąd *Stack Overflow*.

#### Przeszukiwanie w Głąb – Iteracyjnie (BB_DFS_STACK)
Algorytm zachowuje logikę "nurkowania" w głąb liścia, jednak zamiast sprzętowej rekurencji wykorzystuje powołaną na stercie w C++ strukturę `std::stack` (LIFO – Last In, First Out).
* **Zalety i Różnice:** Wyniki i skuteczność odcinania ma identyczne z podejściem rekurencyjnym. Wprowadza on minimalny narzut czasowy (rzędu pojedynczych milisekund) na rzecz bezpieczeństwa pamięciowego – samodzielnie alokuje zlecenia na stercie (Heap), unikając ryzyka przepełnienia stosu systemowego. Wprowadzenie obu wariantów miało na celu walidację różnic architektonicznych między stosami C++.

#### Metoda Najniższego Kosztu (BB_LC - Lowest-Cost / Best-First Search)
Jest to tzw. przeszukiwanie "połączone z wiedzą". Zamiast sztywno trzymać się reguł Wszerz lub W Głąb, ten algorytm ma na uwadze bieżący koszt wszystkich niezbadanych jeszcze odnóg. Odkładane są one do wektora, po czym algorytm w każdej iteracji przeszukuje całą listę i zawsze wyciąga węzeł o absolutnie najmniejszym dotychczasowym koszcie.
* **Zalety:** Algorytm naturalnie podąża obiecującymi drogami. Istnieje wysokie prawdopodobieństwo, że trzymając się najtańszych węzłów, szybko złoży optymalne rozwiązanie, natychmiast odcinając droższe i niepotrzebne ścieżki.
* **Wady:** W naszej edukacyjnej i całkowicie jawnej implementacji koszt wyciągania "najtańszego węzła" wiąże się z liniowym skanowaniem całego wektora. Sprawia to, że poszukiwania w rozbudowanych grafach mają delikatny narzut narastającej złożoności przeglądania wektora (tzw. "wąskie gardło"), co zauważalnie wydłuża jego czas w stosunku do szybkiego schodzenia DFS, mimo obcinania dużej części drzewa.