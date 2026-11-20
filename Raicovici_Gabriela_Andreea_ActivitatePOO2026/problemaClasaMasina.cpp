#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Masina {
private:
    char* marca;
    float pret;
    int anFabricatie;
    bool disponibila;
    int nrDotari;
    string* dotari;

    const int id;
    static int contor;

public:

    // Constructor fara parametri
    Masina() : id(contor++) {
        marca = new char[strlen("Necunoscuta") + 1];
        strcpy(marca, "Necunoscuta");

        pret = 0;
        anFabricatie = 2020;
        disponibila = false;
        nrDotari = 0;
        dotari = nullptr;
    }

    // Constructor cu parametri
    Masina(const char* marca, float pret,
        int anFabricatie, bool disponibila,
        int nrDotari, string* dotari)
        : id(contor++) {

        this->marca = new char[strlen(marca) + 1];
        strcpy(this->marca, marca);

        this->pret = pret;
        this->anFabricatie = anFabricatie;
        this->disponibila = disponibila;

        if (nrDotari > 0 && dotari != nullptr) {
            this->nrDotari = nrDotari;
            this->dotari = new string[nrDotari];

            for (int i = 0; i < nrDotari; i++) {
                this->dotari[i] = dotari[i];
            }
        }
        else {
            this->nrDotari = 0;
            this->dotari = nullptr;
        }
    }

    // Constructor de copiere
    Masina(const Masina& m) : id(contor++) {
        marca = new char[strlen(m.marca) + 1];
        strcpy(marca, m.marca);

        pret = m.pret;
        anFabricatie = m.anFabricatie;
        disponibila = m.disponibila;
        nrDotari = m.nrDotari;

        if (nrDotari > 0) {
            dotari = new string[nrDotari];

            for (int i = 0; i < nrDotari; i++) {
                dotari[i] = m.dotari[i];
            }
        }
        else {
            dotari = nullptr;
        }
    }

    // Destructor
    ~Masina() {
        delete[] marca;
        delete[] dotari;
    }

    // Operator =
    Masina& operator=(const Masina& m) {
        if (this != &m) {
            char* marcaNoua =
                new char[strlen(m.marca) + 1];
            strcpy(marcaNoua, m.marca);

            string* dotariNoi = nullptr;

            if (m.nrDotari > 0) {
                dotariNoi = new string[m.nrDotari];

                for (int i = 0; i < m.nrDotari; i++) {
                    dotariNoi[i] = m.dotari[i];
                }
            }

            delete[] marca;
            delete[] dotari;

            marca = marcaNoua;
            dotari = dotariNoi;

            pret = m.pret;
            anFabricatie = m.anFabricatie;
            disponibila = m.disponibila;
            nrDotari = m.nrDotari;
        }

        return *this;
    }

    // Getteri
    const char* getMarca() const {
        return marca;
    }

    float getPret() const {
        return pret;
    }

    int getAnFabricatie() const {
        return anFabricatie;
    }

    bool getDisponibila() const {
        return disponibila;
    }

    int getNrDotari() const {
        return nrDotari;
    }

    int getId() const {
        return id;
    }

    static int getContor() {
        return contor;
    }

    // Setter
    void setPret(float pret) {
        if (pret >= 0) {
            this->pret = pret;
        }
    }

    // Metoda de afisare
    void afisare() const {
        cout << "ID: " << id << endl;
        cout << "Marca: " << marca << endl;
        cout << "Pret: " << pret << endl;
        cout << "An fabricatie: "
            << anFabricatie << endl;
        cout << "Disponibila: "
            << disponibila << endl;
        cout << "Numar dotari: "
            << nrDotari << endl;

        for (int i = 0; i < nrDotari; i++) {
            cout << dotari[i] << endl;
        }

        cout << endl;
    }

    // Metoda pentru vechime
    int calculeazaVechime() const {
        return 2026 - anFabricatie;
    }

    // Operator +
    Masina operator+(float valoare) const {
        Masina copie(*this);
        copie.pret += valoare;
        return copie;
    }

    // Operator []
    string& operator[](int index) {
        if (index >= 0 && index < nrDotari) {
            return dotari[index];
        }

        throw "Index invalid";
    }

    // Operator ()
    float operator()(float procent) const {
        return pret * procent / 100;
    }

    // Operator ==
    bool operator==(const Masina& m) const {
        return pret == m.pret &&
            anFabricatie == m.anFabricatie &&
            strcmp(marca, m.marca) == 0;
    }

    // Operator -=
    Masina& operator-=(float valoare) {
        if (valoare >= 0 && valoare <= pret) {
            pret -= valoare;
        }

        return *this;
    }

    // Operator +=
    Masina& operator+=(float valoare) {
        pret += valoare;
        return *this;
    }

    // Operator ++ prefixat
    Masina& operator++() {
        pret++;
        return *this;
    }

    // Operator ++ postfixat
    Masina operator++(int) {
        Masina copie(*this);
        pret++;
        return copie;
    }

    // Conversie la float
    explicit operator float() const {
        return pret;
    }

    // Conversie la int
    explicit operator int() const {
        return anFabricatie;
    }
};

// Initializare atribut static
int Masina::contor = 100;

int main() {

    Masina m1;

    string dotari1[] = {
        "Aer conditionat",
        "Navigatie",
        "Scaune incalzite"
    };

    Masina m2("BMW", 25000, 2020,
        true, 3, dotari1);

    cout << "Masina 1:" << endl;
    m1.afisare();

    cout << "Masina 2:" << endl;
    m2.afisare();

    // Constructor de copiere
    Masina m3(m2);

    cout << "Masina 3:" << endl;
    m3.afisare();

    // Setter
    m1.setPret(15000);

    cout << "Pret nou m1: "
        << m1.getPret() << endl;

    // Operator =
    m1 = m2;

    cout << "Dupa atribuire:" << endl;
    m1.afisare();

    // Operator +
    Masina m4 = m2 + 1000;

    cout << "Dupa operator +:" << endl;
    m4.afisare();

    // Operator []
    cout << "Prima dotare: "
        << m2[0] << endl;

    // Operator ()
    cout << "10% din pret: "
        << m2(10) << endl;

    // Operator ==
    if (m1 == m2) {
        cout << "Masinile sunt egale" << endl;
    }
    else {
        cout << "Masinile sunt diferite" << endl;
    }

    // Operator -=
    m2 -= 500;

    cout << "Pret dupa -=: "
        << m2.getPret() << endl;

    // Operator +=
    m2 += 1000;

    cout << "Pret dupa +=: "
        << m2.getPret() << endl;

    // Operator ++ prefixat
    ++m2;

    cout << "Pret dupa ++m2: "
        << m2.getPret() << endl;

    // Operator ++ postfixat
    m2++;

    cout << "Pret dupa m2++: "
        << m2.getPret() << endl;

    // Conversie la float
    float pretMasina = (float)m2;

    cout << "Conversie float: "
        << pretMasina << endl;

    // Conversie la int
    int an = (int)m2;

    cout << "Conversie int: "
        << an << endl;

    // Metoda vechime
    cout << "Vechime masina: "
        << m2.calculeazaVechime() << endl;

    // Atribut static
    cout << "Contor: "
        << Masina::getContor() << endl;

    return 0;
}