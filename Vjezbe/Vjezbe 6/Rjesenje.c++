#include <iostream>
#include <memory>
#include <functional>
using namespace std;

//Z0.1
char* AlocirajIKopiraj(const char* izvor) {
    if (izvor == nullptr)
        return nullptr;
    int vel = strlen(izvor) + 1;
    char* destinacija = new char[vel];
    strcpy_s(destinacija, vel, izvor);
    return destinacija;
}

//Z0.2 :: Funkcija vraca max. od dva elementa
template<typename T>
T Max(T el1, T el2) { return (el1 > el2) ? el1 : el2; }

//Z0.3 :: Funkcija vraca min. od dva elementa
template<typename T>
T Min(T el1, T el2) { return (el1 < el2) ? el1 : el2; }

//Z0.4 :: Ispis niza (tipa T) gdje se delimiter ispisuje izmedju dva susjedna elementa tog niza
template<class T>
void IspisNiza(T niz[], int vel, const char* delimiter = ", ") {
    for (int i = 0; i < vel; i++)
        cout << niz[i] << delimiter;
    cout << endl;
}

/*Z0.5 :: Napisati genericku funkciju 'BubbleSort' za sortiranje niza elemenata tipa T
       :: Iskoristiti vec postojeci kod za sortiranje niza integera ('BubbleSort.txt') i prepraviti ga
       :: reverse' polje oznacava da li se radi o uzlaznom ili silaznom sortiranju
*/
template<class T>
void BubbleSort(T niz[], int vel, bool reverse = false) {
    auto operacija = [&reverse](T& el1, T& el2) {
        if (reverse == true)
            return el1 < el2;
        return el1 > el2;
    };
    for (int i = 0; i < vel - 1; i++) {
        for (int j = 0; j < vel - i - 1; j++) {
            if (operacija(niz[j], niz[j + 1])) {
                T temp = niz[j]; // implementirati copy ctor za klasu T
                niz[j] = niz[j + 1];  // implementirati operator '=' za klasu T
                niz[j + 1] = temp; // implementirati operator '=' za klasu T
            }
        }
    }
}

class Datum
{
private:
    unique_ptr<int> _dan;
    unique_ptr<int> _mjesec;
    unique_ptr<int> _godina;
public:
    //Z1.1
    Datum() {}
    //Z1.2
    Datum(int dan, int mjesec, int godina)
    {
        _dan = make_unique<int>(dan);
        _mjesec = make_unique<int>(mjesec);
        _godina = make_unique<int>(godina);
    }
    //Z1.3
    Datum(const Datum& obj)
    {
        _dan = make_unique<int>(*obj._dan);
        _mjesec = make_unique<int>(*obj._mjesec);
        _godina = make_unique<int>(*obj._godina);
    }
    //Z1.4
    Datum(Datum&& obj) :
        _dan(move(obj._dan)),
        _mjesec(move(obj._mjesec)),
        _godina(move(obj._godina))
    {
    }
    //Z1.5
    Datum& operator =(const Datum& obj) {
        if (this == &obj)
            return *this;
        if (_dan == nullptr) _dan = make_unique<int>();
        if (_mjesec == nullptr) _mjesec = make_unique<int>();
        if (_godina == nullptr) _godina = make_unique<int>();
        *_dan = *obj._dan;
        *_mjesec = *obj._mjesec;
        *_godina = *obj._godina;
        return *this;
    }

    //Z1.6
    void SetDan(int dan) {
        if (_dan == nullptr)
            _dan = make_unique<int>();
        *_dan = dan;
    }
    void SetMjesec(int mjesec) {
        if (_mjesec == nullptr)
            _mjesec = make_unique<int>();
        *_mjesec = mjesec;
    }
    void SetGodina(int godina) {
        if (_godina == nullptr)
            _godina = make_unique<int>();
        *_godina = godina;
    }
    //Z1.7
    int GetDan() const { return *_dan; }
    int GetMjesec() const { return *_mjesec; }
    int GetGodina() const { return *_godina; }

    //Z1.8
    bool CheckIfValid() {
        if (*_godina > INT_MAX || *_godina < INT_MIN)
            return false;
        if (*_mjesec < 1 || *_mjesec > 12)
            return false;
        if (*_dan < 1 || *_dan > 31)
            return false;

        bool (*CheckIfPrijestupna) (int) = [](int godina) {
            return (((godina % 4 == 0) &&
                (godina % 100 != 0)) ||
                (godina % 400 == 0));
        };
        if (*_mjesec == 2) {
            if (CheckIfPrijestupna(*_godina))
                return (*_dan <= 29);
            else
                return (*_dan <= 28);
        }
        if (*_mjesec == 4 || *_mjesec == 6 || *_mjesec == 9 || *_mjesec == 11)
            return (*_dan <= 30);
        return true;
    }

    //Z1.9 :: Staticka metoda za generisanje datuma (sa ugradjenom provjerom validnosti tog datuma)
    static Datum GetRandomDatum() {
        Datum datum;
        do {
            int d = rand() % 31 + 1; //vrijednost izmedju [1-31]
            int m = rand() % 12 + 1; //vraca vrijednost izmedju [1-12]
            int g = rand() % 2021 + 1; //vraca vrijednost izmedju [1-2021]
            datum.SetDan(d);
            datum.SetMjesec(m);
            datum.SetGodina(g);
        } while (!datum.CheckIfValid());
        return datum;
    }

