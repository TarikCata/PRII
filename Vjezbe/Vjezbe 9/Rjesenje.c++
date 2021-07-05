#include <vector>
#include <iostream>
#include <cassert>
#include <time.h>
#include <Windows.h>
using namespace std;

int Min(int a, int b) { return (a <= b) ? a : b; }
int Max(int a, int b) { return (a >= b) ? a : b; }

//:::::::::::ZADACI::::::::::::
//Z0.1 
char* Alokator(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}

//Z0.2 :: Funkcija za alokaciju pametnog (shared_ptr) pokazivaca na niz karaktera
shared_ptr<char> SharedAlokator(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    shared_ptr<char> novi(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}

//Z0.3 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char> UniqueAlokator(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    unique_ptr<char> novi(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}
//Z0.4:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool CheckIfIsti(const char* tekst1, const char* tekst2) {
    if (tekst1 == nullptr || tekst2 == nullptr)
        return false;
    return strcmp(tekst1, tekst2) == 0;
}

//Z0.5 Provjeriti da li su dva vektora jednaka (da li imaju iste elemente)
template<class T>
bool operator == (const vector<T>& v1, const vector<T>& v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;
}
template<class T>
bool operator != (const vector<T>& v1, const vector<T>& v2) {
    return !(v1 == v2);
}
bool operator == (const vector<const char*>& v1, const vector<const char*>& v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); i++)
        if (!CheckIfIsti(v1[i], v2[i]))
            return false;
    return true;
}
bool operator != (const vector<const char*>& v1, const vector<const char*>& v2) {
    return !(v1 == v2);
}


//Simulacija ratne stateske igre
enum class Moral { Nizak = 1, Srednji, Visok };
class Vojnik {
protected:
    unique_ptr<int> _zdravlje; //[0-100] 
    unique_ptr<int> _izdrzljivost; //[0-100]
    Moral* _moral;
    vector<const char*> _oruzja;
    bool _statusZiv;
    void Dealocate() { delete _moral; _moral = nullptr; }
public:
    __declspec(property (get = GetZdravlje, put = SetZdravlje)) int Zdravlje;
    __declspec(property (get = GetIzdrzljivost, put = SetIzdrzljivost)) int Izdrzljivost;
    __declspec(property (get = GetMoral, put = SetMoral)) Moral Moral_;
    __declspec(property (get = GetOruzja, put = SetOruzja)) vector<const char*> Oruzja;
    __declspec(property (get = GetStatusZiv, put = SetStatusZiv)) bool StatusZiv;

    //Z1.1
    Vojnik(int zdravlje = 100, int izdrzljivost = 100, Moral moral = Moral::Visok, bool statusZiv = true) {
        _zdravlje = make_unique<int>(zdravlje);
        _izdrzljivost = make_unique<int>(izdrzljivost);
        _moral = new Moral(moral);
        _statusZiv = statusZiv;
    }
    //Z1.2
    Vojnik(const Vojnik& obj) : _oruzja(obj._oruzja) {
        _zdravlje = make_unique<int>(*obj._zdravlje);
        _izdrzljivost = make_unique<int>(*obj._izdrzljivost);
        _moral = new Moral(*obj._moral);
        _statusZiv = obj._statusZiv;
    }
    //Z1.3
    Vojnik(Vojnik&& obj) :_zdravlje(move(obj._zdravlje))
        , _izdrzljivost(move(obj._izdrzljivost)), _oruzja(move(obj._oruzja))
    {
        _moral = obj._moral;
        obj._moral = nullptr;
        _statusZiv = obj._statusZiv;
    }
    //Z1.4 :: Getteri
    int GetZdravlje() const { return *_zdravlje; }
    int GetIzdrzljivost() const { return *_izdrzljivost; }
    Moral GetMoral() const { return *_moral; }
    vector<const char*> GetOruzja() const { return _oruzja; }
    bool GetStatusZiv() const { return _statusZiv; }
    //Z1.5 :: Setteri
    void SetZdravlje(int zdravlje) {
        if (_zdravlje == nullptr)_zdravlje = make_unique<int>();
        *_zdravlje = zdravlje;
    }
    void SetIzdrzljivost(int izdrzljivost) {
        if (_izdrzljivost == nullptr)_izdrzljivost = make_unique<int>();
        *_izdrzljivost = izdrzljivost;
    }
    void SetMoral(Moral moral) {
        if (_moral == nullptr)_moral = new Moral();
        *_moral = moral;
    }
    void SetOruzja(vector<const char*> oruzja) { _oruzja = oruzja; }
    void SetStatusZiv(bool statusZiv) { _statusZiv = statusZiv; }
    //Z1.6
    Vojnik& operator = (const Vojnik& obj) {
        if (this != &obj)
        {
            Dealocate();
            if (_zdravlje == nullptr)_zdravlje = make_unique<int>();
            *_zdravlje = *obj._zdravlje;
            if (_izdrzljivost == nullptr)_izdrzljivost = make_unique<int>();
            *_izdrzljivost = *obj._izdrzljivost;
            if (_moral == nullptr)_moral = new Moral();
            *_moral = *obj._moral;
            _oruzja = obj._oruzja;
            _statusZiv = obj._statusZiv;
        }
        return *this;
    }
    //Z1.7
    virtual void Ispis() {
        cout << "Zdravlje: " << Zdravlje << endl;
        cout << "Izdrzljivost: " << Izdrzljivost << endl;
        cout << "Moral: ";
        switch (Moral_)
        {
        case Moral::Nizak: cout << "Nizak" << endl; break;
        case Moral::Srednji: cout << "Srednji" << endl; break;
        case Moral::Visok: cout << "Srednji" << endl; break;
        default:
            break;
        }
        for (size_t i = 0; i < Oruzja.size(); i++)
            cout << Oruzja[i] << ", ";
        cout << endl << "Status: " << ((StatusZiv) ? "Ziv" : "Nije ziv :P") << endl;

    }
    //Z1.8
    virtual ~Vojnik() { Dealocate(); }
};
//Z1.9
bool operator == (const Vojnik& v1, const Vojnik& v2) {
    return v1.GetIzdrzljivost() == v2.GetIzdrzljivost() &&
        v1.GetZdravlje() == v2.GetZdravlje();
}
bool operator != (const Vojnik& v1, const Vojnik& v2);

