#include <vector>
#include <iostream>
#include <cassert>
#include <functional>
using namespace std;

//Z0.1 
char* Alokator(const char* tekst) {
    if (tekst == nullptr)  return nullptr;
    int vel =strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}
//Z0.2
int IzracunajBrojZnamenki(int broj) {
    int v = 0;
    while (broj)
    {
        broj /= 10;
        v++;
    }
    return v;
}
//Z0.3 :: Pretvoriti (int) u (char*).
char* IntToStr(int broj) {
    int vel = IzracunajBrojZnamenki(broj) + 1;
    char* novi = new char[vel];
    _itoa_s(broj, novi, vel, 10);
    return novi;
}

//Z0.4 :: Funkcija za alokaciju pametnog (shared_ptr) pokazivaca na niz karaktera
shared_ptr<char> SharedAlokator(const char* tekst) {
    if (tekst == nullptr)  return nullptr;
    int vel = strlen(tekst) + 1;
    shared_ptr<char>novi;
    novi.reset(new char[vel]);
    return novi;
}
//Z0.5 :: Funkcija za alokaciju pametnog (unique_ptr) pokazivaca na niz karaktera
unique_ptr<char> UniqueAlokator(const char* tekst) {
    if (tekst == nullptr)  return nullptr;
    int vel = strlen(tekst) + 1;
    unique_ptr<char>novi;
    novi.reset(new char[vel]);
    strcpy_s(novi.get(), vel, tekst);
    return novi;
}

//Z0.6:: Provjeriti da li su dva niza karaktera ista (po vrijednosti)
bool CheckIfIsti(const char* tekst1, const char* tekst2) {
    return strcmp(tekst1, tekst2) == 0;
}
//Z0.7 Provjeriti da li su dva vektora jednaka (da li imaju iste elemente)
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
bool operator != (const vector<T>& v1, const vector<T>& v2);
//Z0.8 Provjeriti da li su dva vektora nizova karaktera jednaka (da li imaju iste elemente)
bool CheckIfIsti(const vector<const char*>& v1, const vector<const char*>& v2) {
    return !(v1 == v2);
}