    //Z1.10
    ~Datum() {
        _dan.reset();
        _mjesec.reset();
        _godina.reset();
    }
    friend ostream& operator << (ostream& COUT, const Datum& obj);
    friend bool operator == (const Datum& d1, const Datum& d2);
    friend bool operator > (const Datum&, const Datum&);
};
//Z1.11
bool operator == (const Datum& d1, const Datum& d2) {
    return *d1._dan == *d2._dan
        && *d1._mjesec == *d2._mjesec
        && *d1._godina == *d2._godina;
}
bool operator != (const Datum& d1, const Datum& d2) {
    return !(d1 == d2);
}

//Z1.12
bool operator >(const Datum& d1, const Datum& d2) {
    return d1.GetGodina() * 365 + d1.GetMjesec() * 30 + d1.GetDan()
    > d2.GetGodina() * 365 + d2.GetMjesec() * 30 + d2.GetDan();
}
bool operator >= (const Datum& d1, const Datum& d2) {
    return (d1 > d2) || (d1 == d2);
}
bool operator <= (const Datum& d1, const Datum& d2) {
    return  !(d1 > d2);
}
bool operator < (const Datum& d1, const Datum& d2) {
    return  !(d1 >= d2);
}
//Z1.13
ostream& operator << (ostream& COUT, const Datum& obj) {
    if (obj._dan != nullptr && obj._mjesec && obj._mjesec != nullptr && obj._godina != nullptr)
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
    return COUT;
}

//Vektor :: Kolekcija elemenata (tipa T) sa mogucnoscu dinamickog prosirivanja
template<class T>
class Vektor {
private:
    int _trenutno;  //oznacava velicinu niza
    int _maxElemenata;
    T* _elementi;
public:
    //Z2.1
    Vektor(int maxElemenata = 10) {
        _trenutno = 0;
        _maxElemenata = maxElemenata;
        _elementi = new T[_maxElemenata]; // implementirati dflt. ctor (klasa T)
    }
    //Z2.2
    Vektor(const Vektor<T>& kolekcija) {
        _trenutno = kolekcija._trenutno;
        _maxElemenata = kolekcija._maxElemenata;
        _elementi = new T[_maxElemenata]; // implementirati dflt. ctor (klasa T)
        for (int i = 0; i < _trenutno; i++)
            _elementi[i] = kolekcija._elementi[i]; // implementirati operator = (klasa T)
    }
    //Z2.3
    Vektor(Vektor<T>&& kolekcija) {
        _trenutno = kolekcija._trenutno;
        _maxElemenata = kolekcija._maxElemenata;
        _elementi = kolekcija._elementi;
        kolekcija._trenutno = 0, kolekcija._elementi = nullptr;
    }
    //Z2.4
    Vektor<T>& operator = (const Vektor<T>& kolekcija) {
        if (this == &kolekcija)
            return *this;
        _trenutno = kolekcija._trenutno;
        _maxElemenata = kolekcija._maxElemenata;
        delete[] _elementi; // implementirati dtor (klasa T)
        _elementi = new T[_maxElemenata]; // implementirati dflt. ctor (klasa T)
        for (int i = 0; i < _trenutno; i++)
            _elementi[i] = kolekcija._elementi[i]; // implementirati operator = (klasa T)
        return *this;
    }
    //Z2.5 :: Osigurati da je index unutar opsega [0,_trenutno-1]. Koristiti genericke funkcije 'Min' i 'Max' 
    T& operator [] (int index) const {
        index = Max<int>(0, index);
        index = Min<int>(index, _trenutno - 1);
        return _elementi[index];
    }
    T* GetElementi() const { return _elementi; }

    //Z2.6
    void ProsiriVektor(int prosiriZa) {
        T* temp = _elementi;
        _maxElemenata += prosiriZa;
        _elementi = new T[_maxElemenata];
        for (int i = 0; i < _trenutno; i++)
            _elementi[i] = temp[i];
        delete[] temp;
        temp = nullptr;
    }

    //Z2.7 :: Dodavanje novog elementa (ukoliko je _trenutno < _maxElemenata, uraditi prosirivanje niza za 10)
    void operator += (T noviElement) {
        if (_elementi == nullptr)
            _elementi = new T[_maxElemenata];
        if (_trenutno == _maxElemenata)
            ProsiriVektor(10);
        _elementi[_trenutno] = noviElement;
        _trenutno++;
    }
    //Z2.8
    bool UkloniZadnjiElement() {
        if (_trenutno == 0)
            return false;
        _trenutno--;
        return true;
    }

    //Z2.9
    bool CheckIfSadrzi(T element) {
        for (int i = 0; i < _trenutno; i++)
            if (_elementi[i] == element) // klasa T mora implementirati operator '=='
                return true;
        return false;
    }

    //Z2.10 :: Sortiranje elemenata na osnovu specificiranog algoritma
    void Sortiraj(void(*algoritamSortiranja)(T[], int, bool), bool reverse = false) {
        algoritamSortiranja(_elementi, _trenutno, reverse);
    }