//interfejs
class IPonasanje {
public:
    virtual void OglasiSe() = 0;
    virtual void Napadaj(Vojnik* meta) = 0;
    virtual void OporavljajSe() = 0;
};

enum class Kategorija { Laka = 1, Srednja, Teska };
class Pjesak : public Vojnik, public IPonasanje {
protected:
    Kategorija _kategorija;
    unique_ptr<char> _oklop;
public:
    __declspec(property (get = GetKategorija, put = SetKategorija)) Kategorija Kategorija_;
    __declspec(property (get = GetOklop, put = SetOklop)) const char* Oklop;
    //Z2.1
    Pjesak(Kategorija kategorija = Kategorija::Srednja, const char* oklop = "metalni") {
        _kategorija = kategorija;
        _oklop = UniqueAlokator(oklop);
    }
    //Z2.2
    Pjesak(const Pjesak& obj) : Vojnik(obj) {
        _kategorija = obj._kategorija;
        _oklop = UniqueAlokator(obj._oklop.get());
    }
    //Z2.3
    Pjesak(Pjesak&& obj) :Vojnik(move(obj)), _oklop(move(obj._oklop)) {
        _kategorija = obj._kategorija;
    }
    //Z2.4 :: Getteri
    Kategorija GetKategorija() const { return _kategorija; }
    const char* GetOklop() const { return _oklop.get(); }
    //Z2.5 :: Setteri
    void SetKategorija(Kategorija kategorija) { _kategorija = kategorija; }
    void SetOklop(const char* oklop) { _oklop = UniqueAlokator(oklop); }
    //Z2.6
    Pjesak& operator = (const Pjesak& obj) {
        if (this != &obj)
        {
            (Vojnik&)(*this) = obj;
            _kategorija = obj._kategorija;
            _oklop = UniqueAlokator(obj._oklop.get());
        }
        return *this;
    }
    //Z2.7
    void Ispis() {
        Vojnik::Ispis();
        cout << "Kategorija: ";
        switch (Kategorija_)
        {
        case Kategorija::Laka: cout << "Laka" << endl; break;
        case Kategorija::Srednja: cout << "Srednja" << endl; break;
        case Kategorija::Teska: cout << "Teska" << endl; break;
        default:
            break;
        }
        cout << "Oklop: " << Oklop << endl;

    }
    //Z2.8 :: Ispisati poruku "Ja sam tipa <Tip Podatka>" ... 
    //Za utvrdjivanje tipa podatka, koristiti funkciju 'typeid'
    void OglasiSe() {
        cout << "Ja sam tipa --" << typeid(*this).name() << endl;
    }
    //Z2.9 :: Ovu funkciju implementirati izvan scope-a
    void Napadaj(Vojnik* meta);
    //Z2.10 :: Povecati vrijednost atributa Zdravlje za slucajnu vrijednost izmedju [0-25]
    //Pri cemu isti atribut mora ostati u opsegu vrijednosti od 0-100
    void OporavljajSe() {
        int rnd = rand() % 25;
        Zdravlje = Min(100, Zdravlje + rnd);
    }
    //Z2.11
    ~Pjesak() {}
};
//Z2.12
bool operator == (const Pjesak& p1, const Pjesak& p2) {
    return (Vojnik&)p1 == (Vojnik&)p2;
}
//Z2.13
bool operator != (const Pjesak& p1, const Pjesak& p2);