//Po mogucnosti postavljati 'assert' tamo gdje se radi dereferenciranje pokazivaca
//Za postojece objekte mozete koristiti property-je za pristup vrijednostima atributa
//Za ispravno koristenje property-ja, uraditi implementaciju odgovarajucih gettera i settera
class Uredjaj {
private:
    const char* _id;
protected:
    unique_ptr<char> _naziv;
    int _godinaProizvodnje;
    shared_ptr<float> _cijena;
    int* _garancija;
    vector<int> _ocjene;
public:
    __declspec(property (get = GetId, put = SetId)) const char* Id;
    __declspec(property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    __declspec(property (get = GetGodinaProizvodnje, put = SetGodinaProizvodnje)) int GodinaProizvodnje;
    __declspec(property (get = GetCijena, put = SetCijena)) float Cijena;
    __declspec(property (get = GetGarancija, put = SetGarancija)) int Garancija;
    __declspec(property (get = GetOcjene, put = SetOcjene)) vector<int> Ocjene;

    //Z1.0 :: Staticka metoda koja vraca niz karaktera (brojeva) u opsegu "10000" do "99999"
    static const char* GetRandomId() {
        int brojId = rand() % 90000 + 10000;
        return IntToStr(brojId);
    }
    //Z1.1 :: Postaviti '_id' na rezultat koji vrati staticka funkcija 'GetRandomId'
    Uredjaj() {
        _id = GetRandomId();
        _godinaProizvodnje = 2020;
        _garancija = nullptr;
    }
    //Z1.2
    Uredjaj(const char* naziv, int godinaProizvodnje, float cijena, int garancija) {
        _naziv = UniqueAlokator(naziv);
        _godinaProizvodnje = godinaProizvodnje;
        _cijena = make_shared<float>(cijena);
        _garancija = new int(garancija);
    }
    //Z1.3 :: mozete koristiti property-je drugog (vec postojeceg) objekta za pristup vrijednostima njegovih atributa
    //Kopirati sve atribute, ukljucujuci i polje '_id'
    Uredjaj(const Uredjaj& obj) :_ocjene(obj._ocjene)
    {
        _id = Alokator(obj._id);
        _naziv = UniqueAlokator(obj._naziv.get());
        _godinaProizvodnje = obj._godinaProizvodnje;
        _cijena = make_shared<float>(*obj._cijena);
        _garancija = new int(*obj._garancija);

    }
    //Z1.4
    Uredjaj(Uredjaj&& obj) :_naziv(move(obj._naziv)),_cijena(move(obj._cijena)),_ocjene(move(obj._ocjene))
    {
        _id = obj._id;
        obj._id = nullptr;
        _godinaProizvodnje = obj._godinaProizvodnje;
        _garancija = obj._garancija;
        obj._garancija = nullptr;
    }

    //Z1.5
    const char* GetId() const { return _id; }
    const char* GetNaziv() const { return _naziv.get(); }
    int GetGodinaProizvodnje() const { return _godinaProizvodnje; }
    float GetCijena() const { return *_cijena; }
    int GetGarancija() const { return *_garancija; }
    vector<int> GetOcjene() const { return _ocjene; }

    //Z1.6
    void SetId(const char* id) {
        delete[]_id;
        _id = Alokator(id);

    }
    void SetNaziv(const char* naziv) {
        _naziv = UniqueAlokator(naziv);

    }
    void SetGodinaProizvodnje(int godinaProizvodnje) {
        _godinaProizvodnje = godinaProizvodnje;

    }
    void SetCijena(float cijena) {
        if (_cijena == nullptr)_cijena = make_shared<float>();
        *_cijena = cijena;
    }
    void SetGarancija(int garancija) {
        if (_garancija == nullptr) _garancija = new int;
        *_garancija = garancija;
    }
    void SetOcjene(vector<int> ocjene) {
        _ocjene = ocjene;
    }
    //Z1.7 :: mozete koristiti property-je za oba objekta (obzirom da vec postoje)
    Uredjaj& operator =(const Uredjaj& obj) {
        if (this != &obj)
        {
            delete[]_id;
            _id = Alokator(obj._id);
            _naziv = UniqueAlokator(obj._naziv.get());
            _godinaProizvodnje = obj._godinaProizvodnje;
            if (_cijena == nullptr)_cijena = make_shared<float>();
            *_cijena = *obj._cijena;
            if (_garancija == nullptr)_garancija = new int;
            *_garancija = *obj._garancija;
            _ocjene = obj._ocjene;
        }
        return *this;
    }
    //Z1.8
    void AddOcjena(int ocjene) {
        _ocjene.push_back(ocjene);
    }

    //Z1.9 :: Mozete koristiti property-je obzirom da objekt vec postoji
    float GetProsjecnaOcjena(function<float(vector<int>)> tipProsjeka) {
        return tipProsjeka(Ocjene);
    }
    //Z1.10 :: implementacija funkcije 'Ispis' se prepisuje (override-a) sa implementacijom istoimene funkcije  najizvedenije klase
    // Mozete koristiti property-je obzirom da objekt vec postoji
    virtual void Ispis() {
        cout << "Id: " << Id << endl;
        cout << "Naziv: " << Naziv << endl;
        cout << "Godina proizvodnje: " << GodinaProizvodnje << endl;
        cout << "Cijena: " << Cijena << " KM" << endl;
        cout << "Garancija (u god.): " << Garancija << endl;
        cout << "Ocjene: " << endl;
        for (size_t i = 0; i < Ocjene.size(); i++)
            cout << Ocjene[i] << ", ";
    }
    //Z1.11
    virtual ~Uredjaj() {
        if (_id != nullptr) { delete[]_id; _id = nullptr; }
    }
   
};

//Z1.12
//Iskljuciti polje 'Id' iz uporedbe
bool operator == (const Uredjaj& u1, const Uredjaj& u2) {
    return u1.Cijena == u2.Cijena;
}
bool operator != (const Uredjaj& u1, const Uredjaj& u2) {
    return u1.Cijena != u2.Cijena;
}

class Mobitel : public Uredjaj {
private:
    char _operativniSistem[50];
    unique_ptr<float> _velicinaEkrana;//u incima Npr. 6.1
    int* _memorija; //GB
public:
    __declspec(property (get = GetOperativniSistem, put = SetOperativniSistem)) const char* OperativniSistem;
    __declspec(property (get = GetVelicinaEkrana, put = SetVelicinaEkrana)) float VelicinaEkrana;
    __declspec(property (get = GetMemorija, put = SetMemorija)) int Memorija;
    //Z3.1
    Mobitel() {
        strcpy_s(_operativniSistem, 50, "");
        _memorija = nullptr;
    }
    //Z2.2
    Mobitel(const char* naziv, int godinaP, float cijena, int garancija, const char* operativniS, float velicinaE, int memorija)
        : Uredjaj(naziv, godinaP, cijena, garancija)
    {
        strcpy_s(_operativniSistem, 50, operativniS);
        _velicinaEkrana = make_unique<float>(velicinaE);
        _memorija = new int(memorija);
    }
    //Z2.3
    Mobitel(const Mobitel& mobitel)
        : Uredjaj(mobitel)
    {
        strcpy_s(_operativniSistem, 50, mobitel._operativniSistem);
        _velicinaEkrana = make_unique<float>(*mobitel._velicinaEkrana);
        _memorija = new int(*mobitel._memorija);

    }
    //Z2.4
    Mobitel(Mobitel&& obj)
        : Uredjaj(move(obj)),
        _velicinaEkrana(move(obj._velicinaEkrana))
    {
        strcpy_s(_operativniSistem, 50, obj._operativniSistem);
        _memorija = obj._memorija;
        obj._memorija = nullptr;
    }