    //Z2.11
    int GetTrenutno() const { return _trenutno; }
    int GetMaxElemenata() const { return _maxElemenata; }

    //Z.12
    ~Vektor() {
        delete[] _elementi; // implementirati dtor za klasu T
        _elementi = nullptr;
    }
    friend ostream& operator << <> (ostream& COUT, const Vektor<T>& kolekcija);
};
//Z2.13 :: Ispisuje elemente kolekcije. Za pristup elementima koristiti preklopljeni operator []
template<class T>
ostream& operator << <>(ostream& COUT, const Vektor<T>& kolekcija) {
    for (int i = 0; i < kolekcija._trenutno; i++)
        COUT << kolekcija[i] << endl;
    return COUT;
}

class Fudbaler {
private:
    char* _ime;
    char* _prezime;
    unique_ptr<Datum> _datumRodjenja;
    float* _visina; // npr. 1.75 m
    char _pozicija[50]; //pozicija na terenu

    int _trenutnoNagrada; //brojac :: krece od 0
    char* _nagrade[100] = { nullptr };
public:
    //Z3.1
    Fudbaler() {
        _ime = _prezime = nullptr;
        _visina = nullptr;
        strcpy_s(_pozicija, 50, "");
        _trenutnoNagrada = 0;
    }
    //Z3.2
    Fudbaler(const char* ime, const char* prezime, Datum datum, float visina, const char* pozicija) {
        _ime = AlocirajIKopiraj(ime);
        _prezime = AlocirajIKopiraj(prezime);
        _datumRodjenja = make_unique<Datum>(datum);
        _visina = new float(visina);
        strcpy_s(_pozicija, 50, pozicija);
        _trenutnoNagrada = 0;
    }
    //Z3.3
    Fudbaler(const Fudbaler& obj) {
        _ime = AlocirajIKopiraj(obj._ime);
        _prezime = AlocirajIKopiraj(obj._prezime);
        _datumRodjenja = make_unique<Datum>(*obj._datumRodjenja);
        _visina = new float(*obj._visina);
        strcpy_s(_pozicija, 50, obj._pozicija);
        _trenutnoNagrada = obj._trenutnoNagrada;
        for (int i = 0; i < _trenutnoNagrada; i++)
            _nagrade[i] = AlocirajIKopiraj(obj._nagrade[i]);
    }

    //Z3.4
    Fudbaler(Fudbaler&& obj) :
        _datumRodjenja(move(obj._datumRodjenja))
    {
        _ime = obj._ime;
        obj._ime = nullptr;
        _prezime = obj._prezime;
        obj._prezime = nullptr;
        _visina = obj._visina;
        obj._visina = nullptr;
        strcpy_s(_pozicija, 50, obj._pozicija);
        strcpy_s(obj._pozicija, 50, "");

        _trenutnoNagrada = obj._trenutnoNagrada;
        obj._trenutnoNagrada = 0;
        for (int i = 0; i < _trenutnoNagrada; i++) {
            _nagrade[i] = obj._nagrade[i];
            obj._nagrade[i] = nullptr;
        }
    }

    //Z3.5
    Fudbaler& operator = (const Fudbaler& obj) {
        if (this == &obj)
            return *this;
        delete[] _ime, delete[] _prezime;
        _ime = AlocirajIKopiraj(obj._ime);
        _prezime = AlocirajIKopiraj(obj._prezime);
        if (_datumRodjenja == nullptr)
            _datumRodjenja = make_unique<Datum>();
        *_datumRodjenja = *obj._datumRodjenja;
        if (_visina == nullptr)
            _visina = new float;
        *_visina = *obj._visina;
        strcpy_s(_pozicija, 50, obj._pozicija);
        for (int i = 0; i < _trenutnoNagrada; i++) {
            delete[] _nagrade[i];
            _nagrade[i] = nullptr;
        }
        _trenutnoNagrada = obj._trenutnoNagrada;
        for (int i = 0; i < _trenutnoNagrada; i++)
            _nagrade[i] = AlocirajIKopiraj(obj._nagrade[i]);
        return *this;
    }

    //Z3.6 :: Dodavanje nove nagrade u niz pokazivaca '_nagrade'. Uraditi alokaciju prilikom dodavanja
    bool operator()(const char* nagrada) {
        if (_trenutnoNagrada == 100)
            return false;
        _nagrade[_trenutnoNagrada] = AlocirajIKopiraj(nagrada);
        _trenutnoNagrada++;
        return true;
    }

    //Z3.7
    const char* GetIme() const { return _ime; }
    const char* GetPrezime() const { return _prezime; }
    Datum GetDatumRodjenja() const { return *_datumRodjenja; }
    float GetVisina() const { return *_visina; }
    const char* GetPozicija() const { return _pozicija; }
    int GetTrenutnoNagrada() const { return _trenutnoNagrada; }

    //Z3.8 :: Dohvacanje elementa iz niza '_nagrade'
    const char* operator[] (int index) const {
        index = Max<int>(0, index);
        index = Min<int>(index, _trenutnoNagrada - 1);
        return _nagrade[index];
    }