class Strijelac : public Vojnik, public IPonasanje {
protected:
    int* _municija;
public:
    __declspec(property (get = GetMunicija, put = SetMunicija)) int Municija;
    //Z3.1
    Strijelac(int municija = 50) {
        _municija = new int(municija);
    }
    //Z3.2
    Strijelac(const Strijelac& obj) : Vojnik(obj) {
        _municija = new int(*obj._municija);
    }
    //Z3.3
    Strijelac(Strijelac&& obj) : Vojnik(move(obj))
    {
        _municija = obj._municija;
        obj._municija = nullptr;
    }
    //Z3.4 :: Getteri
    int GetMunicija() const { return *_municija; }
    //Z3.5 :: Setteri
    void SetMunicija(int municija) {
        if (_municija == nullptr)_municija = new int();
        *_municija = municija;
    }
    //Z3.6
    Strijelac& operator =(const Strijelac& obj) {
        if (this != &obj)
        {
            (Vojnik&)(*this) = obj;
            if (_municija == nullptr)_municija = new int();
            *_municija = *obj._municija;
        }
        return *this;
    }
    //Z3.7
    void Ispis() {
        Vojnik::Ispis();
        cout << "Municija: " << Municija << endl;
    }

    //Z3.8 :: Ispisati poruku "Ja sam tipa <Tip Podatka>" ... 
    //Za utvrdjivanje tipa podatka, koristiti funkciju 'typeid'
    void OglasiSe() {
        cout << "Ja sam -> " << typeid(*this).name() << endl;
    }
    //Z3.9 :: Ovu funkciju implementirati izvan scope-a
    void Napadaj(Vojnik* meta);

    //Z3.10  Povecati vrijednost atributa zdravlje za slucajnu vrijednost izmedju [0-35]
    //Pri cemu isti atribut mora ostati u opsegu vrijednosti od 0-100
    void OporavljajSe() {
        int rnd = rand() % 35;
        Zdravlje = Min(100, Zdravlje + rnd);
    }
    //Z3.11
    ~Strijelac() { delete _municija; _municija = nullptr; }
};
//Z3.12
bool operator == (const Strijelac& s1, const Strijelac& s2) {
    return (Vojnik&)s1 == (Vojnik&)s2;

}
//Z3.13
bool operator != (const Strijelac& s1, const Strijelac& s2);

class Konjanik : public Vojnik, public IPonasanje {
protected:
    unique_ptr<char> _oklop;
    const char* _vrstaKonja;
    void Dealocate() { delete[]_vrstaKonja; _vrstaKonja = nullptr; }
public:
    __declspec(property (get = GetOklop, put = SetOklop)) const char* Oklop;
    __declspec(property (get = GetVrstaKonja, put = SetVrstaKonja)) const char* VrstaKonja;
    //Z4.1
    Konjanik(const char* oklop = "metalni", const char* vrstaKonja = "") {
        _oklop = UniqueAlokator(oklop);
        _vrstaKonja = Alokator(vrstaKonja);
    }
    //Z4.2
    Konjanik(const Konjanik& obj) : Vojnik(obj) {
        _oklop = UniqueAlokator(obj._oklop.get());
        _vrstaKonja = Alokator(obj._vrstaKonja);
    }
    //Z4.3
    Konjanik(Konjanik&& obj) : Vojnik(move(obj)), _oklop(move(obj._oklop)) {
        _vrstaKonja = obj._vrstaKonja;
        obj._vrstaKonja = nullptr;
    }
    //Z4.4 :: Getteri
    const char* GetOklop() const { return _oklop.get(); }
    const char* GetVrstaKonja() const {
        return _vrstaKonja;
    }
    //Z4.5 :: Setteri
    void SetOklop(const char* oklop) { _oklop = UniqueAlokator(oklop); }
    void SetVrstaKonja(const char* vrstaKonja) {
        delete[]_vrstaKonja;
        _vrstaKonja = Alokator(vrstaKonja);
    }
    //Z4.6
    Konjanik& operator = (const Konjanik& obj) {
        if (this != &obj)
        {
            (Vojnik&)(*this) = obj;
            Dealocate();
            _oklop = UniqueAlokator(obj._oklop.get());
            _vrstaKonja = Alokator(obj._vrstaKonja);
        }
        return *this;
    }
    //Z4.7  
    void Ispis() {
        Vojnik::Ispis();
        cout << "Oklop: " << Oklop << endl;
        cout << "Vrsta konja: " << VrstaKonja << endl;
    }

