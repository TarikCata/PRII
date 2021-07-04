#include <iostream>
using namespace std;


/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ÆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEÈILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIÈNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUÈAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOÆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

char* aloc(const char* tekst)
{
    if (tekst == nullptr) return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}

const char* crt = "\n----------------------------------------------------\n";
class Datum
{
    int* _dan, * _mjesec, * _godina;
public:
    
    Datum(int d, int m, int g)
    {
        _dan = new int(d);
        _mjesec = new int(m);
        _godina = new int(g);
    }
    Datum(const Datum& obj)
    {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    ~Datum()
    {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<<(ostream& COUT, const Datum& obj)
    {
        COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina;
        return COUT;
    }
    Datum& operator=(const Datum& obj)
    {
        if (this != &obj)
        {
            *_dan = *obj._dan;
            *_mjesec = *obj._mjesec;
            *_godina = *obj._godina;
        }
        return *this;
    }
};

template<class T, int velicina>
class FITArray
{
    T  _niz[velicina];
    int _trenutno;
    bool _dozvoliDupliciranje;
public:
    // OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE

    FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
    FITArray(const FITArray& obj) {
            for (size_t i = 0; i < _trenutno; i++)
                _niz[i] = obj._niz[i];
            _trenutno = obj._trenutno;
            _dozvoliDupliciranje = obj._dozvoliDupliciranje;
        
    }
    int GetTrenutno() const { return _trenutno; }
    T* GetNiz() { return _niz; }
    bool operator+=(const T&);
    friend ostream& operator<<<>(ostream&, const FITArray&);
    void operator-=(const T&);
    FITArray<T, velicina> operator ()(int OD, int DO);
    FITArray& operator=(const FITArray& obj) {
        if (this!=&obj)
        {
            _trenutno = obj._trenutno;
            _dozvoliDupliciranje = obj._dozvoliDupliciranje;
            for (size_t i = 0; i < _trenutno; i++)
                _niz[i] = obj._niz[i];
        }
        return *this;
    }
};
template<class T, int velicina>
bool FITArray<T, velicina>::operator+=(const T& broj)
{
    if (_trenutno == velicina) return false;
    if (!_dozvoliDupliciranje)
        for (size_t i = 0; i < _trenutno; i++)
            if (_niz[i] == broj)
                return false;
    _niz[_trenutno++] = broj; 
    return true;
}

template<class T, int velicina>
ostream& operator<<(ostream& cout, const FITArray<T, velicina>& obj)
{
    for (size_t i = 0; i < obj._trenutno; i++)
        cout << obj._niz[i] << endl;
    return cout;
}

template<class T, int velicina>
void FITArray<T, velicina>::operator-=(const T& el)
{
    for (size_t i = 0; i < _trenutno; i++)
    {
        if (_niz[i] == el)
        {
            for (size_t j = i; j < _trenutno - 1; j++)
            {
                _niz[j] = _niz[j + 1];
            }
            _trenutno--;
            if (!_dozvoliDupliciranje)
                return;
            else
                i--;
        }
    }
}

template<class T, int velicina>
FITArray<T,velicina> FITArray<T,velicina>::operator()(int OD,int DO)
{
    
    FITArray<T,velicina>temp(_trenutno);
    
    if(OD >= 0 && OD < _trenutno)
    { 
        if (DO > _trenutno) DO = _trenutno;
        for (size_t i = OD; i <= DO ; i++)
        {
            temp += _niz[i];
        }
    }
    return temp;

}


class PolozeniPredmet
{
    char* _naziv;
    int _ocjena;
    Datum _datumPolaganja;
public:
    PolozeniPredmet():_datumPolaganja(1,1,2000)
    {
        _naziv = nullptr;
        _ocjena = 5;
    }
    PolozeniPredmet(const Datum& datum,const char* tekst,int ocjena):_datumPolaganja(datum)
    {
        _naziv = aloc(tekst);
        _ocjena = ocjena;
    }
    PolozeniPredmet(const PolozeniPredmet& obj) : _datumPolaganja(obj._datumPolaganja) {
        _naziv = aloc(obj._naziv);
        _ocjena = obj._ocjena;
    }
    int GetOcjena() const { return _ocjena; }
    ~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }
    friend ostream& operator<<(ostream& COUT,const PolozeniPredmet& obj)
    {
        COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
        return COUT;
    }
    friend bool operator == (const PolozeniPredmet & jedan, const PolozeniPredmet & dva);
    PolozeniPredmet& operator=(const PolozeniPredmet& obj)
    {
        if (this != &obj)
        {
            delete[]_naziv;
            _naziv = aloc(obj._naziv);
            _ocjena = obj._ocjena;
            _datumPolaganja = obj._datumPolaganja;
        }
        return *this;
    }
};
bool operator == (const PolozeniPredmet& jedan, const PolozeniPredmet& dva) { return strcmp(jedan._naziv, dva._naziv) == 0 && jedan._ocjena == dva._ocjena; }


class Student
{
    static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
    const int _indeks;
    char* _imePrezime;
    FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:
    Student(const char* tekst) :_indeks(_indeksCounter++),_polozeniPredmeti(false)
    {
        _imePrezime = aloc(tekst);
    }
    
    ~Student()
    {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<<(ostream& COUT, Student& obj)
    {
        COUT << obj._indeks << " " << obj._imePrezime << endl << obj._polozeniPredmeti;
        return COUT;
    }
    bool DodajPredmet(const PolozeniPredmet& predmet)
    {
        return _polozeniPredmeti += predmet;
    }
    
    Student& operator=(const Student& obj)
    {
        if (this!= & obj)
        {
            delete[]_imePrezime;
            _imePrezime = aloc(obj._imePrezime);
            _polozeniPredmeti = obj._polozeniPredmeti;
        }
        return *this;
    }
    float GetProsjek() {
        float prosjek = 0.0f;
        if (_polozeniPredmeti.GetTrenutno() == 0) return 0;
        for (size_t i = 0; i < _polozeniPredmeti.GetTrenutno(); i++)
            prosjek += _polozeniPredmeti.GetNiz()[i].GetOcjena();
        return prosjek /= _polozeniPredmeti.GetTrenutno();
    }
};
int Student::_indeksCounter = 160000;


void main()
{
    const int max = 20;
    
    Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
    cout << jucer << danas << sutra << endl;
    jucer = danas;
    cout << jucer << danas << sutra << endl;

    //parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
    FITArray<int, max> nizIntegera(false);

    for (size_t i = 0; i < max - 1; i++)
       nizIntegera += i;//dodaje novog clana niza
    

    if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
        cout << "Element nije dodan u niz" << endl;

    cout << crt << nizIntegera << crt; //ispisuje sve clanove niza

    nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
    nizIntegera -= 17;

    FITArray<int, max> noviNizIntegera(nizIntegera);
    cout << crt << noviNizIntegera << crt;


    // parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti. u 
    // slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od lokacije 
    // OD pa do posljednje dostupnog elementa 
    cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << endl << noviNizIntegera(2, 5) << crt;

    Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

    PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7);
    adel.DodajPredmet(prII);
    adel.DodajPredmet(prIII);
    cout << adel << endl;
    //////vraca prosjecnu ocjenu studenta
    cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;
    //
    jasmin = adel;
    cout << jasmin << endl;
    cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
    system("pause");
}