    const char* GetOperativniSistem()const { return _operativniSistem; }
    float GetVelicinaEkrana()const { return *_velicinaEkrana; }
    int GetMemorija()const { return *_memorija; }

    void SetOperativniSistem(const char* operativniSistem) {
        strcpy_s(_operativniSistem, 50, operativniSistem);

    }
    void SetVelicinaEkrana(float velicinaEkrana) {
        if (_velicinaEkrana == nullptr)_velicinaEkrana = make_unique<float>();
        *_velicinaEkrana = velicinaEkrana;
    }
    void SetMemorija(int memorija) {
        if (_memorija == nullptr)_memorija = new int;
        *_memorija = memorija;
    }
    //Z2.5
    Mobitel& operator = (const Mobitel& obj) {
        if (this!=&obj)
        {
            (Uredjaj&)(*this) = obj;
            strcpy_s(_operativniSistem, 50, obj._operativniSistem);
            if (_velicinaEkrana == nullptr)_velicinaEkrana = make_unique<float>();
            *_velicinaEkrana = *obj._velicinaEkrana;
            if (_memorija == nullptr)_memorija = new int;
            *_memorija = *obj._memorija;
        }
        return *this;
    }
    //Z2.6
    //Ispisati id, naziv mobitela, velicinu ekrana, operativni sistem, kolicinu memorije, cijenu te broj godina garancije
    void Ispis() {
        cout << "Id: " << Id << endl;
        cout << "Naziv mobitela: " << Naziv << endl;
        cout << "Velicina ekrana: " << VelicinaEkrana << "\"" << endl;
        cout << "OS: " << OperativniSistem << endl;
        cout << "Memorija: " << Memorija << " GB" << endl;
        cout << "Cijena: " << Cijena << " KM" << endl;
        cout << "Garancija (god): " << Garancija << endl;

    }
    //Z2.7
    ~Mobitel() {
        delete _memorija; _memorija = nullptr;
    }
};
//Z2.8
bool operator == (const Mobitel& m1, const Mobitel& m2) {
    return m1.Garancija == m2.Garancija;

}
bool operator != (const Mobitel& m1, const Mobitel& m2);

class Televizor : public Uredjaj {
    unique_ptr<float> _velicinaEkrana;
    unique_ptr<char> _tipEkrana;
    pair<int, int> _rezolucija;
    vector<const char*> _prikljucci;
public:
    __declspec(property (get = GetVelicinaEkrana, put = SetVelicinaEkrana)) float VelicinaEkrana;
    __declspec(property (get = GetTipEkrana, put = SetTipEkrana)) const char* TipEkrana;
    __declspec(property (get = GetRezolucija, put = SetRezolucija)) pair<int, int> Rezolucija;
    __declspec(property (get = GetPrikljucci, put = SetPrikljucci)) vector<const char*> Prikljucci;