    //Z4.8 :: Ispisati poruku "Ja sam tipa <Tip Podatka>" ... 
    //Za utvrdjivanje tipa podatka, koristiti funkciju 'typeid'
    void OglasiSe() {
        cout << "Ja sam -> " << typeid(*this).name() << endl;
    }
    //4.9 :: Ovu funkciju implementirati izvan scope-a
    void Napadaj(Vojnik* meta);
    //Z4.10  Povecati vrijednost atributa zdravlje za slucajnu vrijednost izmedju [0-15]
    //Pri cemu isti atribut mora ostati u opsegu vrijednosti od 0-100
    void OporavljajSe() {
        int rnd = rand() % 15;
        Zdravlje = Min(100, Zdravlje + rnd);
    }
    //4.11
    ~Konjanik() { Dealocate(); }
};
//4.12
bool operator == (const Konjanik& k1, const Konjanik& k2) {
    return (Vojnik&)k1 == (Vojnik&)k2;
}
//4.13
bool operator != (const Konjanik& k1, const Konjanik& k2);

//Z2.9 ::
//Pjesak ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//*Utvrditi tip mete koristenjem 'dynamic_cast'
//U slucaju da je napad uspjesan, steta koja se nanosi je:
// ->30 (ukoliko je meta drugi pjesak)
// ->50 (ukoliko je meta strijelac)
// ->10 (ukoliko je meta konjanik)
//*Umanjiti zdravlje mete za nacinjenu stetu
//*Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (StatusAlive = false)
void Pjesak::Napadaj(Vojnik* meta) {
    if (meta == nullptr) return;
    bool napad = rand() % 2;
    int damage = 0;
    if (napad) {
        if (dynamic_cast<Pjesak*>(meta) != nullptr) { damage = 30; cout << "Pjesak napada pjesaka" << "\n"; }
        if (dynamic_cast<Strijelac*>(meta) != nullptr) { damage = 50; cout << "Strijelac napada pjesaka" << "\n"; }
        if (dynamic_cast<Konjanik*>(meta) != nullptr) { damage = 10; cout << "Konjanik napada pjesaka" << "\n"; }
        meta->Zdravlje = Min(0, Zdravlje - damage);
        if (meta->Zdravlje == 0) meta->StatusZiv = false;
    }
    else
        cout << "Bezuspjesan napad!" << "\n";
}

//Z3.9 ::
//Strijelac ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//*Utvrditi tip mete koristenjem 'dynamic_cast'
//U slucaju da je napad uspjesan, steta koja se nanosi je:
//->35 (ukoliko je meta pjesak)
//->50 (ukoliko je meta drugi strijelac)
//->65 (ukoliko je meta konjanik)
//*Umanjiti zdravlje mete za nacinjenu stetu
//*Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (StatusAlive = false)
void Strijelac::Napadaj(Vojnik* meta) {
    if (meta == nullptr) return;
    bool napad = rand() % 2;
    int damage = 0;
    if (napad) {
        if (dynamic_cast<Pjesak*>(meta) != nullptr) { damage = 35; cout << "Pjesak napada strijelca" << "\n"; }
        if (dynamic_cast<Strijelac*>(meta) != nullptr) { damage = 50; cout << "Strijelac napada strijelca" << "\n"; }
        if (dynamic_cast<Konjanik*>(meta) != nullptr) { damage = 65; cout << "Konjanik napada strijelca" << "\n"; }
        meta->Zdravlje = Min(0, Zdravlje - damage);
        if (meta->Zdravlje == 0) meta->StatusZiv = false;
    }
    else
        cout << "Bezuspjesan napad!" << "\n";
}
//Z4.9 ::
//Konjanik ima vjerovatnocu od 50% da ce uspjesno sprovesti napad
//*Utvrditi tip mete koristenjem 'dynamic_cast'
//U slucaju da je napad uspjesan, steta koja se nanosi je:
//->50 (ukoliko je meta pjesak)
//->80 (ukoliko je meta strijelac)
//->20 (ukoliko je meta konjanik)
//*Umanjiti zdravlje mete za nacinjenu stetu
//*Ukoliko je zdravlje mete palo na 0, proglasiti metu nezivom (StatusAlive = false)
void Konjanik::Napadaj(Vojnik* meta) {
    if (meta == nullptr) return;
    bool napad = rand() % 2;
    int damage = 0;
    if (napad) {
        if (dynamic_cast<Pjesak*>(meta) != nullptr) { damage = 50; cout << "Pjesak napada konjanika" << "\n"; }
        if (dynamic_cast<Strijelac*>(meta) != nullptr) { damage = 80; cout << "Strijelac napada konjanika" << "\n"; }
        if (dynamic_cast<Konjanik*>(meta) != nullptr) { damage = 20; cout << "Konjanik napada konjanika" << "\n"; }
        meta->Zdravlje = Min(0, Zdravlje - damage);
        if (meta->Zdravlje == 0) meta->StatusZiv = false;
    }
    else
        cout << "Bezuspjesan napad!" << "\n";
}

