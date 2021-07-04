#include<iostream>
#include<vector>
#include<functional>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO RE\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false)
{
    if (sadrzaj == nullptr) return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, sadrzaj);
    if (dealociraj) delete[]sadrzaj;
    return novi;
}
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000)
    {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj)
    {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum(Datum&& obj)
    {
        _dan = obj._dan;
        obj._dan = nullptr;
        _mjesec = obj._mjesec;
        obj._mjesec = nullptr;
        _godina = obj._godina;
        obj._godina = nullptr;
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;

    }
    Datum& operator=(const Datum& obj)
    {
        if (this!=&obj)
        {
            *_dan = *obj._dan;
            *_mjesec = *obj._mjesec;
            *_godina = *obj._godina;

        }
        return *this;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
    friend bool operator == (const Datum& a1, const Datum& a2)
    {
        return *a1._dan == *a2._dan && *a1._mjesec == *a2._mjesec && *a1._godina == *a2._godina;
    }

};

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = 0;
        _omoguciDupliranje = omoguciDupliranje;
    }
    Kolekcija(const Kolekcija<T1, T2>& obj)
    {
        _trenutno = obj._trenutno;
        _omoguciDupliranje = obj._omoguciDupliranje;
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        for (size_t i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Kolekcija(Kolekcija<T1, T2>&& obj)
    {
        _trenutno = obj._trenutno;
        obj._trenutno = 0;
        _omoguciDupliranje = obj._omoguciDupliranje;
        _elementi1 = obj._elementi1;
        obj._elementi1 = nullptr;
        _elementi2 = obj._elementi2;
        obj._elementi2 = nullptr;

    }

    Kolekcija& operator=(const Kolekcija<T1, T2>& obj)
    {
        if (this != &obj)
        {
            _trenutno = obj._trenutno;
            _omoguciDupliranje = obj._omoguciDupliranje;
            delete[]_elementi1; delete[]_elementi2;
            _elementi1 = new T1[_trenutno];
            _elementi2 = new T2[_trenutno];
            for (size_t i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }

    void AddElement(T1 el1, T2 el2)
    {
        if (_omoguciDupliranje == true)
            for (size_t i = 0; i < _trenutno; i++)
                if (_elementi1[i] == el1 && _elementi2[i] == el2)
                    return;
        T1* temp1 = new T1[_trenutno + 1];
        T2* temp2 = new T2[_trenutno + 1];
        for (size_t i = 0; i < _trenutno; i++)
        {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
        _elementi1 = temp1;
        _elementi2 = temp2;
        _elementi1[_trenutno] = el1;
        _elementi2[_trenutno] = el2;
        _trenutno++;
    }

    T1* GetElementi1() const { return _elementi1; }
    T2* GetElementi2() const { return _elementi2; }

    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;

    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return _trenutno; }
    bool DupliranjeOmoguceno() const { return _omoguciDupliranje; }

    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
    friend bool operator==(const Kolekcija<T1, T2>& a1, const Kolekcija<T1, T2>& a2)
    {
        if (a1.getTrenutno() == a2.getTrenutno())
        {
            for (size_t i = 0; i < a1.getTrenutno(); i++)
                if (a1.getElement1(i) == a2.getElement1(i) && a1.getElement2(i) == a2.getElement2(i))
                    return true;
        }
        return false;
    }
    Kolekcija<T1, T2> operator()(int OD, int DO)
    {
        Kolekcija<T1, T2> novaKolekcija(!_omoguciDupliranje);
        if (OD >= 0 && OD < DO) {
            for (int i = OD; i <= DO; i++)
            {
                novaKolekcija.AddElement(_elementi1[i], _elementi2[i]);
            }
        }
        return novaKolekcija;

    }

};


class Predmet {
    const char* _naziv;
    char* _detalji;
    char _akademskaGodina[100];
    unique_ptr<int> _brojECTS;
    Kolekcija<int, Datum>* _ocjene;
public:
    Predmet(const char* naziv = "", const char* detalji = "", const char* akademskaGodina = "", int brojECTS = 5)
    {
        _naziv = GetNizKaraktera(naziv);
        _detalji = GetNizKaraktera(detalji);
        strcpy_s(_akademskaGodina, 100, "");
        _brojECTS = make_unique<int>(brojECTS);
        _ocjene = new Kolekcija<int, Datum>();
    }
    Predmet(const Predmet& obj)
    {
        _naziv = GetNizKaraktera(obj._naziv);
        _detalji = GetNizKaraktera(obj._detalji);
        strcpy_s(_akademskaGodina, 100, obj._akademskaGodina);
        _brojECTS = make_unique<int>(*obj._brojECTS);
        _ocjene = new Kolekcija<int, Datum>(obj._ocjene);


    }
    Predmet(Predmet&& obj) :_brojECTS(move(obj._brojECTS))
    {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
        _detalji = obj._detalji;
        obj._detalji = nullptr;
        strcpy_s(_akademskaGodina, 100, obj._akademskaGodina);
        _ocjene = obj._ocjene;
        obj._ocjene = nullptr;
    }
    Predmet& operator=(const Predmet& obj)
    {
        if (this != &obj)
        {
            delete[] _naziv;
            _naziv = GetNizKaraktera(obj._naziv);
            delete[]_detalji;
            _detalji = GetNizKaraktera(obj._detalji);
            strcpy_s(_akademskaGodina, 100, obj._akademskaGodina);
            if (_brojECTS == nullptr)_brojECTS = make_unique<int>();
            *_brojECTS = *obj._brojECTS;
            if (_ocjene == nullptr)  _ocjene = new Kolekcija<int, Datum>(obj._ocjene->DupliranjeOmoguceno());
            *_ocjene = *obj._ocjene;
        }
        return *this;
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
        delete[]_detalji; _detalji = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    void AddOcjena(int ocjena, Datum datum) {
        _ocjene->AddElement(ocjena, datum);
    }
    const char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return *_ocjene; }

    friend ostream& operator <<(ostream& COUT, const Predmet& predmet) {
        COUT << "Naziv: " << predmet._naziv << endl;
        COUT << "Detalji: " << predmet._detalji << endl;
        COUT << "Akademska godina: " << predmet._akademskaGodina << endl;
        COUT << "Broj ECTS:" << *predmet._brojECTS << endl;
        COUT << "Ocjene: " << endl;
        COUT << *predmet._ocjene << endl;
        return COUT;
    }
    friend bool operator==(const Predmet& a1, const Predmet& a2)
    {
        return strcmp(a1._naziv, a2._naziv) == 0 && strcmp(a1._detalji, a2._detalji) == 0;

    }
};

//formula: (x1 + x2 + x3 + ... + xn)/n;

function<float(int[], int)> aritmetickaSredina = [](int niz[], int vel) {

    float suma = 0.0f;
    for (size_t i = 0; i < vel; i++)
        suma += niz[i];
    return suma / vel;
};
//formula:  (x1 * x2 * x3 * ... * xn)^(1/n);
function<float(int[], int)> geometrijskaSredina = [](int niz[], int vel) {
    float suma = 1.0f;
    if (vel == 0) return suma;
    for (size_t i = 0; i < vel; i++)
        suma *= niz[i];
    return pow(suma, 1.0f / vel);

};

//formula:  n/((1/x1) + (1/x2) + ... + (1/xn))
function<float(int[], int)> harmonijskaSredina = [](int niz[], int vel)
{
    float suma = 1.0f;
    for (size_t i = 0; i < vel; i++)
    {
        suma += (1.0f / niz[i]);
    }
    return vel / suma;
};

int GetRandomBroj(int a, int b) {
    return rand() % b + a;
}

void main() {
    cout << PORUKA;
    Datum datum1(1, 1, 2021), datum2(2, 2, 2021), datum3(3, 3, 2021), datum4(4, 4, 2021);

    Datum temp(datum1);
    cout << ((datum1 == temp) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;
    Datum temp2(move(temp));
    cout << ((datum1 == temp2) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;
    Datum temp3;
    temp3 = datum1;
    cout << ((datum1 == temp3) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;
    cout << "\n";

    Kolekcija<Datum, int> ocjene(false);
    ocjene.AddElement(datum1, 10);
    ocjene.AddElement(datum1, 10);
    ocjene.AddElement(datum1, 8);
    ocjene.AddElement(datum2, 6);
    ocjene.AddElement(datum3, 6);
    ocjene.AddElement(datum4, 7);

    Kolekcija<Datum, int> ocjene2(ocjene);
    cout << ((ocjene == ocjene2) ? "Kolekcije sa istim vrijednostima" : "Kolekcije sa razlicitim vrijednostima") << endl;

    Kolekcija<Datum, int> ocjene3(move(ocjene2));
    cout << ((ocjene == ocjene3) ? "Kolekcije sa istim vrijednostima" : "Kolekcije sa razlicitim vrijednostima") << endl;

    Kolekcija<Datum, int> ocjene4;
    ocjene4 = ocjene;
    cout << ((ocjene == ocjene4) ? "Kolekcije sa istim vrijednostima" : "Kolekcije sa razlicitim vrijednostima") << endl;

    cout << ocjene4 << endl;

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> brojevi(false);
    for (int i = 0; i <= kolekcijaTestSize; i++) {
        int broj1 = GetRandomBroj(1, 3);
        int broj2 = GetRandomBroj(1, 3);
        brojevi.AddElement(broj1, broj2);
    }
    cout << brojevi << endl;
    /*objekat 'brojevi2' ce biti inicijalizovan elementima koji se u objektu 'brojevi' nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije.*/
    Kolekcija<int, int> brojevi2 = brojevi(1, 4);
    cout << brojevi2 << crt;

    Predmet operativniSistemi("Operativni sistemi", "Neki detalji...", "2020/2021", 7),
        diskretnaMatematika("Diskretna matematika", "Neki detalji...", "2020/2021", 6),
        engleskiJezik1("Engleski Jezik I", "Neki detalji...", "2020/2021", 6),
        programiranje1("Programiranje I", "Neki detalji...", "2020/2021", 7);
    programiranje1.AddOcjena(7, Datum(5, 4, 2021));
    programiranje1.AddOcjena(8, Datum(11, 4, 2021));
    programiranje1.AddOcjena(10, Datum(26, 4, 2021));

    Predmet pr1(programiranje1);

    cout << ((pr1 == programiranje1) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;

    Predmet pr_1(move(pr1));
    cout << ((pr_1 == programiranje1) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;

    Predmet PR1;
    PR1 = programiranje1;
    cout << ((PR1 == programiranje1) ? "Objekti sa istim vrijednostima" : "Objekti sa razlicitim vrijednostima") << endl;
    cout << PR1 << endl;

    cout << aritmetickaSredina(PR1.GetOcjene().GetElementi1(), PR1.GetOcjene().getTrenutno()) << endl;
    cout << geometrijskaSredina(PR1.GetOcjene().GetElementi1(), PR1.GetOcjene().getTrenutno()) << endl;
    cout << harmonijskaSredina(PR1.GetOcjene().GetElementi1(), PR1.GetOcjene().getTrenutno()) << endl;
    system("pause");
}