    //Z3.1
    Televizor(){}
    //Z3.2
    Televizor(const char* naziv, int godinaP, float cijena, int garancija,
        float velicinaEkrana, const char* tipEkrana, pair<int, int> rezolucija)
        : Uredjaj(naziv, godinaP, cijena, garancija),
        _rezolucija(rezolucija)

    {
        _velicinaEkrana = make_unique<float>(velicinaEkrana);
        _tipEkrana = UniqueAlokator(tipEkrana);
    }
    //Z3.3
    Televizor(const Televizor& obj)
        :Uredjaj(obj),
        _rezolucija(obj._rezolucija)
    {
        _velicinaEkrana = make_unique<float>(*obj._velicinaEkrana);
        _tipEkrana = UniqueAlokator(obj._tipEkrana.get());
        _prikljucci = obj._prikljucci;
    }
    //Z3.4
    Televizor(Televizor&& obj)
        : _velicinaEkrana(move(obj._velicinaEkrana)),
        _tipEkrana(move(obj._tipEkrana))
        , _rezolucija(move(obj._rezolucija)),
        _prikljucci(move(obj._prikljucci))
    {

    }

    float GetVelicinaEkrana()const { return *_velicinaEkrana; }
    const char* GetTipEkrana()const { return _tipEkrana.get(); }
    pair<int, int> GetRezolucija()const { return _rezolucija; }
    vector<const char*> GetPrikljucci()const { return _prikljucci; }

    void SetVelicinaEkrana(float velicinaEkrana) {
        if (_velicinaEkrana == nullptr)_velicinaEkrana = make_unique<float>();
        *_velicinaEkrana = velicinaEkrana;
    }
    void SetTipEkrana(const char* tipEkrana) {
        _tipEkrana = UniqueAlokator(tipEkrana);
    }
    void SetRezolucija(pair<int, int> rezolucija) {
        _rezolucija = rezolucija;
    }
    void SetPrikljucci(vector<const char*>prikljucci) {
        _prikljucci = prikljucci;
    }

    //Z3.5
    Televizor& operator = (const Televizor& obj) {
        if (this != &obj)
        {
            (Uredjaj&)(*this) = obj;
            if (_velicinaEkrana == nullptr)_velicinaEkrana = make_unique<float>();
            *_velicinaEkrana = *obj._velicinaEkrana;
            _tipEkrana = UniqueAlokator(obj._tipEkrana.get());
            _rezolucija = obj._rezolucija;
            _prikljucci = obj._prikljucci;
        }
        return *this;
    }
    void operator+=(const char* prikljucak) {
        _prikljucci.push_back(prikljucak);
    }