template<class T>
class VojnaJedinica {
protected:
    const char* _naziv;
    vector<T> _pripadnici;
    unique_ptr<float> _cijenaObuke;
    unique_ptr<float> _cijenaOdrzavanja;
    void Dealocate() { delete[]_naziv; _naziv = nullptr; }
public:
    __declspec(property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    __declspec(property (get = GetPripadnici, put = SetPripadnici)) vector<T> Pripadnici;
    __declspec(property (get = GetCijenaObuke, put = SetCijenaObuke)) float CijenaObuke;
    __declspec(property (get = GetCijenaOdrzavanja, put = SetCijenaOdrzavanja)) float CijenaOdrzavanja;
    //Z5.1
    VojnaJedinica(const char* naziv = "", float cijenaObuke = 500, float cijenaOdrzavanja = 110) {
        _naziv = Alokator(naziv);
        _cijenaObuke = make_unique<float>(cijenaObuke);
        _cijenaOdrzavanja = make_unique<float>(cijenaOdrzavanja);

    }
    //Z5.2
    VojnaJedinica(const VojnaJedinica<T>& obj) : _pripadnici(obj._pripadnici) {
        _naziv = Alokator(obj._naziv);
        _cijenaObuke = make_unique<float>(*obj._cijenaObuke);
        _cijenaOdrzavanja = make_unique<float>(*obj._cijenaOdrzavanja);
    }
    //Z5.3
    VojnaJedinica(VojnaJedinica<T>&& obj) :_pripadnici(move(obj._pripadnici)),
        _cijenaObuke(move(obj._cijenaObuke)), _cijenaOdrzavanja(move(obj._cijenaOdrzavanja))
    {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
    }
    //Z5.4 :: Getteri
    const char* GetNaziv() const { return _naziv; }
    vector<T> GetPripadnici() const { return _pripadnici; }
    float GetCijenaObuke() const { return *_cijenaObuke; }
    float GetCijenaOdrzavanja() const { return *_cijenaOdrzavanja; }
    //Z5.5 :: Setteri
    void SetNaziv(const char* naziv) {
        delete[]_naziv;
        _naziv = Alokator(naziv);
    }
    void SetPripadnici(vector<T> pripadnici) {
        _pripadnici = pripadnici;
    }
    void SetCijenaObuke(float cijenaObuke) {
        if (_cijenaObuke == nullptr) _cijenaObuke = make_unique<float>();
        *_cijenaObuke = cijenaObuke;
    }
    void SetCijenaOdrzavanja(float cijenaOdrzavanja) {
        if (_cijenaOdrzavanja == nullptr) _cijenaOdrzavanja = make_unique<float>();
        *_cijenaOdrzavanja = cijenaOdrzavanja;
    }
    //Z5.6
    VojnaJedinica<T>& operator = (const VojnaJedinica<T>& obj) {
        if (this != &obj)
        {
            Dealocate();
            _naziv = Alokator(obj._naziv);
            if (_cijenaObuke == nullptr) _cijenaObuke = make_unique<float>();
            *_cijenaObuke = *obj._cijenaObuke;
            if (_cijenaOdrzavanja == nullptr) _cijenaOdrzavanja = make_unique<float>();
            *_cijenaOdrzavanja = *obj._cijenaOdrzavanja;
        }
        return *this;
    }
    //Z5.7
    template<class T>
    void DodajPripadnika(const T pripadnik) {
        _pripadnici.push_back(pripadnik);
    }
    //Z5.8 :: Ispisati ukupan broj pripadnika umjesto ispisa svakog pojedinacnog pripadnika
    void Ispis() {
        cout << "Naziv: " << Naziv << endl;
        cout << "Vojni red: " << typeid(T).name() << endl;
        cout << "Broj pripadnika: " << Pripadnici.size() << endl;
        cout << "Cijena obuke (recruitment cost): " << CijenaObuke << endl;
        cout << "Cijena odrzavanja (upkeep cost): " << CijenaOdrzavanja << endl;

    }
    //Z5.9
    ~VojnaJedinica() { Dealocate(); }
};
//Z5.11
template<class T>
bool operator == (const VojnaJedinica<T>& obj1, const VojnaJedinica<T>& obj2) {
    return obj1.Pripadnici == obj2.Pripadnici;

}
//Z5.12
template<class T>
bool operator != (const VojnaJedinica<T>& obj1, const VojnaJedinica<T>& obj2);

class Armija {
private:
    const char* _ime;
    vector<VojnaJedinica<Pjesak>> _pjesadija;
    vector<VojnaJedinica<Strijelac>> _strijelci;
    vector<VojnaJedinica<Konjanik>> _konjica;
    void Dealocate() { delete[]_ime; _ime = nullptr; }
public:
    __declspec(property (get = GetIme, put = SetIme)) const char* Ime;
    __declspec(property (get = GetPjesadija, put = SetPjesadija)) vector<VojnaJedinica<Pjesak>> Pjesadija;
    __declspec(property (get = GetStrijelci, put = SetStrijelci)) vector<VojnaJedinica<Strijelac>> Strijelci;
    __declspec(property (get = GetKonjica, put = SetKonjica)) vector<VojnaJedinica<Konjanik>> Konjica;
    //Z6.1
    Armija(const char* ime = "") {
        _ime = Alokator(ime);
    }
    //Z6.2
    Armija(const Armija& obj) : _pjesadija(obj._pjesadija), _strijelci(obj._strijelci), _konjica(obj._konjica)
    {
        _ime = Alokator(obj._ime);
    }
    //Z6.3
    Armija(Armija&& obj) : _pjesadija(move(obj._pjesadija)), _strijelci(move(obj._strijelci)), _konjica(move(obj._konjica))
    {
        _ime = obj._ime;
        obj._ime = nullptr;
    }
    //Z6.4 :: Getteri
    const char* GetIme() const { return _ime; }
    vector<VojnaJedinica<Pjesak>> GetPjesadija() const { return _pjesadija; }
    vector<VojnaJedinica<Strijelac>> GetStrijelci() const { return _strijelci; }
    vector<VojnaJedinica<Konjanik>> GetKonjica() const { return _konjica; }
    //Z6.5 :: Setteri
    void SetIme(const char* ime) {
        delete[]_ime; _ime = Alokator(ime);
    }
    void SetPjesadija(vector<VojnaJedinica<Pjesak>> pjesadija) { _pjesadija = pjesadija; }
    void SetStrijelci(vector<VojnaJedinica<Strijelac>> strijelci) { _strijelci = strijelci; }
    void SetKonjica(vector<VojnaJedinica<Konjanik>> konjica) { _konjica = konjica; }