    //Z3.9
    void SetIme(const char* ime) {
        delete[] _ime;
        _ime = AlocirajIKopiraj(ime);
    }
    void SetPrezime(const char* prezime) {
        delete[] _prezime;
        _prezime = AlocirajIKopiraj(prezime);
    }
    void SetDatumRodjenja(Datum datumRodjenja) {
        if (_datumRodjenja == nullptr)
            _datumRodjenja = make_unique<Datum>();
        *_datumRodjenja = datumRodjenja;
    }
    void SetVisina(float visina) {
        if (_visina == nullptr)
            _visina = new float;
        *_visina = visina;
    }
    void SetPozicija(const char* pozicija) {
        strcpy_s(_pozicija, 50, pozicija);
    }

    //Z3.10
    ~Fudbaler() {
        delete[] _ime, delete[] _prezime, delete _visina;
        _ime = _prezime = nullptr;
        _visina = nullptr;
        _datumRodjenja.reset();
        for (int i = 0; i < _trenutnoNagrada; i++) {
            delete[] _nagrade[i];
            _nagrade[i] = nullptr;
        }
    }
};

//Z3.11
ostream& operator <<(ostream& COUT, const Fudbaler& fudbaler) {
    COUT << "Ime i prezime: " << fudbaler.GetIme() << " " << fudbaler.GetPrezime() << endl;
    COUT << "Datum rodjenja: " << fudbaler.GetDatumRodjenja() << endl;
    COUT << "Visina: " << fudbaler.GetVisina() << endl;
    COUT << "Pozicija na terenu: " << fudbaler.GetPozicija() << endl;
    COUT << "---------------------NAGRADE-----------------------------\n";
    for (int i = 0; i < fudbaler.GetTrenutnoNagrada(); i++)
        COUT << fudbaler[i] << endl;
    COUT << "---------------------------------------------------------\n";
    return COUT;
}

//Z3.12 :: Poredjenje vrijedosti svih atrbitura jednog objekta sa vrijednostima atributa drugog objekta
bool operator == (const Fudbaler& f1, const Fudbaler& f2) {
    if (strcmp(f1.GetIme(), f2.GetIme()) != 0)
        return false;
    if (strcmp(f1.GetPrezime(), f2.GetPrezime()) != 0)
        return false;
    if (f1.GetDatumRodjenja() != f2.GetDatumRodjenja())
        return false;
    if (f1.GetVisina() != f2.GetVisina())
        return false;
    if (strcmp(f1.GetPozicija(), f2.GetPozicija()) != 0)
        return false;
    if (f1.GetTrenutnoNagrada() != f2.GetTrenutnoNagrada())
        return false;
    for (int i = 0; i < f1.GetTrenutnoNagrada(); i++)
        if (strcmp(f1[i], f2[i]) != 0)
            return false;
    return true;
}

bool operator != (const Fudbaler& f1, const Fudbaler& f2) {
    return !(f1 == f2);
}

auto GetRandomBrojIgraca = []() {
    return rand() % 100 + 1;
};

class FudbalskiTim {
private:
    const char* _naziv;
    Datum _datumOsnivanja;
    char* _domaciStadion;
    Vektor<Fudbaler> _fudbaleri;
    Vektor<int> _brojevi; // brojevi fudbalera na majicama
    function<int()> _rasporedjivac;
public:
    //Z4.1 :: Postaviti defaultne vrijednosti
    FudbalskiTim(function<int()> rasporedjivac = GetRandomBrojIgraca) {
        _naziv = nullptr;
        _domaciStadion = nullptr;
        _rasporedjivac = rasporedjivac;
    }
    //Z4.2
    FudbalskiTim(const char* naziv, Datum datumOsnivanja, const char* domaciStadion, function<int()> rasporedjivac = GetRandomBrojIgraca) :
        _datumOsnivanja(datumOsnivanja.GetDan(), datumOsnivanja.GetMjesec(), datumOsnivanja.GetGodina())
    {
        _naziv = AlocirajIKopiraj(naziv);
        _domaciStadion = AlocirajIKopiraj(domaciStadion);
        _rasporedjivac = rasporedjivac;
    }
    //Z4.3
    FudbalskiTim(const FudbalskiTim& obj) :
        _datumOsnivanja(obj._datumOsnivanja), // klasa Datum mora implementirati  copy ctor
        _fudbaleri(obj._fudbaleri), // klasa Vektor mora implementirati copy ctor (kao i naravno klasa Fudbaler)
        _brojevi(obj._brojevi)
    {
        _naziv = AlocirajIKopiraj(obj._naziv);
        _domaciStadion = AlocirajIKopiraj(obj._domaciStadion);
        _rasporedjivac = obj._rasporedjivac;
    }

    //Z4.4
    FudbalskiTim(FudbalskiTim&& obj) :
        _datumOsnivanja(move(obj._datumOsnivanja)), // klasa Datum mora implementirati  move ctor
        _fudbaleri(move(obj._fudbaleri)), // klasa Vektor mora implementirati move ctor (kao i naravno klasa Fudbaler)
        _brojevi(move(obj._brojevi)) // ...
    {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
        _domaciStadion = obj._domaciStadion;
        obj._domaciStadion = nullptr;
        _rasporedjivac = obj._rasporedjivac;
    }

