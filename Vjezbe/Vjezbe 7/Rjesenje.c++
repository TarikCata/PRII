#include <vector>
#include <iostream>
#include <cassert>
#include <functional>
using namespace std;

int MIN_GODINA = 1, MAX_GODINA = 10000;
enum Mjesec { Januar = 1, Februar, Mart, April, Maj, Juni, Juli, August, Septembar, Oktobar, Novembar, Decembar };
enum class Spol { Muski = 1, Zenski = 0 };

//Z0.1 
char* Alokator(const char* tekst) {
    if (tekst == nullptr)return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}
//Z0.2 :: Funkcija za alokaciju pametnog (shared_ptr) pokazivaca na niz karaktera

shared_ptr<char> SharedAlokator(const char* tekst)
{
    if (tekst == nullptr) return nullptr;
    int vel = strlen(tekst) + 1;
    shared_ptr<char>novi;
    novi.reset(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi; 
}

//Z0.3 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char> UniqueAlokator(const char* tekst) {
    if (tekst == nullptr) return nullptr;
    int vel = strlen(tekst) + 1;
    unique_ptr<char>novi;
    novi.reset(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}

//Z0.4 :: Funkcija vraca max. od dva elementa
template<typename T>
T Max(T el1, T el2) { return (el1 > el2) ? el1 : el2; }
//Z0.5 :: Funkcija vraca min. od dva elementa
template<typename T>
T Min(T el1, T el2) {return (el1 < el2) ? el1 : el2;}

class Vrijeme {
protected:
    int* _sati;
    int* _minute;
    int* _sekunde;
    void Dealocate() {
        if (_sati != nullptr) { delete _sati; _sati = nullptr; }
        if (_minute != nullptr) { delete _minute; _minute = nullptr; }
        if (_sekunde != nullptr) { delete _sekunde; _sekunde = nullptr; }
    }
public:
    __declspec(property (get = GetSati, put = SetSati)) int Sati;
    __declspec(property (get = GetMinute, put = SetMinute)) int Minute;
    __declspec(property (get = GetSekunde, put = SetSekunde)) int Sekunde;

    //Z1.1
    //Vraca true ako postoji makar jedno obiljezje sa vrijednoscu nullptr
    static bool CheckIfNull(const Vrijeme& obj) {
        return (obj._sati == nullptr) || (obj._minute == nullptr) || (obj._sekunde == nullptr);
    }
    //Z1.2
    Vrijeme():_sati(nullptr),_minute(nullptr),_sekunde(nullptr){}
    //Z1.3
    Vrijeme(int sati, int minute, int sekunde) {
        _sati = new int(sati);
        _minute = new int(minute);
        _sekunde = new int(sekunde);

    }
    //Z1.4
    Vrijeme(const Vrijeme& obj) {
        assert(!CheckIfNull(obj) && "Copy ctor vrijeme");
        _sati = new int(*obj._sati);
        _minute = new int(*obj._minute);
        _sekunde = new int(*obj._sekunde);
    }
    //Z1.5
    Vrijeme(Vrijeme&& obj) {
        _sati = obj._sati;
        obj._sati = nullptr;
        _minute = obj._minute;
        obj._minute = nullptr;
        _sekunde = obj._sekunde;
        obj._sekunde = nullptr;

    }
    //Z1.6
    Vrijeme& operator =(const Vrijeme& obj) {
        if (this!=&obj)
        {
            assert(!CheckIfNull(obj) && " operator =  vrijeme");
            if (_sati == nullptr)_sati = new int;
            *_sati = *obj._sati;
            if (_minute == nullptr)_minute = new int;
            *_minute = *obj._minute;
            if (_sekunde == nullptr)_sekunde = new int;
            *_sekunde = *obj._sekunde;
        }
        return *this;
    }
    //Z1.7
    void SetSati(int sati) {
        if (_sati == nullptr)_sati = new int;
        *_sati = sati;
    }
    void SetMinute(int minute) {
        if (_minute == nullptr)_minute = new int;
        *_minute = minute;
    }
    void SetSekunde(int sekunde) {
        if (_sekunde == nullptr)_sekunde = new int;
        *_sekunde = sekunde;
    }
    //Z1.8
    int GetSati() const {
        assert(_sati != nullptr);
        return *_sati;
    }
    int GetMinute() const {
        assert(_minute != nullptr);
        return *_minute;
    }
    int GetSekunde() const {
        assert(_sekunde != nullptr);
        return *_sekunde;
    }
    //Z1.9 :: koristenjem rand() funkcije generisati slucajne vrijednosti za novi objekat(Vrijeme)
    static Vrijeme GetRandomVrijeme() {
        Vrijeme obj;
        obj.Sati = rand() % 24; //vrijednost izmedju [0-23]
        obj.Minute = rand() % 60; //vraca vrijednost izmedju [0-59]
        obj.Sekunde = rand() % 60; //vraca vrijednost izmedju [0-59]
        return obj;
    }
    //Z1.10
    bool CheckIfValidnoVrijeme() {
        if (Sati < 0 || Sati> 23)
            return false;
        if (Minute < 0 || Minute> 60)
            return false;
        if (Sekunde < 0 || Sekunde> 60)
            return false;
        return true;
    }
    //Z1.11
    ~Vrijeme() {
        Dealocate();
    }
};
//Z1.12
ostream& operator << (ostream& COUT, const Vrijeme& obj) {
    COUT << obj.Sati << ":" << obj.Minute << ":" << obj.Sekunde << "\n";
    return COUT;
}
//Z1.13
bool operator == (const Vrijeme& v1, const Vrijeme& v2) {
    return v1.Sati == v2.Sati && v1.Minute == v2.Minute && v1.Sekunde == v2.Sekunde;
}
bool operator != (const Vrijeme& v1, const Vrijeme& v2);
bool operator > (const Vrijeme& v1, const Vrijeme& v2);
bool operator >= (const Vrijeme& v1, const Vrijeme& v2);
bool operator < (const Vrijeme& v1, const Vrijeme& v2);
bool operator <= (const Vrijeme& v1, const Vrijeme& v2);

class DatumVrijeme : public Vrijeme {
private:
    shared_ptr<int> _dan;
    shared_ptr<int> _mjesec;
    shared_ptr<int> _godina;
public:
    __declspec(property (get = GetDan, put = SetDan)) int Dan;
    __declspec(property (get = GetMjesec, put = SetMjesec)) int Mjesec;
    __declspec(property (get = GetGodina, put = SetGodina)) int Godina;
    //Z2.1
    static bool CheckIfNull(const DatumVrijeme& obj) {
        return (obj._dan == nullptr) || (obj._mjesec == nullptr) || (obj._godina == nullptr);
    }
    //Z2.2
    DatumVrijeme(){}
    //Z2.3
    DatumVrijeme(int dan, int mjesec, int godina, int sati, int minute, int sekunde) : Vrijeme(sati,minute,sekunde)
    {
        _dan = make_shared<int>(dan);
        _mjesec = make_shared<int>(mjesec);
        _godina = make_shared<int>(godina);
    }
    //Z2.4
    DatumVrijeme(const DatumVrijeme& obj) : Vrijeme(obj)
    {
        assert(!CheckIfNull(obj) && "copy ctor datumvrijeme");
        _dan = make_shared<int>(*obj._dan);
        _mjesec = make_shared<int>(*obj._mjesec);
        _godina = make_shared<int>(*obj._godina);
    }
    //Z2.5
    DatumVrijeme(DatumVrijeme&& obj) : Vrijeme(move(obj))
    {
        _dan = obj._dan;
        obj._dan = nullptr;
        _mjesec = obj._mjesec;
        obj._mjesec = nullptr;
        _godina = obj._godina;
        obj._godina = nullptr;
    }
    //Z2.6 
    DatumVrijeme& operator =(const DatumVrijeme& obj) {
        if (this!=&obj)
        {
            (Vrijeme&)(*this) = obj;
            assert(!CheckIfNull(obj) && "operator = datumvrijeme");
            if (_dan == nullptr)_dan = make_shared<int>();
            *_dan = *obj._dan;
            if (_mjesec == nullptr)_mjesec = make_shared<int>();
            *_mjesec = *obj._mjesec;
            if (_godina == nullptr)_godina = make_shared<int>();
            *_godina = *obj._godina;
        }
        return *this;
    }
    //Z2.7
    void SetDan(int dan) {
        if (_dan == nullptr)_dan = make_shared<int>();
        *_dan = dan;
    }
    void SetMjesec(int mjesec) {
        if (_mjesec == nullptr)_mjesec = make_shared<int>();
        *_mjesec = mjesec;
    }
    void SetGodina(int godina) {
        if (_godina == nullptr)_godina = make_shared<int>();
        *_godina = godina;
    }
    //Z2.8
    int GetDan() const {
        assert(_dan != nullptr && "_dan geter");
        return *_dan;
    }
    int GetMjesec() const {
        assert(_mjesec != nullptr && "_mjesec geter");
        return *_mjesec;
    }
    int GetGodina() const {
        assert(_godina != nullptr && "_godina geter");
        return *_godina;
    }
    //Z2.9
    bool CheckIfValidnoDatumVrijeme() {
        if (!CheckIfValidnoVrijeme())
            return false;
        if (Godina < MIN_GODINA || Godina > MAX_GODINA)
            return false;
        if (Mjesec < Januar || Mjesec > Decembar)
            return false;
        if (Dan < 1 || Dan> 31)
            return false;
        bool (*CheckIfPrijestupna) (int) = [](int godina) {
            return (((godina % 4 == 0) && (godina % 100 != 0)) || (godina % 400 == 0));
        };
        if (Mjesec == Februar)
            return CheckIfPrijestupna(Godina) ? Dan <= 29 : Dan <= 28;
        if (Mjesec == April || Mjesec == Juni || Mjesec == Septembar || Mjesec == Novembar)
            return Dan <= 30;
        return true;
    }
    //Z2.10 Obratiti paznju na validnost novokreiranog objekta (DatumVrijeme) sa slucajnim vrijednostima
    static DatumVrijeme GetRandomDatumVrijeme() {
        auto vrijeme = Vrijeme::GetRandomVrijeme();
        DatumVrijeme datumVrijeme(1, 1, 2021, vrijeme.Sati, vrijeme.Minute, vrijeme.Sekunde);
        do {
            datumVrijeme.Dan = rand() % 31 + 1; //vrijednost izmedju [1-31]
            datumVrijeme.Mjesec = rand() % 12 + 1; //vraca vrijednost izmedju [1-12]
            datumVrijeme.Godina = rand() % 2021 + 1; //vraca vrijednost izmedju [1-2021]
        } while (!datumVrijeme.CheckIfValidnoDatumVrijeme());
        return datumVrijeme;

    }
    //Z2.11
    ~DatumVrijeme(){}

};
//Z2.12
ostream& operator << (ostream& COUT, const DatumVrijeme& obj) {
    COUT << obj.Dan << "." << obj.Mjesec << "." << obj.Godina << "\n";
    return COUT;
}
//Z2.13
bool operator == (const DatumVrijeme& d1, const DatumVrijeme& d2) {
    return d1.Dan == d2.Dan
        && d1.Mjesec == d2.Mjesec
        && d1.Godina == d2.Godina
        && (Vrijeme&)d1 == (Vrijeme&)d2;

}
bool operator !=(const DatumVrijeme& d1, const DatumVrijeme& d2);
//Z2.14
bool operator >(const DatumVrijeme& d1, const DatumVrijeme& d2);
bool operator >= (const DatumVrijeme& d1, const DatumVrijeme& d2);
bool operator < (const DatumVrijeme& d1, const DatumVrijeme& d2);
bool operator <= (const DatumVrijeme& d1, const DatumVrijeme& d2);

template<class T, int max> //max oznacava velicinu niza
class Array {
private:
    int _trenutno; //trenutno elemenata 
    T* _elementi[max] = { nullptr }; //staticki niz pokazivaca
    bool _omoguciDupliranje;
    void Dealocate() {
        if (_elementi != nullptr)
           for (size_t i = 0; i < _trenutno; i++)
           {
               delete _elementi[i]; 
               _elementi[i] = nullptr; 
           }    
    }
public:
    __declspec(property (get = GetTrenutno)) int Length;
    //Z3.1
    Array(bool omoguciDupliranje = true) {
        _trenutno = 0;
        _omoguciDupliranje = omoguciDupliranje;
    }
    //Z3.2
    Array(const Array<T, max>& obj) {
        _trenutno = obj._trenutno;
        _omoguciDupliranje = obj._omoguciDupliranje;
        
        for (size_t i = 0; i < _trenutno; i++)
            _elementi[i] = new T(*obj._elementi[i]);
    }
    //Z3.3
    Array(Array<T, max>&& obj) {
        _trenutno = obj._trenutno;
        _omoguciDupliranje = obj._omoguciDupliranje;
        for (size_t i = 0; i < _trenutno; i++)
        {
            _elementi[i] = obj._elementi[i];
            _elementi[i] = nullptr;
        }
    }
    //Z3.4
    Array<T, max>& operator=(const Array<T, max>& obj) {
        if (this!= &obj)
        {
            _trenutno = obj._trenutno;
            _omoguciDupliranje = obj._omoguciDupliranje;
            for (size_t i = 0; i < _trenutno; i++)
            {
                delete _elementi[i];
                _elementi[i] = nullptr;
            }
            assert(_elementi != nullptr && "array operator = _elementi");
            for (size_t i = 0; i < _trenutno; i++)
                _elementi[i] = new T(*obj._elementi[i]);
        }
        return *this;
    }

    //Z3.5 :: Osigurati da je index unutar opsega [0,_trenutno-1]. Koristiti genericke funkcije 'Min' i 'Max' 
    T& operator [] (int index) const
    { 
        assert(_elementi != nullptr && "[]operator");
        return *_elementi[index]; 
    }
    //Z3.6 :: Dodati (alocirati u niz) novi element
    bool operator +=(T noviElement) {
        if (_trenutno == max) return false;
        if (_omoguciDupliranje == false)
            for (size_t i = 0; i < _trenutno; i++)
                if (*_elementi[i] == noviElement)
                    return false;
        _elementi[_trenutno] = new T(noviElement);
        _trenutno++;
        return true;
    }
    //Z3.7 :: Izbrisati (dealocirati) zadnji element i umanjiti brojac
    bool UkloniZadnjiElement() {
        if (_trenutno >= max)return false;
        delete _elementi[_trenutno - 1]; _elementi[_trenutno - 1] = nullptr;
        _trenutno--;
        return true;
    }
    //Z3.8
    bool CheckIfSadrzi(T element) {
        for (size_t i = 0; i < _trenutno; i++)
            if (*_elementi[i] == element)
                return true;
        return false;
    }
    //Z3.9 :: Sortiranje elemenata pomocu algoritma za sortiranje "Bubble Sort"
    void Sortiraj(bool reverse = false) {
        auto operacija = [&reverse](T& el1, T& el2) {
            return (reverse) ? el1 < el2 : el1 > el2;
        };

        for (int i = 0; i < _trenutno - 1; i++) {
            for (int j = 0; j < _trenutno - i - 1; j++) {
                if (operacija(*_elementi[j], *_elementi[j + 1])) {
                    T temp = *_elementi[j];
                    *_elementi[j] = *_elementi[j + 1];
                    *_elementi[j + 1] = temp;
                }
            }

        }
    }
    //Z3.10
    int GetTrenutno() const { return _trenutno; }
    int GetMaxElemenata() const;
    bool GetOmoguciDupliranje() const;
    //Z3.11
    ~Array() {
        Dealocate();
    }
};
//Z3.12
template<class T, int max>
ostream& operator << <>(ostream& COUT, const Array<T, max>& obj) {
    for (int i = 0; i < obj.Length; i++)
        COUT << obj[i] << endl;
    return COUT;

}
//Z3.13
template<class T, int max>
void Ispis(const Array<T, max>& obj, const char* delimiter = " ") {
    for (int i = 0; i < obj.Length; i++)
        cout << obj[i] << delimiter;
    cout << endl;
}
//Z3.14
template<class T, int max>
bool operator == (const Array<T, max>& arr1, const Array<T, max>& arr2) {
    return arr1.Length == arr2.Length;

}
template<class T, int max>
bool operator != (const Array<T, max>& arr1, const Array<T, max>& arr2);

class Osoba {
protected:
    shared_ptr<char> _ime;
    shared_ptr<char> _prezime;
    unique_ptr<DatumVrijeme> _datumRodjenja;
    Spol _spol;
    
public:
    __declspec(property (get = GetIme, put = SetIme)) const char* Ime;
    __declspec(property (get = GetPrezime, put = SetPrezime)) const char* Prezime;
    __declspec(property (get = GetDatumRodjenja, put = SetDatumRodjenja)) DatumVrijeme DatumRodjenja;
    __declspec(property (get = GetSpol, put = SetSpol)) Spol Spol_;

    //Z4.1
    Osoba(Spol spol = Spol::Zenski) {
        _spol = spol;
    }
    //Z4.2
    Osoba(const char* ime, const char* prezime, DatumVrijeme datumRodjenja, Spol spol) 
    {
        _ime = SharedAlokator(ime);
        _prezime = SharedAlokator(prezime);
        _datumRodjenja = make_unique<DatumVrijeme>(datumRodjenja);
        _spol = spol;
    }
    //Z4.3
    Osoba(const Osoba& obj) {
        _ime = SharedAlokator(obj._ime.get());
        _prezime = SharedAlokator(obj._prezime.get());
        _datumRodjenja = make_unique<DatumVrijeme>(*obj._datumRodjenja);
        _spol = obj._spol;

    }
    //Z4.4
    Osoba(Osoba&& obj) : _datumRodjenja(move(obj._datumRodjenja)) {
        _ime = obj._ime;
        obj._ime = nullptr;
        _prezime = obj._prezime;
        obj._prezime = nullptr;
        _spol = obj._spol;
    }
    //Z4.5
    Osoba& operator = (const Osoba& obj) {
        if (this != &obj)
        {
            _ime = SharedAlokator(obj._ime.get());
            _prezime = SharedAlokator(obj._prezime.get());
            if (_datumRodjenja == nullptr) _datumRodjenja = make_unique<DatumVrijeme>();
            *_datumRodjenja = *obj._datumRodjenja;
            _spol = obj._spol;
        }
        return *this;
    }
    //Z4.6
    const char* GetIme() const { return _ime.get(); }
    const char* GetPrezime() const{ return _prezime.get(); }
    DatumVrijeme GetDatumRodjenja() const {
        assert(_datumRodjenja != nullptr && "get::Osoba::datumrodjenja");
        return *_datumRodjenja;
    }
    Spol GetSpol() const { return _spol; }
    //Z4.7
    void SetIme(const char* ime) {
        _ime = SharedAlokator(ime);

    }
    void SetPrezime(const char* prezime) {
        _prezime = SharedAlokator(prezime);
    }
    void SetDatumRodjenja(DatumVrijeme datumRodjenja) {
        if (_datumRodjenja == nullptr) 
            _datumRodjenja = make_unique<DatumVrijeme>(datumRodjenja);
        *_datumRodjenja = datumRodjenja;
    }
    void SetSpol(Spol spol) { _spol = spol; }
    //4.8
    ~Osoba(){
    }
};
//Z4.9
ostream& operator << (ostream& COUT, const Osoba& osoba) {
    COUT << "Ime i prezime: " << osoba.Ime << " " << osoba.Prezime << endl;
    COUT << "Datum rodjenja: " << osoba.DatumRodjenja << endl;
    COUT << "Spol: " << ((osoba.Spol_ == Spol::Muski) ? "Muski" : "Zenski") << endl;
    return COUT;

}
//Z4.10
bool operator == (const Osoba& o1, const Osoba& o2) {
    return strcmp(o1.Ime, o2.Ime) == 0 && strcmp(o1.Prezime, o2.Prezime) == 0;

}
bool operator != (const Osoba& o1, const Osoba& o2) {
    return !(o1 == o2);
}

class Pjevac : public Osoba {
    const char* _zanr;
    vector<const char*> _instrumenti;
    unique_ptr<char> _aktivan; // Npr. 1978 - present
    void Dealocate()
    {
        if (_zanr != nullptr) { delete[]_zanr; _zanr = nullptr; }
    }
public:
    __declspec(property (get = GetZanr, put = SetZanr)) const char* Zanr;
    __declspec(property (get = GetInstrumenti)) vector<const char*> Instrumenti;
    __declspec(property (get = GetAktivan, put = SetAktivan)) const char* Aktivan;
    //Z5.1
    Pjevac():_zanr(nullptr){}
    //Z5.2
    Pjevac(const char* ime, const char* prezime, DatumVrijeme dv, Spol sp, const char* zanr, const char* aktivan)
        : Osoba(ime, prezime, dv, sp)
    {
        _zanr = Alokator(zanr);
        _aktivan = UniqueAlokator(aktivan);
    }
    //Z5.3
    Pjevac(const Pjevac& obj) : Osoba(obj),_instrumenti(obj._instrumenti)
    {
        _zanr = Alokator(obj._zanr);
        _aktivan = UniqueAlokator(obj._aktivan.get());

    }
    //Z5.4
    Pjevac(Pjevac&& obj) : Osoba(move(obj)),_instrumenti(move(obj._instrumenti)),_aktivan(move(obj._aktivan))
    {
        _zanr = obj._zanr;
        obj._zanr = nullptr;
    }
    //Z5.5
    Pjevac& operator = (const Pjevac& obj) {
        if (this!=&obj)
        {
            (Osoba&)(*this) = obj;
            delete[]_zanr;
            _zanr = Alokator(obj._zanr);
            _instrumenti = obj._instrumenti;
            _aktivan = UniqueAlokator(obj._aktivan.get());
        }
        return *this;
    }
    //Z5.6
    const char* GetZanr()const { return _zanr;}
    const char* GetAktivan()const { return _aktivan.get(); }
    vector<const char*> GetInstrumenti() const { return _instrumenti; }
    //Z5.7
    void SetZanr(const char* zanr) {
        delete[]_zanr;
        _zanr = Alokator(zanr);
    }
    void SetAktivan(const char* aktivan) {
        _aktivan = UniqueAlokator(aktivan);
    }
    //Z5.8
    void DodajInstrument(const char* instrument) {
        _instrumenti.push_back(instrument);
    }
    //Z5.9
    ~Pjevac() { Dealocate(); }
};
//Z5.10
ostream& operator << (ostream& COUT, const Pjevac& pjevac) {
    COUT << (Osoba&)pjevac;
    COUT << "Muzicki zanr: " << pjevac.Zanr << endl;
    COUT << "Aktivan (od-do): " << pjevac.Aktivan << endl;
    COUT << "Instrumenti: ";
    for (size_t i = 0; i < pjevac.Instrumenti.size(); i++)
        COUT << pjevac.Instrumenti[i] << ", ";
    return COUT;

}
//Z5.11
bool operator == (const Pjevac& p1, const Pjevac& p2) {
    return (Osoba&)p1 == (Osoba&)p2;
}
bool operator != (const Pjevac& p1, const Pjevac& p2);

class Pjesma {
    const char* _naziv;
    char* _tekst;
    pair<int, int> _trajanje; // <minute, sekunde> [Po defaultu postaviti na <0,0>]
    shared_ptr<char> _tekstopisac;
    int _trenutnoZanrova;
    char* _zanrovi[5] = { nullptr };
    void Dealocate() {
        if (_naziv != nullptr) { delete[]_naziv; _naziv = nullptr; }
        if (_tekst != nullptr) { delete[]_tekst; _tekst = nullptr; }
        for (size_t i = 0; i < _trenutnoZanrova; i++)
        {
            delete _zanrovi[i];
            _zanrovi[i] = nullptr;
        }
    }
public:
    __declspec(property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    __declspec(property (get = GetTekst, put = SetTekst)) const char* Tekst;
    __declspec(property (get = GetTrajanje, put = SetTrajanje)) pair<int, int> Trajanje;
    __declspec(property (get = GetTekstopisac, put = SetTekstopisac)) const char* Tekstopisac;

    //Z6.1
    Pjesma() : _naziv(nullptr),_tekst(nullptr),_trajanje(0,0) {
        _trenutnoZanrova = 0;
    }
    //Z6.2
    Pjesma(const char* naziv, const char* tekst, pair<int, int> trajanje, const char* tekstopisac):_trajanje(trajanje.first,trajanje.second)
    {
        _naziv = Alokator(naziv);
        _tekst = Alokator(tekst);
        _tekstopisac = SharedAlokator(tekstopisac);
        _trenutnoZanrova = 0;
    }
    //Z6.3
    Pjesma(const Pjesma& obj){
        _naziv = Alokator(obj._naziv);
        _tekst = Alokator(obj._tekst);
        _trajanje = obj._trajanje;
        _tekstopisac = SharedAlokator(obj._tekstopisac.get());
        _trenutnoZanrova = obj._trenutnoZanrova;
        for (size_t i = 0; i < _trenutnoZanrova; i++)
            _zanrovi[i] = Alokator(obj._zanrovi[i]);
    }
    //Z6.4
    Pjesma(Pjesma&& obj):_tekstopisac(move(obj._tekstopisac)),_trajanje(move(obj._trajanje)) {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
        _tekst = obj._tekst;
        obj._tekst = nullptr;
        _trenutnoZanrova = obj._trenutnoZanrova;
        obj._trenutnoZanrova = 0;
        for (size_t i = 0; i < _trenutnoZanrova; i++)
        {
            _zanrovi[i] = obj._zanrovi[i];
            obj._zanrovi[i] = nullptr;
        }
    }
    //Z6.5
    Pjesma& operator = (const Pjesma& obj) {
        if (this!=&obj)
        {
            delete[]_naziv;
            _naziv = Alokator(obj._naziv);
            delete[]_tekst;
            _tekst = Alokator(obj._tekst);
            _trajanje = obj._trajanje;
            _tekstopisac = SharedAlokator(obj._tekstopisac.get());
            _trenutnoZanrova = obj._trenutnoZanrova;
            for (size_t i = 0; i < _trenutnoZanrova; i++)
            {
                delete _zanrovi[i];
                _zanrovi[i] = nullptr;
            }
            assert(_zanrovi != nullptr && "zanrovi operator=");
            for (size_t i = 0; i < _trenutnoZanrova; i++)
                _zanrovi[i] = Alokator(obj._zanrovi[i]);
        }
        return *this;
    }
    //Z6.6
    const char* GetNaziv() const { return _naziv; }
    const char* GetTekst() const { return _tekst; }
    pair<int, int> GetTrajanje()const { return _trajanje; }
    const char* GetTekstopisac()const { return _tekstopisac.get(); }
    int GetTrenutno()const { return _trenutnoZanrova; }

    const char* GetZanr(int index) const { return _zanrovi[index]; }
    //Z6.7
    void SetNaziv(const char* naziv) {
        delete[]_naziv;
        _naziv = Alokator(naziv);
    }
    void SetTekst(const char* tekst) {
        delete[]_tekst;
        _tekst = Alokator(tekst);
    }
    void SetTrajanje(pair<int, int> trajanje) { _trajanje = trajanje; }
    void SetTekstopisac(const char* tekstopisac)
    {
        _tekstopisac = SharedAlokator(tekstopisac);
    }
    //Z6.8
    bool DodajZanr(const char* zanr) {
        if (_trenutnoZanrova >= 5)return false;
        _zanrovi[_trenutnoZanrova] = Alokator(zanr);
        _trenutnoZanrova++;
        return true;
    }
    //Z6.9
    ~Pjesma() { Dealocate(); }
};
//Z6.10
ostream& operator << (ostream& COUT, const Pjesma& obj) {
    COUT << "Naziv: " << obj.Naziv << endl;
    COUT << "Tekst: " << obj.Tekst << endl;
    COUT << "Trajanje (mm:ss): " << obj.Trajanje.first << ":" << obj.Trajanje.second << endl;
    COUT << "Tekstopisac: " << obj.Tekstopisac << endl;
    COUT << "Zanrovi: ";
    for (int i = 0; i < obj.GetTrenutno(); i++)
        COUT << obj.GetZanr(i) << ", ";
    COUT << endl;
    return COUT;

}
//Z6.11
bool operator == (const Pjesma& p1, const Pjesma& p2) {
    return p1.Trajanje == p2.Trajanje;
}
bool operator != (const Pjesma& p1, const Pjesma& p2);

class Album {
    char* _naziv;
    Pjevac* _pjevac;
    Array<Pjesma, 100> _pjesme;
    vector<const char*> _izdavackeKuce;
    void Dealocate() {
        if (_naziv != nullptr) { delete[]_naziv; _naziv = nullptr; }
        if (_pjevac != nullptr) { delete[]_pjevac; _pjevac = nullptr; }
    }
public:
    __declspec(property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    __declspec(property (get = GetPjevac, put = SetPjevac)) Pjevac Pjevac_;
    __declspec(property (get = GetPjesme)) Array<Pjesma, 100> Pjesme;
    __declspec(property (get = GetIzdavackeKuce)) vector<const char*> IzdavackeKuce;
    //Z7.1
    Album():_naziv(nullptr),_pjevac(nullptr) {
        
    }
    //Z7.2
    Album(const char* naziv, Pjevac pjevac) {
        _naziv = Alokator(naziv);
        _pjevac = new Pjevac(pjevac);
    }
    //Z7.3
    Album(const Album& obj):_pjesme(obj._pjesme),_izdavackeKuce(obj._izdavackeKuce)
    {
        _naziv = Alokator(obj._naziv);
        _pjevac = new Pjevac(*obj._pjevac); 
    }
    //Z7.4
    Album(Album&& obj):_pjesme(move(obj._pjesme)),_izdavackeKuce(move(obj._izdavackeKuce))
    {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
        _pjevac = obj._pjevac;
        obj._pjevac = nullptr;

    }
    //Z7.5
    Album& operator =(const Album& obj) {
        if (this!=&obj)
        {
            delete[]_naziv; 
            _naziv = Alokator(obj._naziv);
            if (_pjevac == nullptr) _pjevac = new Pjevac;
            *_pjevac = *obj._pjevac;
            _pjesme = obj._pjesme;
            _izdavackeKuce = obj._izdavackeKuce;
        }
        return *this;
    }
    //Z7.6
    const char* GetNaziv() const { return _naziv; }
    Pjevac GetPjevac()const { return *_pjevac; }
    Array<Pjesma, 100> GetPjesme() const { return _pjesme; }
    vector<const char*> GetIzdavackeKuce() const { return _izdavackeKuce; }
    //Z7.7
    void SetNaziv(const char* naziv) {
        delete[]_naziv;
        _naziv = Alokator(naziv);
    }
    void SetPjevac(Pjevac pjevac) {
        if (_pjevac == nullptr) _pjevac = new Pjevac;
        *_pjevac = pjevac;
    }
    //Z7.8
    bool operator+= (Pjesma novaPjesma) {
        return _pjesme += novaPjesma;
    }
    //Z7.9
    void operator+= (const char* izdavackaKuca) {
        _izdavackeKuce.push_back(izdavackaKuca);
    }
    //Z7.10
    ~Album() { Dealocate(); }
};
//Z7.11
ostream& operator <<(ostream& COUT, const Album& obj) {
    COUT << "Naziv: " << obj.Naziv << endl;
    COUT << "Pjevac: " << endl << obj.Pjevac_ << endl;
    COUT << ".............Pjesme ........................." << endl;
    Ispis(obj.Pjesme, "\n");
    COUT << "Izdavacke kuce: " << endl;
    for (size_t i = 0; i < obj.IzdavackeKuce.size(); i++)
        COUT << obj.IzdavackeKuce[i] << ", ";
    COUT << endl;
    return COUT;

}
//Z7.12
bool operator == (const Album& a1, const Album& a2) {
    return a1.Naziv == a2.Naziv;
}
bool operator !=(const Album& a1, const Album& a2);

auto IspisiPoruku = [](const char* tipFunkcije, bool success) {
    cout << tipFunkcije << " se izvrsio " << ((success) ? "uspjesno!" : "bezuspjesno!") << endl;
};

void Zadatak1() {
    cout << "Generisanje slucajnog vremena: " << endl;
    Vrijeme vrijeme = Vrijeme::GetRandomVrijeme();
    cout << vrijeme << endl;
    //
    Vrijeme vrijeme2(vrijeme.Sati, vrijeme.Minute, vrijeme.Sekunde);
    IspisiPoruku("User-defined ctor", vrijeme2 == vrijeme);
    Vrijeme vrijeme3(vrijeme);
    IspisiPoruku("Copy ctor", vrijeme3 == vrijeme);
    Vrijeme vrijeme4(move(vrijeme2));
    IspisiPoruku("Move ctor", vrijeme4 == vrijeme);
    Vrijeme vrijeme5;
    vrijeme5 = vrijeme;
    IspisiPoruku("Copy assignment operator", vrijeme5 == vrijeme);
    
    //Za [27.4]
    cout << endl;
    Vrijeme izlazakSunca(5, 48, 0);
    cout << izlazakSunca << " => " << (izlazakSunca.CheckIfValidnoVrijeme() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    Vrijeme podne(12, 47, 0);
    cout << podne << " => " << (podne.CheckIfValidnoVrijeme() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    Vrijeme zalazakSunca(19, 50, 0);
    cout << zalazakSunca << " => " << (zalazakSunca.CheckIfValidnoVrijeme() ? "validno vrijeme" : "nevalidno vrijeme") << endl;
    cout << "\nDealokacija" << endl;
}
void Zadatak2() {
    cout << "Generisanje slucajnog datuma i vremena: " << endl;
    DatumVrijeme dv = DatumVrijeme::GetRandomDatumVrijeme();
    cout << dv << endl;
    
    DatumVrijeme dv2(dv.Dan, dv.Mjesec, dv.Godina, dv.Sati, dv.Minute, dv.Sekunde);
    IspisiPoruku("User-defined ctor", dv2 == dv);
    DatumVrijeme dv3(dv);
    IspisiPoruku("Copy ctor", dv3 == dv);
    DatumVrijeme dv4(move(dv2));
    IspisiPoruku("Move ctor", dv4 == dv);
    DatumVrijeme dv5;
    dv5 = dv;
    IspisiPoruku("Copy assignment operator", dv5 == dv);
    
    cout << "\nDealokacija" << endl;
}
void Zadatak3() {
    const int maxElemenata = 100;
    Array<int, maxElemenata> randomNumbers;
    cout << "Dodavanje " << maxElemenata << " elemenata!" << endl;
    for (int i = 0; i < maxElemenata; i++)
        randomNumbers += rand() % 100;
    int toRemove = 75;
    cout << "Uklanjanje " << toRemove << " elemenata!" << endl;
    for (int i = 0; i < 75; i++)
        randomNumbers.UkloniZadnjiElement();
    cout << "Ostalo nam je " << maxElemenata - toRemove << " elemenata!" << endl;
    Ispis(randomNumbers, ", ");
    
    //Sortiranje Array<int,max>
    cout << "Sortiranje [ASCENDING]: " << endl;
    randomNumbers.Sortiraj(false);
    Ispis(randomNumbers, ", ");
    cout << "Sortiranje [DESCENDING]: " << endl;
    randomNumbers.Sortiraj(true);
    Ispis(randomNumbers, ", ");
    //
    Array<int, maxElemenata> arr2(randomNumbers);
    IspisiPoruku("Copy ctor", arr2 == randomNumbers);
    
    Array<int, maxElemenata> arr3(move(arr2));
    IspisiPoruku("Move ctor", arr3 == randomNumbers);
    
    Array<int, maxElemenata> arr4;
    arr4 = randomNumbers;
    IspisiPoruku("Copy assignment operator", arr4 == randomNumbers);
    cout << "\nTestiranje Array<DatumVrijeme,int> \n";
    Array<DatumVrijeme, 10> datumi;
    for (int i = 0; i < 10; i++)
        datumi += DatumVrijeme::GetRandomDatumVrijeme();
    Ispis(datumi, "\n");
    
    //Sortiranje Array<Datum, max>;
    //cout << "Sortiranje [ASCENDING]: " << endl;
    //datumi.Sortiraj(false);
    //Ispis(datumi, "\n");
    //cout << "Sortiranje [DESCENDING]: " << endl;
    //datumi.Sortiraj(true);
    //Ispis(datumi, "\n");
    cout << endl;
    cout << "\nDealokacija" << endl;
}
void Zadatak4() {
    Osoba realDonaldTrump;
    realDonaldTrump.Ime = "Donald J.";
    realDonaldTrump.Prezime = "Trump";
    realDonaldTrump.DatumRodjenja = DatumVrijeme(13, 5, 1945, 17, 30, 0);
    realDonaldTrump.Spol_ = Spol::Muski;
    cout << realDonaldTrump << endl;
    
    Osoba jobsPresident(realDonaldTrump.Ime, realDonaldTrump.Prezime, realDonaldTrump.DatumRodjenja, realDonaldTrump.Spol_);
    IspisiPoruku("User-defined ctor", jobsPresident == realDonaldTrump);
    Osoba borisJohnson(realDonaldTrump);
    IspisiPoruku("Copy ctor", borisJohnson == realDonaldTrump);
    Osoba magaPresident(move(jobsPresident));
    IspisiPoruku("Move ctor", magaPresident == realDonaldTrump);
    Osoba o4;
    o4 = realDonaldTrump;
    IspisiPoruku("Copy assignment", o4 == realDonaldTrump);
    cout << endl;
    cout << "\nDealokacija" << endl;
}
void Zadatak5() {
    Pjevac theRocketMan;
    theRocketMan.Ime = "Kim";
    theRocketMan.Prezime = "Jong-un";
    theRocketMan.DatumRodjenja = DatumVrijeme(32, 12, 1940, 01, 00, 00);
    theRocketMan.Spol_ = Spol::Muski;
    theRocketMan.Zanr = "K-pop";
    theRocketMan.Aktivan = "2011-present";
    theRocketMan.DodajInstrument("bubnjevi");
    theRocketMan.DodajInstrument("bongo");
    theRocketMan.DodajInstrument("klavir");
    cout << theRocketMan << endl;
    
    Pjevac supremeFrontman(theRocketMan.Ime, theRocketMan.Prezime,
        theRocketMan.DatumRodjenja, theRocketMan.Spol_, theRocketMan.Zanr, theRocketMan.Aktivan);
    supremeFrontman.DodajInstrument("bubnjevi");
    supremeFrontman.DodajInstrument("bongo");
    supremeFrontman.DodajInstrument("klavir");
    
    IspisiPoruku("User-defined ctor", supremeFrontman == theRocketMan);
    Pjevac kPopPrince(theRocketMan);
    IspisiPoruku("Copy ctor", kPopPrince == theRocketMan);
    Pjevac sendMeNukes(move(supremeFrontman));
    IspisiPoruku("Move ctor", sendMeNukes == theRocketMan);
    Pjevac p4;
    p4 = theRocketMan;
    IspisiPoruku("Copy assignment", p4 == theRocketMan);
    cout << endl;
    cout << "Dealokacija" << endl;
}
void Zadatak6() {
    Pjesma horseWithNoName;
    horseWithNoName.Naziv = "America - A Horse With No Name";
    horseWithNoName.Tekst = "On the first part of the journey I was looking at all the life";
    horseWithNoName.Trajanje = make_pair<int, int>(4, 7);
    horseWithNoName.Tekstopisac = "Dewey Bunnell";
    horseWithNoName.DodajZanr("folk rock");
    horseWithNoName.DodajZanr("soft rock");
    horseWithNoName.DodajZanr("country rock");
    cout << horseWithNoName;
    
    Pjesma gtaSaSong(horseWithNoName.Naziv, horseWithNoName.Tekst, horseWithNoName.Trajanje, horseWithNoName.Tekstopisac);
    gtaSaSong.DodajZanr("folk rock");
    gtaSaSong.DodajZanr("soft rock");
    gtaSaSong.DodajZanr("country rock");
    IspisiPoruku("User-defined ctor", gtaSaSong == horseWithNoName);
    Pjesma kdistFTW(horseWithNoName);
    IspisiPoruku("Copy ctor", kdistFTW == horseWithNoName);
    Pjesma breakingBadSong(move(gtaSaSong));
    IspisiPoruku("Move ctor", breakingBadSong == horseWithNoName);
    Pjesma joeysFailedAudition;
    joeysFailedAudition = horseWithNoName;
    IspisiPoruku("Copy assignment", joeysFailedAudition == horseWithNoName);
    cout << endl;
    cout << "Dealokacija" << endl;
}
void Zadatak7() {
    Album finalHour;
    finalHour.Naziv = "Face to face";
    //finalHour.Pjevac_ = Pjevac("Phil", "Collins", DatumVrijeme(13, 5, 1951, 14, 30, 00), Spol::Muski, "Pop, soft rock", "1963-2011");
    
    Pjesma inTheAirTonight("In the air tonight", "I can feel it coming in the air tonight...", make_pair(5, 34), "Phil Collins");
    inTheAirTonight.DodajZanr("Experimental pop");
    inTheAirTonight.DodajZanr("Soft rock");
    Pjesma anotherDay("Another day in paradise", "She calls out to the man on the street...", make_pair(4, 40), "Phil Collins");
    anotherDay.DodajZanr("Soft rock");
    Pjesma rainItDown("I Wish It Would Rain Down", "You know I never meant to see you again...", make_pair(4, 11), "Phil Collins");
    rainItDown.DodajZanr("Pop");
    finalHour += inTheAirTonight;
    finalHour += anotherDay;
    finalHour += rainItDown;
    finalHour += "Atlas Music Publishing";
    finalHour += "Concord Music Publising";
    finalHour += "Big Deal Music";
    finalHour += "Bluewater Music";
    //cout << finalHour << endl;
   // Album ritual(finalHour.Naziv, finalHour.Pjevac_);
   //ritual += inTheAirTonight;
   //ritual += anotherDay;
   //ritual += rainItDown;
   //ritual += "Atlas Music Publishing";
   //ritual += "Concord Music Publising";
   //ritual += "Big Deal Music";
   //ritual += "Bluewater Music";
  /*  IspisiPoruku("User-defined ctor", ritual == finalHour);
    Album copycat(finalHour);
    IspisiPoruku("Copy ctor", copycat == finalHour);
    Album stealCredit(move(ritual));
    IspisiPoruku("Move ctor", stealCredit == finalHour);
    Album imaginationLevelZero;
    imaginationLevelZero = finalHour;
    IspisiPoruku("Copy assignment", imaginationLevelZero == finalHour);*/
    cout << endl;
    cout << "Dealokacija" << endl;
}
void Menu() {
    int nastaviDalje = 1;
    while (nastaviDalje == 1) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "(6) Zadatak 6" << endl;
            cout << "(7) Zadatak 7" << endl;
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 7);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: Zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        case 6: Zadatak6(); cout << "Zadatak 6. Done." << endl; break;
        case 7: Zadatak7(); cout << "Zadatak 7. Done." << endl; break;
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