    //Z6.6
    Armija& operator =(const Armija& obj) {
        if (this != &obj)
        {
            Dealocate();
            _ime = Alokator(obj._ime);
            _pjesadija = obj._pjesadija;
            _strijelci = obj._strijelci;
            _konjica = obj._konjica;

        }
        return *this;
    }
    //Z6.7
    void DodajJedinicu(VojnaJedinica<Pjesak> jedinica) {
        _pjesadija.push_back(jedinica);
    }
    void DodajJedinicu(VojnaJedinica<Strijelac> jedinica) {
        _strijelci.push_back(jedinica);

    }
    void DodajJedinicu(VojnaJedinica<Konjanik> jedinica) {
        _konjica.push_back(jedinica);

    }
    //Z6.8
    void Ispis() {
        cout << "Naziv armije: " << Ime << endl;
        cout << "----------------------------------\n";
        cout << "Pjesadija:" << endl;
        cout << "----------------------------------\n";
        for (size_t i = 0; i < Pjesadija.size(); i++)
            Pjesadija[i].Ispis();
        cout << "----------------------------------\n";
        cout << "Strijelci:" << endl;
        cout << "----------------------------------\n";
        for (size_t i = 0; i < Strijelci.size(); i++)
            Strijelci[i].Ispis();
        cout << "----------------------------------\n";
        cout << "Konjica:" << endl;
        cout << "----------------------------------\n";
        for (size_t i = 0; i < Konjica.size(); i++)
            Konjica[i].Ispis();
        cout << "----------------------------------\n";

    }
    //Z6.9
    ~Armija() { Dealocate(); }
};
//Z6.10
bool operator == (const Armija& a1, const Armija& a2);

auto IspisiPoruku = [](const char* tipFunkcije, bool success) {
    cout << tipFunkcije << " se izvrsio " << ((success) ? "uspjesno!" : "bezuspjesno!") << endl;
};

void Zadatak1() {
    vector<const char*> oruzja{ "mac", "dugi mac", "ratna sjekira", "buzdovan", "helebarda", "koplje" };
    Vojnik univerzalniVojnik;
    univerzalniVojnik.Zdravlje = 85;
    univerzalniVojnik.Izdrzljivost = 75;
    univerzalniVojnik.Moral_ = Moral::Srednji;
    univerzalniVojnik.Oruzja = oruzja;
    univerzalniVojnik.StatusZiv = true;
    univerzalniVojnik.Ispis();
    //
    Vojnik u1(univerzalniVojnik);
    IspisiPoruku("Copy ctor", univerzalniVojnik == u1);
    Vojnik u2(move(u1));
    IspisiPoruku("Move ctor", univerzalniVojnik == u2);
    Vojnik u3;
    u3 = univerzalniVojnik;
    IspisiPoruku("Operator '='", univerzalniVojnik == u3);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak2() {
    vector<const char*> oruzja{ "velika ratna sjekira", "mac s dvije ruke" };
    Pjesak gimly;
    gimly.Oruzja = oruzja;
    gimly.Oklop = "teski celicni oklop";
    gimly.Kategorija_ = Kategorija::Teska;
    gimly.Ispis();

    Pjesak anotherDwarf(gimly);
    IspisiPoruku("Copy ctor", anotherDwarf == gimly);
    Pjesak anotherDwarf2(move(anotherDwarf));
    IspisiPoruku("Move ctor", gimly == anotherDwarf2);
    Pjesak p3;
    p3 = gimly;
    IspisiPoruku("Operator '='", gimly == p3);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak3() {
    vector<const char*> oruzja{ "velski dugacki luk", "samostrijel", "kratki mac" };
    Strijelac legolas;
    legolas.Oruzja = oruzja;
    legolas.Municija = 150;
    legolas.Ispis();
    Strijelac anotherElf(legolas);
    IspisiPoruku("Copy ctor", legolas == anotherElf);
    Strijelac anotherElf2(move(anotherElf));
    IspisiPoruku("Move ctor", legolas == anotherElf2);
    Strijelac s3;
    s3 = legolas;
    IspisiPoruku("Operator '='", legolas == s3);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak4() {
    system("cls;");
    vector<const char*> oruzja{ "dugacko koplje", "buzdovan" };
    Konjanik eomer;
    eomer.Oruzja = oruzja;
    eomer.Oklop = "celicni oklop";
    eomer.VrstaKonja = "frizijski konj";
    eomer.Ispis();
    Konjanik anotherHorserider(eomer);
    IspisiPoruku("Copy ctor", anotherHorserider == eomer);
    Konjanik anotherHorserider2(move(anotherHorserider));
    IspisiPoruku("Move ctor", eomer == anotherHorserider2);
    Konjanik ghostRider;
    ghostRider = eomer;
    IspisiPoruku("Operator '='", eomer == ghostRider);
    srand(time(0));
    Pjesak p1, p2, p3, p4, p5;
    Strijelac s1, s2, s3, s4, s5;
    Konjanik k1, k2, k3, k4, k5;
    cout << "Bitka pocinje: -->" << endl;
    p1.Napadaj(&s1); //Pjesak napada strijelca (50% vjerovatnoca da uspije)
    p2.Napadaj(&p1); //Pjesak napada pjesaka (50% vjerovatnoca da uspije)
    p1.Napadaj(&k1); //Pjesak napada konjanika (50% vjerovatnoca da uspije)
    ////
    s1.Napadaj(&s2); // Strijelac napada strijelca (50% vjerovatnoca da uspije)
    s2.Napadaj(&k5); // Strijelac napada konjanika (50% vjerovatnoca da uspije)
    s4.Napadaj(&p5); // Strijelac napada pjesaka (50% vjerovatnoca da uspije)
    ////
    k4.Napadaj(&p3); // Konjanika napada pjesaka (50% vjerovatnoca da uspije)
    k4.Napadaj(&k3); // Konjanik napada konjanika (50% vjerovatnoca da uspije)
    k4.Napadaj(&s4); // Konjanik napada strijelca (50% vjerovatnoca da uspije)
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak5() {
    VojnaJedinica<Pjesak> svicarskaGarda("Svicarska garda", 560.5f, 120.5f);
    svicarskaGarda.Naziv = "Svicarska Garda";
    svicarskaGarda.CijenaObuke = 570.0f;
    svicarskaGarda.CijenaOdrzavanja = 120.0f;
    for (int i = 0; i < 100; i++)
        svicarskaGarda.DodajPripadnika(Pjesak(Kategorija::Srednja, "lagani oklop"));
    svicarskaGarda.Ispis();
    VojnaJedinica<Pjesak> kopija(svicarskaGarda);
    //spisiPoruku("Copy ctor", svicarskaGarda == kopija);
    VojnaJedinica<Pjesak> pjesadija(move(kopija));
    //IspisiPoruku("Move ctor", svicarskaGarda == pjesadija);
    VojnaJedinica<Pjesak> p3;
    p3 = svicarskaGarda;
    //IspisiPoruku("Operator '='", svicarskaGarda == p3);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak6() {

    VojnaJedinica<Pjesak> svicarskaGarda("Svicarska garda", 550.0f, 130.0f);
    VojnaJedinica<Pjesak> varangijanskaGarda("Varangijanska garda", 670.0f, 160.0f);
    VojnaJedinica<Pjesak> manAtArms("Man At Arms", 520.0f, 110.0f);
    for (int i = 0; i < 250; i++)
        svicarskaGarda.DodajPripadnika(Pjesak(Kategorija::Srednja, "lagani oklop"));
    for (int i = 0; i < 150; i++)
        varangijanskaGarda.DodajPripadnika(Pjesak(Kategorija::Teska, "celicni oklop"));
    for (int i = 0; i < 100; i++)
        manAtArms.DodajPripadnika(Pjesak(Kategorija::Srednja, "lagani oklop"));
    //
    VojnaJedinica<Strijelac> englishLongbowman("Enlish Longbowman", 350.0f, 110.0f);
    for (int i = 0; i < 250; i++)
        englishLongbowman.DodajPripadnika(Strijelac(100));
    //
    VojnaJedinica<Konjanik> bosanskaElitnaKonjica("Bosanska elitna konjica", 950.0f, 250.0f);
    for (int i = 0; i < 80; i++)
        bosanskaElitnaKonjica.DodajPripadnika(Konjanik("celicni oklop", "bosanski brdski konj"));
    VojnaJedinica<Konjanik> katafrakt("Katafrakt", 850.0f, 230.0f);
    for (int i = 0; i < 100; i++)
        katafrakt.DodajPripadnika(Konjanik("teski celicni oklop", "teski bizantijski konj"));
    //
    Armija sjevernaArmija("Army Of The North");
    sjevernaArmija.DodajJedinicu(svicarskaGarda);
    sjevernaArmija.DodajJedinicu(varangijanskaGarda);
    sjevernaArmija.DodajJedinicu(manAtArms);
    sjevernaArmija.DodajJedinicu(englishLongbowman);
    sjevernaArmija.DodajJedinicu(bosanskaElitnaKonjica);
    sjevernaArmija.DodajJedinicu(katafrakt);
    sjevernaArmija.Ispis();
    //
    Armija juznaArmija(sjevernaArmija);
    // IspisiPoruku("Copy ctor", sjevernaArmija == juznaArmija);
    Armija pirane(move(juznaArmija));
    // IspisiPoruku("Move ctor", sjevernaArmija == pirane);
    Armija a3;
    a3 = sjevernaArmija;
    // IspisiPoruku("Operator '='", sjevernaArmija == a3);
     cout << endl << "Dealokacija..." << endl;

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
            cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor < 1 || izbor > 6);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
        case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
        case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
        case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
        case 5: Zadatak5(); cout << "Zadatak 5. Done." << endl; break;
        case 6: Zadatak6(); cout << "Zadatak 6. Done." << endl; break;
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