    //Z4.5
    FudbalskiTim& operator = (const FudbalskiTim& obj) {
        if (this == &obj)
            return *this;
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(obj._naziv);
        delete[] _domaciStadion;
        _domaciStadion = AlocirajIKopiraj(obj._domaciStadion);
        _datumOsnivanja = obj._datumOsnivanja; // klasa Datum mora implementirati  operator '=' 
        _fudbaleri = obj._fudbaleri; // klasa Vektor mora implementirati  operator '=' 
        _brojevi = obj._brojevi; // ...
        _rasporedjivac = obj._rasporedjivac;
        return *this;
    }

    //Z4.5
    const char* GetNaziv() const { return _naziv; }
    Datum GetDatumOsnivanja() const { return _datumOsnivanja; }
    const char* GetDomaciStadion() const { return _domaciStadion; }
    function<int()> GetRasporedjivac() const { return _rasporedjivac; }
    Vektor<Fudbaler> GetFudbalere() const { return _fudbaleri; }
    Vektor<int> GetBrojeve() const { return _brojevi; }

    //Z4.6
    void SetNaziv(const char* naziv) {
        delete[] _naziv;
        _naziv = AlocirajIKopiraj(naziv);
    }
    void SetDatumOsnivanja(Datum datumOsnivanja) {
        _datumOsnivanja = datumOsnivanja;
    }
    void SetDomaciStadion(const char* stadion) {
        delete[]_domaciStadion;
        _domaciStadion = AlocirajIKopiraj(stadion);
    }
    /*Z4.7 :: Dodati novog fudbalera, i asocirati uz njega novi (neiskoristeni) broj koristenjem pokazivaca na funkciju '_rasporedjivac'
           :: Dodavanje vrsiti u vektore '_fudbaleri' i '_brojevi'*/
    void operator += (Fudbaler fudbaler) {
        int noviBroj = 0;
        do {
            noviBroj = _rasporedjivac();
        } while (_brojevi.CheckIfSadrzi(noviBroj));
        _fudbaleri += fudbaler; // klasa Vektor mora implementirati operator '+=' za dodavanje
        _brojevi += noviBroj;
    }
    //4.8
    Fudbaler& operator[](int index) const {
        index = Max<int>(0, index);
        index = Min<int>(index, _fudbaleri.GetTrenutno() - 1);
        return _fudbaleri[index]; // klasa Vektor mora implementirati operator '[]' za pristupanje elementima
    }

    //4.9 :: Setter za polje '_brojevi'. Promijeniti vrijednost elementa na lokaciji specificiranoj parametrom 'index'
    void SetBroj(int index, int noviBroj) {
        index = Max<int>(0, index);
        index = Min<int>(index, _brojevi.GetTrenutno() - 1);
        _brojevi[index] = noviBroj;
    }

    //Z4.10
    ~FudbalskiTim() {
        delete[]_naziv, delete[] _domaciStadion;
        _naziv = _domaciStadion = nullptr;
    }
    friend ostream& operator << (ostream& COUT, const FudbalskiTim& tim);
    friend bool operator == (const FudbalskiTim& tim1, const FudbalskiTim& tim2);
};

//Z4.11 :: Ispisati obiljezja '_naziv', '_datumOsnivanja', '_domaciStadion', te imena, prezimena i brojeve fudbalera, kao i pozicije na kojima igraju
ostream& operator << (ostream& COUT, const FudbalskiTim& tim) {
    COUT << "Naziv: " << tim._naziv << endl;
    COUT << "Datum osnivanja: " << tim._datumOsnivanja << endl;
    COUT << "Domaci stadion: " << tim._domaciStadion << endl;
    COUT << "Trenutno aktivni fudbaleri: " << endl;
    COUT << "--------------------------------------------------------\n";
    for (int i = 0; i < tim._fudbaleri.GetTrenutno(); i++)
        COUT << tim[i].GetIme() << " " << tim[i].GetPrezime() << " (" << tim._brojevi[i] << ") " << tim[i].GetPozicija() << "\n";
    COUT << "--------------------------------------------------------\n";
    return COUT;
}

//Z4.12 :: Poredjenje objekata (poredjenje svih atributa)
bool operator == (const FudbalskiTim& tim1, const FudbalskiTim& tim2) {
    if (strcmp(tim1._naziv, tim2._naziv) != 0)
        return false;
    if (strcmp(tim1._domaciStadion, tim2._domaciStadion) != 0)
        return false;
    if (tim1._datumOsnivanja != tim2._datumOsnivanja)
        return false;
    if (tim1._fudbaleri.GetTrenutno() != tim2._fudbaleri.GetTrenutno())
        return false;
    for (int i = 0; i < tim1._fudbaleri.GetTrenutno(); i++)
        if (tim1[i] != tim2[i])
            return false;
    if (tim1._brojevi.GetTrenutno() != tim2._brojevi.GetTrenutno())
        return false;
    for (int i = 0; i < tim1._brojevi.GetTrenutno(); i++)
        if (tim1._brojevi[i] != tim2._brojevi[i])
            return false;
    return true;
}
bool operator != (const FudbalskiTim& tim1, const FudbalskiTim& tim2) {
    return !(tim1 == tim2);
}