    //Z3.6
    //Ispisati id, naziv TV-a, velicinu ekrana, tip ekrana, rezoluciju, cijenu, broj godina garancije, te sve prikljucke
    void Ispis() {
        cout << "Id: " << Id << endl;
        cout << "Naziv TV-a: " << Naziv << endl;
        cout << "Velicina ekrana: " << VelicinaEkrana << "\"" << endl;
        cout << "Tip ekrana: " << TipEkrana << endl;
        cout << "Rezolucija: " << Rezolucija.first << "x" << Rezolucija.second << endl;
        cout << "Cijena: " << Cijena << " KM" << endl;
        cout << "Garancija: " << Garancija << endl;
        cout << "Prikljucci: " << endl;
        for (size_t i = 0; i < Prikljucci.size(); i++)
            cout << Prikljucci[i] << ", ";

    }
    //Z3.7
    ~Televizor(){}
};

bool operator == (const Televizor& t1, const Televizor& t2) {
    return t1.VelicinaEkrana == t2.VelicinaEkrana;
}
bool operator != (const Televizor& t1, const Televizor& t2);

class Printer : public Uredjaj {
    int* _brzinaPrintanja; // br. str. po minuti
public:
    __declspec(property (get = GetBrzinaPrintanja, put = SetBrzinaPrintanja)) int BrzinaPrintanja;
    //Z4.1
    Printer():_brzinaPrintanja(nullptr){}
    //Z4.2
    Printer(const char* naziv, int godinaP, float cijena, int garancija, int brzinaPrintanja): Uredjaj(naziv,godinaP,cijena,garancija)
    { 
        _brzinaPrintanja = new int(brzinaPrintanja);
    }
    //Z4.3
    Printer(const Printer& obj) : Uredjaj(obj)
    {
        _brzinaPrintanja = new int(*obj._brzinaPrintanja);
    }
    //Z4.4
    Printer(Printer&& obj) :Uredjaj(move(obj)) {
        _brzinaPrintanja = obj._brzinaPrintanja;
        obj._brzinaPrintanja = nullptr;
    }
    int GetBrzinaPrintanja() const { return *_brzinaPrintanja; }
    void SetBrzinaPrintanja(int brzinaPrintanja) {
        if (_brzinaPrintanja == nullptr) _brzinaPrintanja = new int;
        *_brzinaPrintanja = brzinaPrintanja;
    }
    //Z4.5
    Printer& operator= (const Printer& obj) {
        if (this != & obj)
        {
            (Uredjaj&)(*this) = obj;
            if (_brzinaPrintanja == nullptr) _brzinaPrintanja = new int;
            *_brzinaPrintanja = *obj._brzinaPrintanja;
        }
        return *this;
    }
    //Z4.6
    //Ispisati id, naziv, brzinu printanja, cijenu te broj godina garancije
    void Ispis() {
        cout << "Id: " << Id << endl;
        cout << "Naziv printera: " << Naziv << endl;
        cout << "Brzina printanja: " << BrzinaPrintanja << " str/min." << endl;
        cout << "Cijena: " << Cijena << " KM" << endl;
        cout << "Garancija (god): " << Garancija << endl;
    }
    //Z4.7
    ~Printer() { delete  _brzinaPrintanja; _brzinaPrintanja = nullptr; }
};
//Z4.8
bool operator == (const Printer& p1, const Printer& p2) { return p1.BrzinaPrintanja == p2.BrzinaPrintanja; }
bool operator != (const Printer& p1, const Printer& p2);

class WebShop {
    char* _naziv;
    char _emailAdresa[100];
    int _trenutnoUredjaja;
    Uredjaj* _uredjaji[100] = { nullptr };
    void Dealocate() {
        if (_naziv != nullptr) { delete[]_naziv; _naziv = nullptr; }
        for (size_t i = 0; i < _trenutnoUredjaja; i++)
        {
            delete _uredjaji[i];
            _uredjaji[i] = nullptr;
        }
    }
public:
    __declspec(property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    __declspec(property (get = GetEmailAdresa, put = SetEmailAdresa)) const char* EmailAdresa;
    __declspec(property (get = GetTrenutnoUredjaja)) int TrenutnoUredjaja;

    //Z5.1
    WebShop() {
        _naziv = nullptr;
        strcpy_s(_emailAdresa, 100, "");
        _trenutnoUredjaja = 0;
    }
    //Z5.2
    WebShop(const char* naziv, const char* emailAdresa) {
        _naziv = Alokator(naziv);
        strcpy_s(_emailAdresa, 100, emailAdresa);
        _trenutnoUredjaja = 0;

    }
    //Z5.3
    WebShop(const WebShop& obj) {
        _naziv = Alokator(obj._naziv);
        strcpy_s(_emailAdresa, 100, obj._emailAdresa);
        _trenutnoUredjaja = obj._trenutnoUredjaja;
        for (size_t i = 0; i < _trenutnoUredjaja; i++)
        {
            auto mob = dynamic_cast<Mobitel*>(obj._uredjaji[i]);
            if (mob != nullptr)
            {
                _uredjaji[i] = new Mobitel(*mob);
                continue;
            }
            auto teve = dynamic_cast<Televizor*>(obj._uredjaji[i]);
            if (teve != nullptr)
            {
                _uredjaji[i] = new Televizor(*teve);
                continue;
            }
            auto printer = dynamic_cast<Printer*>(obj._uredjaji[i]);
            if (printer != nullptr)
            {
                _uredjaji[i] = new Printer(*printer);
                continue;
            }
            auto device = dynamic_cast<Uredjaj*>(obj._uredjaji[i]);
            if (device != nullptr)
            {
                _uredjaji[i] = new Uredjaj(*device);
                continue;
            }
        }
    }
    //Z5.4
    WebShop(WebShop&& obj) {
        _naziv = obj._naziv;
        obj._naziv = nullptr;
        _trenutnoUredjaja = obj._trenutnoUredjaja;
        for (size_t i = 0; i < _trenutnoUredjaja; i++)
        {
            _uredjaji[i] = obj._uredjaji[i];
            obj._uredjaji[i] = nullptr;
        }
        obj._trenutnoUredjaja = 0;
    }

    const char* GetNaziv() const { return _naziv; }


    const char* GetEmailAdresa() const { return _emailAdresa; }
    int GetTrenutnoUredjaja() const { return _trenutnoUredjaja; }
    Uredjaj* GetElementAt(int index) const { return _uredjaji[index]; }

    void SetNaziv(const char* naziv) {
        delete[]_naziv;
        _naziv = Alokator(naziv);
    }
    void SetEmailAdresa(const char* emailAdresa) {
        strcpy_s(_emailAdresa, 100, emailAdresa);
    }
    //Z5.5
    WebShop& operator = (const WebShop& obj) {
        if (this != &obj)
        {
            Dealocate();
            _naziv = Alokator(obj._naziv);
            strcpy_s(_emailAdresa, 100, obj._emailAdresa);
            _trenutnoUredjaja = obj._trenutnoUredjaja;
            for (size_t i = 0; i < _trenutnoUredjaja; i++)
            {
                auto printer = dynamic_cast<Printer*>(obj._uredjaji[i]);
                if (printer != nullptr)
                {
                    _uredjaji[i] = new Printer(*printer);
                    continue;
                }
                auto teve = dynamic_cast<Televizor*>(obj._uredjaji[i]);
                if (teve != nullptr)
                {
                    _uredjaji[i] = new Televizor(*teve);
                    continue;
                }
                auto mob = dynamic_cast<Mobitel*>(obj._uredjaji[i]);
                if (mob != nullptr)
                {
                    _uredjaji[i] = new Mobitel(*mob);
                    continue;
                }
                auto device = dynamic_cast<Uredjaj*>(obj._uredjaji[i]);
                if (device != nullptr)
                {
                    _uredjaji[i] = new Uredjaj(*device);
                    continue;
                }
            }
        }
        return *this;
    }
    //Z5.6 :: Dodavanje novog elementa u niz pokazivaca
    template <class T>
    bool DodajUredjaj(T uredjaj)
    {
        if (_trenutnoUredjaja == 100) return false;
        _uredjaji[_trenutnoUredjaja] = new T(uredjaj);
        _trenutnoUredjaja++;
        return true;
    }
    //Z5.7
    ~WebShop() { Dealocate(); }
    friend ostream& operator << (ostream& COUT, const WebShop& webShop);

    
};
//Z5.8
ostream& operator << (ostream& COUT, const WebShop& obj) {
    cout << "Naziv webshopa: " << obj.Naziv << endl;
    cout << "Email: " << obj.EmailAdresa << endl;
    for (int i = 0; i < obj.TrenutnoUredjaja; i++) {
        cout << "---------------------------------------------\n";
        obj.GetElementAt(i)->Ispis(); // poziv virtuelne funkcije 'Ispis' [bit ce pozvana funkcija 'Ispis' najizvedenije klase]
    }
    cout << "---------------------------------------------\n";
    return COUT;

}
//Z5.9
bool operator == (const WebShop& shop1, const WebShop& shop2) {
    return shop1.TrenutnoUredjaja == shop2.TrenutnoUredjaja;
}
auto IspisiPoruku = [](const char* tipFunkcije, bool success) {
    cout << tipFunkcije << " se izvrsio " << ((success) ? "uspjesno!" : "bezuspjesno!") << endl;
};
void Zadatak1() {
    //Generator ocjena
    const int max = 20;
    vector<int> ocjene;
    for (int i = 0; i < max; i++)
        ocjene.push_back(rand() % 5 + 1);
    ////Testiranje klase 'Uredjaj'
    Uredjaj monitor;
    monitor.Naziv = "LED monitor";
    monitor.GodinaProizvodnje = 2017;
    monitor.Cijena = 250;
    monitor.Garancija = 2;
    monitor.Ocjene = ocjene;
    monitor.Ispis();
    cout << endl;
    Uredjaj monitor2("LED monitor", 2017, 250, 2);
    monitor2.Ocjene = monitor.Ocjene;
    IspisiPoruku("User-def. ctor", monitor == monitor2);
    Uredjaj monitor3(monitor);
    IspisiPoruku("Copy ctor", monitor == monitor3);
    Uredjaj monitor4(move(monitor2));
    IspisiPoruku("Move ctor", monitor == monitor4);
    Uredjaj monitor5;
    monitor5 = monitor;
    IspisiPoruku("Operator '='", monitor == monitor5);
    auto aritmetickaSredina = [](vector<int> brojevi) {
        float suma = 0.0f;
        if (brojevi.size() == 0)
            return suma;
        for (size_t i = 0; i < brojevi.size(); i++)
            suma += brojevi[i];
        return suma / brojevi.size();
    };
    cout << "Prosjecna ocjena: " << monitor.GetProsjecnaOcjena(aritmetickaSredina) << endl;
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak2() {
    Mobitel ironPhone;
    ironPhone.Naziv = "Iron Phone S Ultra";
    ironPhone.GodinaProizvodnje = 2021;
    ironPhone.Cijena = 1200;
    ironPhone.Garancija = 2;
    ironPhone.OperativniSistem = "Onyx";
    ironPhone.VelicinaEkrana = 6.1f;
    ironPhone.Memorija = 16;
    ironPhone.Ispis();
    cout << endl;
    Mobitel ironPhone2("Iron Phone S Ultra", 2021, 1200, 2, "Onyx", 6.1f, 16);
    IspisiPoruku("User-def. ctor", ironPhone == ironPhone2);
    Mobitel ironPhone3(ironPhone);
    IspisiPoruku("Copy ctor", ironPhone == ironPhone3);
    Mobitel ironPhone4(move(ironPhone2));
    IspisiPoruku("Move ctor", ironPhone == ironPhone4);
    Mobitel ironPhone5;
    ironPhone5 = ironPhone;
    IspisiPoruku("Operator '='", ironPhone == ironPhone5);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak3() {
    vector<const char*> prikljucci;
    prikljucci.push_back("USB-C");
    prikljucci.push_back("HDMI");
    prikljucci.push_back("S-Video");
    Televizor chromethius;
    chromethius.Naziv = "Chromethius";
    chromethius.GodinaProizvodnje = 2020;
    chromethius.Cijena = 700;
    chromethius.Garancija = 2;
    chromethius.VelicinaEkrana = 43.5;
    chromethius.TipEkrana = "LED";
    chromethius.Rezolucija = pair<int, int>(3840, 2160);
    chromethius.Prikljucci = prikljucci;
    chromethius.Ispis();
    cout << endl;
    Televizor chromethius2("Chromethius", 2020, 700, 2, 43.5, "LED", pair<int, int>(3840, 2160));
    chromethius2.Prikljucci = chromethius.Prikljucci;
    IspisiPoruku("User-def. ctor", chromethius == chromethius2);
    Televizor chromethius3(chromethius);
    IspisiPoruku("Copy ctor", chromethius == chromethius3);
    Televizor chromethius4(move(chromethius2));
    IspisiPoruku("Move ctor", chromethius == chromethius4);
    Televizor chromethius5;
    chromethius5 = chromethius;
    IspisiPoruku("Operator '='", chromethius == chromethius5);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak4() {
    Printer optomec;
    optomec.Naziv = "Optomec X-40";
    optomec.GodinaProizvodnje = 2021;
    optomec.Cijena = 550;
    optomec.Garancija = 2;
    optomec.BrzinaPrintanja = 30;
    optomec.Ispis();
    //Testiranje user-def. ctora
    Printer optomec2("Optomec X-40", 2021, 550, 2, 30);
    IspisiPoruku("User-def. ctor", optomec == optomec2);
    //Testiranje copy ctora
    Printer optomec3(optomec);
    IspisiPoruku("Copy ctor", optomec == optomec3);
    //Testiranje move ctora
    Printer optomec4(move(optomec2));
    IspisiPoruku("Move ctor", optomec == optomec4);
    //Testiranje operatora '='
    Printer optomec5;
    optomec5 = optomec;
    IspisiPoruku("Operator '='", optomec == optomec5);
    cout << endl << "Dealokacija..." << endl;
}   
void Zadatak5() {
   ////WebShop
   WebShop bosnianVortex;
   bosnianVortex.Naziv = "Bosnian Vortex";
   bosnianVortex.EmailAdresa = "bosnian.vortex@gmail.com";
   ////Uredjaji
   Uredjaj napojna("Corsair Napojna jedinica", 2018, 159.0, 2);
   Mobitel wikkoJerry("WIKO JERRY 3 ANTHRACITE", 2019, 149.0, 2, "Android 8.1", 5.45f, 16);
   Televizor phillipsTV("PHILIPS LED TV AMBILIGHT", 2019, 899.0, 3, 43.0, "LED", pair<int, int>(3840, 2160));
   Printer officeJet("B-HP OFFICEJET 202", 2019, 549.0, 2, 20);
   ////Dodavanje razlicitih tipova uredjaja
   bosnianVortex.DodajUredjaj<Uredjaj>(napojna); //Mozete izostaviti naziv generickog tipa tj: bosnianVortex.DodajUredjaj(napojna);
   bosnianVortex.DodajUredjaj<Mobitel>(wikkoJerry);
   bosnianVortex.DodajUredjaj<Televizor>(phillipsTV);
   bosnianVortex.DodajUredjaj<Printer>(officeJet);
   ////Testiranje user-def. ctora
   WebShop bosnianVortex2("Bosnian Vortex", "bosnian.vortex@gmail.com");
   bosnianVortex2.DodajUredjaj(napojna);
   bosnianVortex2.DodajUredjaj(wikkoJerry);
   bosnianVortex2.DodajUredjaj(phillipsTV);
   bosnianVortex2.DodajUredjaj(officeJet);
   //cout << bosnianVortex << endl;
   IspisiPoruku("User-def. ctor", bosnianVortex2 == bosnianVortex);
   ////Testiranje copy ctora
   WebShop bosnianVortex3(bosnianVortex);
   IspisiPoruku("Copy ctor", bosnianVortex3 == bosnianVortex);
   ////Testiranje move ctora
   WebShop bosnianVortex4(move(bosnianVortex2));
   IspisiPoruku("Move ctor", bosnianVortex4 == bosnianVortex);
   ////Testiranje operatora '='
   WebShop bosnianVortex5;
   bosnianVortex5 = bosnianVortex;
   IspisiPoruku("Operator '='", bosnianVortex5 == bosnianVortex);
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


