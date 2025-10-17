#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// struktura punktu z współrzędnymi
struct Punkt {
    double x, y;
};

// wczytuje punkty z pliku
bool wczytaj(const string& plik, vector<Punkt>& p) {
    ifstream f(plik);                // otwieram plik
    if (!f.is_open()) return false;  // sprawdzam, czy plik się otworzył

    int n;
    if (!(f >> n)) return false;     // wczytuję liczbę punktów
    p.resize(n);                     // tworzę miejsce na punkty

    for (int i = 0; i < n; i++)      // wczytuję każdy punkt
        f >> p[i].x >> p[i].y;

    return true;
}

// sprawdza kierunek skrętu trzech punktów (lewo/prawo/liniowo)
double cross(const Punkt& o, const Punkt& a, const Punkt& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// tworzy kształt (otoczkę) obejmujący wszystkie punkty
vector<Punkt> otoczka(vector<Punkt> p) {
    int n = p.size(), k = 0;
    if (n <= 1) return p;

    // sortuję punkty od lewej do prawej (a potem po y)
    sort(p.begin(), p.end(), [](const Punkt& a, const Punkt& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    vector<Punkt> h(2 * n);  // miejsce na wynik

    // dolna część kształtu
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(h[k-2], h[k-1], p[i]) <= 0)
            k--;              // usuwam punkty wewnętrzne
        h[k++] = p[i];        // dodaję nowy punkt
    }

    // górna część kształtu
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(h[k-2], h[k-1], p[i]) <= 0)
            k--;
        h[k++] = p[i];
    }

    h.resize(k - 1);          // usuwam powtórzony punkt
    return h;
}

int main() {
    string plik;
    cout << "Podaj plik: ";
    cin >> plik;

    vector<Punkt> p;
    if (!wczytaj(plik, p)) {                // jeśli wczytanie się nie uda
        cerr << "Blad wczytywania pliku.\n";
        return 1;
    }

    auto h = otoczka(p);                    // obliczam granicę punktów

    cout << "Otoczka: ";
    for (int i = 0; i < h.size(); i++) {    // wypisuję wynik
        cout << "(" << h[i].x << ", " << h[i].y << ")";
        if (i + 1 < h.size()) cout << ", ";
    }
    cout << "\n";
}
// referencja tylko do odczytu
// referencja do wektora
// !f_is_open
// if (!(f>>n)) return false
// for (int i=0; i < n; i++)
// bool wczytaj(const string& plik, vector<punkt>& p) {
// f >> p[i].x >> p[i].y
// iloczyn wektorowy
// otoczka wypukła
// wykrzykniki, do czego?
// cerr