class Utakmica {
private:
    pair<FudbalskiTim, FudbalskiTim> _timovi;
    pair<int, int> _postignutiGolovi;
public:
    //Z5.1 '_postignutiGolovi' postaviti na vrijednosti <0,0>
    Utakmica() {
        _postignutiGolovi = make_pair<int, int>(0, 0);
    }
    //Z5.2
    Utakmica(FudbalskiTim domacin, FudbalskiTim gosti) {
        _timovi = make_pair<FudbalskiTim, FudbalskiTim>(move(domacin), move(gosti));
        _postignutiGolovi = make_pair<int, int>(0, 0);
    }
    //Z5.3
    Utakmica(const Utakmica& obj) :
        _timovi(obj._timovi),
        _postignutiGolovi(obj._postignutiGolovi)
    {
    }

    //Z5.4
    Utakmica(Utakmica&& obj) :
        _timovi(move(obj._timovi)),
        _postignutiGolovi(move(obj._postignutiGolovi))
    {
    }

    //Z5.5
    Utakmica& operator = (const Utakmica& obj) {
        _timovi = obj._timovi;
        _postignutiGolovi = obj._postignutiGolovi;
        return *this;
    }

    //Z5.6
    FudbalskiTim GetDomacin() const {
        return _timovi.first;
    }
    FudbalskiTim GetGosti() const {
        return _timovi.second;
    }
    //Z5.7
    void SetDomacin(FudbalskiTim tim) {
        _timovi.first = tim;
    }
    void SetGosti(FudbalskiTim tim) {
        _timovi.second = tim;
    }
    //Z5.8 :: int golZa = {1 if Domacin, 2 if Gosti}
    void DodajGol(int golZa) {
        golZa = Max<int>(golZa, 1);
        golZa = Min<int>(golZa, 2);
        if (golZa == 1)
            _postignutiGolovi.first += 1;
        else
            _postignutiGolovi.second += 1;
    }
    //Z5.9
    ~Utakmica() {
    }
    friend ostream& operator <<(ostream& COUT, const Utakmica& utakmica);
    friend bool operator == (const Utakmica& u1, const Utakmica& u2);
};

/*Z5.10 :: Ispisati utakmicu u sljedecem formatu:
        Stadion: Camp Nou
        Barcelona - Arsenal [2:2]
*/
ostream& operator <<(ostream& COUT, const Utakmica& utakmica) {
    COUT << "Stadion: " << utakmica.GetDomacin().GetDomaciStadion() << endl;
    COUT << utakmica._timovi.first.GetNaziv() << " : " << utakmica._timovi.second.GetNaziv();
    COUT << " [" << utakmica._postignutiGolovi.first << ":" << utakmica._postignutiGolovi.second << "]" << endl;
    return COUT;
}

//Z5.11
bool operator == (const Utakmica& u1, const Utakmica& u2) {
    if (u1._timovi.first != u2._timovi.first) return false;
    if (u1._timovi.second != u2._timovi.second) return false;
    if (u1._postignutiGolovi.first != u2._postignutiGolovi.first) return false;
    if (u1._postignutiGolovi.second != u2._postignutiGolovi.second) return false;
    return true;
}

void Zadatak1() {
    Datum aprilFoolsDay;
    Datum laborDay(1, 5, 2021);
    Datum newYearsEve(31, 12, 2021);
    aprilFoolsDay.SetDan(1);
    aprilFoolsDay.SetMjesec(4);
    aprilFoolsDay.SetGodina(2021);

    Datum d1(aprilFoolsDay);
    Datum d2(move(laborDay));
    Datum d3;
    d3 = newYearsEve;
    cout << d1 << endl;
    cout << d2 << endl;
    cout << d3 << endl;
    cout << "Dealokacija..." << endl;
}

void Zadatak2() {
    cout << ":::::::::: Vektor<int> :::::::::::\n";
    Vektor<int> ocjeneFilma;
    int brojOcjena = 30;
    for (int i = 0; i < brojOcjena; i++)
        ocjeneFilma += rand() % 10 + 1;
    IspisNiza(ocjeneFilma.GetElementi(), ocjeneFilma.GetTrenutno(), ", ");

    ocjeneFilma.Sortiraj(BubbleSort);
    cout << "Ocjene filma nakon sortiranja [Ascending]:" << endl;
    IspisNiza(ocjeneFilma.GetElementi(), ocjeneFilma.GetTrenutno(), ", ");

    ocjeneFilma.Sortiraj(BubbleSort, true);
    cout << "Ocjene filma nakon sortiranja [Descending]:" << endl;
    IspisNiza(ocjeneFilma.GetElementi(), ocjeneFilma.GetTrenutno(), ", ");

    Vektor<int> ocjeneFilma2(ocjeneFilma);
    Vektor<int> ocjeneFilma3(move(ocjeneFilma));
    Vektor<int> ocjeneFilma4;
    ocjeneFilma4 = ocjeneFilma2;
    auto checkIfIsti = [](Vektor<int>& v1, Vektor<int>& v2) {
        if (v1.GetTrenutno() != v2.GetTrenutno())
            return false;
        for (int i = 0; i < v1.GetTrenutno(); i++)
            if (v1[i] != v2[i])
                return false;
        return true;
    };
    cout << (checkIfIsti(ocjeneFilma, ocjeneFilma2) ? "Isti vektori" : "Nisu isti vektori") << endl;
    cout << (checkIfIsti(ocjeneFilma, ocjeneFilma3) ? "Isti vektori" : "Nisu isti vektori") << endl;
    cout << (checkIfIsti(ocjeneFilma2, ocjeneFilma3) ? "Isti vektori" : "Nisu isti vektori") << endl;
    cout << (checkIfIsti(ocjeneFilma4, ocjeneFilma2) ? "Isti vektori" : "Nisu isti vektori") << endl;
    cout << "\n\n";

    cout << ":::::::::: Vektor<Datum> :::::::::::\n";
    Vektor<Datum> datumi;
    int brojDatuma = 15;
    for (int i = 0; i < brojDatuma; i++)
        datumi += Datum::GetRandomDatum(); // dodavanje novog datuma u vektor 
    cout << datumi << endl;
    datumi.Sortiraj(BubbleSort);
    cout << "Datumi nakon sortiranja [Ascending]:" << endl;
    cout << datumi << endl;
    datumi.Sortiraj(BubbleSort, true);
    cout << "Datumi nakon sortiranja [Descending]:" << endl;
    cout << datumi << endl;
    cout << "Dealokacija..." << endl;
}

void Zadatak3() {
    cout << "::::::::::klasa Fudbaler:::::::::::\n";
    Fudbaler gandhi;
    gandhi.SetIme("Mohandas");
    gandhi.SetPrezime("Gandhi");
    gandhi.SetVisina(1.70f);
    gandhi.SetDatumRodjenja(Datum(5, 5, 1990));
    gandhi.SetPozicija("Obrambeni vezni");
    //Dodjeljivanje nagrada igracu
    gandhi("Fair play award 2018"); // poziv operatora '()' za dodavanje novog elementa u niz '_nagrade'
    gandhi("Fair play award 2019");
    gandhi("Fair play award 2020");
    gandhi("Fair play award 2021");
    gandhi("The best team leader award 2019");
    gandhi("The best team leader award 2020");
    gandhi("The greatest comeback award 2020");
    gandhi("The greatest comeback award 2021");
    gandhi("Sportsmanship award 2019");
    gandhi("Sportsmanship award 2020");
    gandhi("The most effective player vs. England national team 2020");
    gandhi("The most effective player vs. England national team 2021");
    gandhi("The 1st player to score 5 goals vs. England in a single match");
    gandhi("The best Indian football player of all time");
    cout << gandhi << "\n";

    cout << "Testiranje user-def. konstruktora: ";
    Fudbaler gandhi2(gandhi.GetIme(), gandhi.GetPrezime(), gandhi.GetDatumRodjenja(), gandhi.GetVisina(), gandhi.GetPozicija());
    for (int i = 0; i < gandhi.GetTrenutnoNagrada(); i++)
        gandhi2(gandhi[i]); // dodajemo nagrade drugom objektu
    cout << ((gandhi == gandhi2) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje konstruktora kopije: ";
    Fudbaler gandhiImpostor(gandhi);
    cout << ((gandhi == gandhiImpostor) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje move konstruktora: ";
    Fudbaler gandhiMover(move(gandhiImpostor));
    cout << ((gandhi == gandhiMover) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje operatora '=': ";
    Fudbaler martinLutherKing;
    martinLutherKing = gandhi;
    cout << ((gandhi == martinLutherKing) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;
    cout << "Dealokacija..." << endl;
}

void Zadatak4() {
    cout << "::::::::::klasa FudbalskiTim:::::::::::\n";
    Fudbaler trump("Donald J.", "Trump", Datum(1, 3, 2150), 1.66f, "Centralni napadac");
    Fudbaler dalaiLama("Tenzin", "Gyatso", Datum(5, 3, 2151), 1.78f, "Obrambeni vezni");
    Fudbaler superSemir("Dr. Semir", "Osmanagic", Datum(5, 3, 2150), 1.85f, "Golman");
    Fudbaler ciroImpostor("Tarik", "Filipovic", Datum(5, 3, 2149), 1.85f, "Stoper");
    Fudbaler kreso("Kresimir", "Misak", Datum(5, 3, 2158), 1.66f, "Krilni vezni");
    Fudbaler theForbiddenOne("Chuck", "Norris", Datum(32, 12, 2154), 2.5f, "Na svim pozicijama istovremeno");

    FudbalskiTim osvajaciGalaksije;
    osvajaciGalaksije.SetNaziv("Osvajaci Galaksije (F.C)");
    osvajaciGalaksije.SetDomaciStadion("Milenijsko gnijezdo");
    osvajaciGalaksije.SetDatumOsnivanja(Datum(5, 5, 2100));

    osvajaciGalaksije += trump;
    osvajaciGalaksije += dalaiLama;
    osvajaciGalaksije += superSemir;
    osvajaciGalaksije += ciroImpostor;
    osvajaciGalaksije += kreso;
    osvajaciGalaksije += theForbiddenOne;
    cout << osvajaciGalaksije << endl;

    cout << "Testiranje user-def. konstruktora: ";
    FudbalskiTim galaktikosi(osvajaciGalaksije.GetNaziv(), osvajaciGalaksije.GetDatumOsnivanja(), osvajaciGalaksije.GetDomaciStadion(),
        osvajaciGalaksije.GetRasporedjivac());
    Vektor<Fudbaler> fudbaleri = osvajaciGalaksije.GetFudbalere();
    Vektor<int> brojevi = osvajaciGalaksije.GetBrojeve();
    for (int i = 0; i < fudbaleri.GetTrenutno(); i++)
        galaktikosi += fudbaleri[i];
    for (int i = 0; i < brojevi.GetTrenutno(); i++)
        galaktikosi.SetBroj(i, brojevi[i]);
    cout << ((osvajaciGalaksije == galaktikosi) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje konstruktora kopije: ";
    FudbalskiTim osvajaci2(osvajaciGalaksije);
    cout << ((osvajaciGalaksije == osvajaci2) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje move konstruktora: ";
    FudbalskiTim osvajaci3(move(osvajaci2));
    cout << ((osvajaciGalaksije == osvajaci3) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje operatora '=': ";
    FudbalskiTim osvajaci4;
    osvajaci4 = osvajaciGalaksije;
    cout << ((osvajaci4 == osvajaciGalaksije) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;
    cout << "Dealokacija..." << endl;
}

void Zadatak5() {
    cout << "::::::::::klasa Utakmica:::::::::::\n";
    //Tim :: 1
    Fudbaler sleepyJoe("Joe", "Biden", Datum(3, 4, 1950), 1.77f, "Obrambeni vezni");
    Fudbaler stableTrump("Donald J.", "Trump", Datum(5, 4, 1951), 1.88f, "Centralni napadac");
    Fudbaler lyingTed("Ted", "Cruz", Datum(6, 6, 1952), 1.8f, "Centralni vezni");
    Fudbaler theLittleMan("Marco", "Rubio", Datum(7, 7, 1953), 1.6f, "Ofanzivni vezni");
    Fudbaler lowEnergyJeb("Jeb", "Bush", Datum(8, 8, 1954), 1.68f, "Golman");
    //Tim :: 2
    Fudbaler facebookLord("Mark", "Zuckerberg", Datum(3, 4, 1960), 1.74f, "Obrambeni vezni");
    Fudbaler elonTheMartian("Elon", "Musk", Datum(5, 5, 1961), 1.77f, "Leteci napadac");
    Fudbaler codeJeff("Jeff", "Bezos", Datum(5, 3, 1961), 1.8f, "Centralni vezni");
    Fudbaler theVaxGuy("Bill", "Gates", Datum(15, 3, 1955), 1.85f, "Golman");
    Fudbaler cryptoGuru("Satoshi", "Nakamoto", Datum(15, 3, 1955), 1.85f, "Nevidljiv na terenu");

    FudbalskiTim cowboys("Cowboys (F.C)", Datum(1, 3, 1960), "Wild West Park");
    cowboys += sleepyJoe;
    cowboys += stableTrump;
    cowboys += lyingTed;
    cowboys += theLittleMan;
    cowboys += lowEnergyJeb;

    FudbalskiTim aliens("Aliens (F.C)", Datum(5, 6, 1955), "Galaxy Centre");
    aliens += facebookLord;
    aliens += elonTheMartian;
    aliens += codeJeff;
    aliens += theVaxGuy;
    aliens += cryptoGuru;

    Utakmica spaceClassico;
    spaceClassico.SetDomacin(cowboys);
    spaceClassico.SetGosti(aliens);
    spaceClassico.DodajGol(1); //gol za domacina
    spaceClassico.DodajGol(1); //gol za domacina
    spaceClassico.DodajGol(2); //gol za goste
    spaceClassico.DodajGol(2); //gol za goste
    spaceClassico.DodajGol(1); //gol za domacina
    cout << spaceClassico << endl;

    cout << "Testiranje user-def. konstruktora: ";
    Utakmica derbi(cowboys, aliens);
    derbi.DodajGol(1);
    derbi.DodajGol(1);
    derbi.DodajGol(2);
    derbi.DodajGol(2);
    derbi.DodajGol(1);
    cout << ((spaceClassico == derbi) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje konstruktora kopije: ";
    Utakmica kopija(spaceClassico);
    cout << ((spaceClassico == kopija) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje move konstruktora: ";
    Utakmica clashOfTheTitans(move(kopija));
    cout << ((spaceClassico == clashOfTheTitans) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;

    cout << "Testiranje operatora '=': ";
    Utakmica mecNaseGeneracije;
    mecNaseGeneracije = spaceClassico;
    cout << ((spaceClassico == mecNaseGeneracije) ? "Ispravno uradjen" : "Nije ispravno uradjen") << endl;
    cout << "Dealokacija..." << endl;
}

void Menu() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "***Zadaci***" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 5);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: Zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        default:break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
}
int main() {
    Menu();
    return 0;
}

