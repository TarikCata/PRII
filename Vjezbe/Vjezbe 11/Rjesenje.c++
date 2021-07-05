#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <exception>
#include <regex>
using namespace std;
//::::::::::::::::::::PRIPREMA ZA ISPIT:::::::::::::::::::::::::::::::::::::::::://
const char* linija = "\n---------------------------------------------\n";
//Z0.1
char* Alokator(const char* str) {
    if (str == nullptr) return nullptr;
    int vel = strlen(str) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, str);
    return novi;
}
//Z0.2
bool CheckIfIsti(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) return false;
    return strcmp(str1, str2) == 0;
}
//Z0.3
unique_ptr<char> UniqueAlokator(const char* str) {
    if (str == nullptr) return nullptr;
    int vel = strlen(str) + 1;
    unique_ptr<char>novi(new char[vel]);
    strcpy_s(novi.get(), vel, str);
    return novi;
}
//Z0.4
const char* GetErrorMessage(int linija, const char* funkcija) {
    stringstream poruka;
    poruka << "Linija -> " << linija << endl;
    poruka << "Funkcija -> " << funkcija << endl;
    return poruka.str().c_str();
}
//Z0.5
template<class T>
bool operator == <> (const vector<T>& v1, const vector<T>& v2) {
    if (v1.size() != v2.size())
        return false;
    for (size_t i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return false;
    return true;

}
//Z0.6
template<class T>
bool operator != <> (const vector<T>& v1, const vector<T>& v2) {
    return !(v1 == v2);
}

class FizikalnaVelicina abstract {
protected:
    unique_ptr<float> _vrijednost;
public:
    _declspec (property (get = GetVrijednost, put = SetVrijednost)) float Vrijednost;
    //Z0.7
    FizikalnaVelicina(float vrijednost = 0.0) {
        _vrijednost = make_unique<float>(vrijednost);
    }
    //Z0.8
    FizikalnaVelicina(const FizikalnaVelicina& obj) {
        _vrijednost = make_unique<float>(*obj._vrijednost);
    }
    //Z0.9
    FizikalnaVelicina(FizikalnaVelicina&& obj) noexcept : _vrijednost(move(obj._vrijednost)){}
    //Z0.10
    float GetVrijednost() const { return *_vrijednost; }
    //Z0.11
    void SetVrijednost(float vrijednost) {
        if (_vrijednost == nullptr) _vrijednost = make_unique<float>();
        *_vrijednost = vrijednost;
    }
    //Z0.12
    FizikalnaVelicina& operator = (const FizikalnaVelicina& obj) {
        if (this != &obj)
        {
            if (_vrijednost == nullptr) _vrijednost = make_unique<float>();
            *_vrijednost =*obj._vrijednost;
        }
        return *this;
    }
    //Z0.13
    virtual ~FizikalnaVelicina(){}
};

enum class JedinicaUdaljenosti { m, km, er, sr, ls, au, ly };
//Z0.14
ostream& operator << (ostream& COUT, const JedinicaUdaljenosti& obj) {
    switch (obj) {
    case JedinicaUdaljenosti::m:  COUT << "m"; break;
    case JedinicaUdaljenosti::km: COUT << "km"; break;
    case JedinicaUdaljenosti::er: COUT << "er"; break; // earth radius
    case JedinicaUdaljenosti::sr: COUT << "sr"; break; // solar radius
    case JedinicaUdaljenosti::ls: COUT << "ls"; break; // ligth second
    case JedinicaUdaljenosti::au: COUT << "au"; break; // astronomical unit
    case JedinicaUdaljenosti::ly: COUT << "ly"; break; // ligth year
    default: break;
    }
    return COUT;

}

class Udaljenost : public FizikalnaVelicina
{
protected:
    unique_ptr<JedinicaUdaljenosti> _jedinica;
public:
    _declspec (property (get = GetJedinica, put = SetJedinica)) JedinicaUdaljenosti Jedinica;
    //Z1.0
    Udaljenost(){}
    //Z1.1
    Udaljenost(float vrijednost, JedinicaUdaljenosti jed) : FizikalnaVelicina(vrijednost)
    {
        _jedinica = make_unique<JedinicaUdaljenosti>(jed);
    }
    //Z1.2
    Udaljenost(const Udaljenost& obj) : FizikalnaVelicina(obj)
    {
        _jedinica = make_unique<JedinicaUdaljenosti>(*obj._jedinica);

    }
    //Z1.3
    Udaljenost(Udaljenost&& obj) noexcept : FizikalnaVelicina(move(obj)),_jedinica(move(obj._jedinica))
    {

    }
    //Z1.4
    JedinicaUdaljenosti GetJedinica() const { return *_jedinica; }
    //Z1.5
    void SetJedinica(JedinicaUdaljenosti jedinica)
    {
        if (_jedinica == nullptr) _jedinica = make_unique<JedinicaUdaljenosti>();
        *_jedinica = jedinica;
    }
    //Z1.6
    Udaljenost& operator = (const Udaljenost& obj) {
        if (this!= & obj)
        {
            (FizikalnaVelicina&)(*this) = obj;
            if (_jedinica == nullptr) _jedinica = make_unique<JedinicaUdaljenosti>();
            *_jedinica = *obj._jedinica;
        }
        return *this;
    }
    //Z1.7
    ~Udaljenost(){}
};
//Z1.8
//Z1.8
ostream& operator <<(ostream& COUT, const Udaljenost& obj) {
    COUT << obj.Vrijednost << " " << obj.Jedinica;
    return COUT;
}
//Z1.9
bool operator == (const Udaljenost& u1, const Udaljenost& u2) {
    return u1.Vrijednost == u2.Vrijednost && u1.Jedinica == u2.Jedinica;
}
//Z1.10
bool operator != (const Udaljenost& u1, const Udaljenost& u2) {
    return !(u1 == u2);
}


enum class JedinicaMase { kg, EM, SM }; // EM- Earth Mass, SM - Solar Mass
//Z1.11
ostream& operator << (ostream& COUT, const JedinicaMase& obj) {
    switch (obj) {
    case JedinicaMase::kg: COUT << "kg"; break;
    case JedinicaMase::EM: COUT << "EM"; break;
    case JedinicaMase::SM: COUT << "SM"; break;
    default: break;
    }
    return COUT;
}

class Masa : public FizikalnaVelicina
{
protected:
    unique_ptr<JedinicaMase> _jedinica;
public:
    _declspec (property (get = GetJedinica, put = SetJedinica)) JedinicaMase Jedinica;
    //Z1.12
    Masa(){}
    //Z1.13
    Masa(float vrijednost, JedinicaMase jed) : FizikalnaVelicina(vrijednost)
    {
        _jedinica = make_unique<JedinicaMase>(jed);
    }
    //Z1.14
    Masa(const Masa& obj) : FizikalnaVelicina(obj)
    {
        _jedinica = make_unique<JedinicaMase>(*obj._jedinica);

    }
    //Z1.15
    Masa(Masa&& obj) noexcept : FizikalnaVelicina(move(obj)),_jedinica(move(obj._jedinica))
    {

    }
    JedinicaMase GetJedinica() const { return *_jedinica; }
    //Z1.17
    void SetJedinica(JedinicaMase jedinica) {
        if (_jedinica == nullptr) _jedinica = make_unique<JedinicaMase>();
        *_jedinica = jedinica;
    }

    //Z1.18
    Masa& operator = (const Masa& obj) {
        if (this!= & obj)
        {
            (FizikalnaVelicina&)(*this) = obj;
            if (_jedinica == nullptr) _jedinica = make_unique<JedinicaMase>();
            *_jedinica = *obj._jedinica;
        }
        return *this;
    }
    //Z1.19
    ~Masa(){}
};
//Z1.20
ostream& operator <<(ostream& COUT, const Masa& obj) {
    COUT << obj.Vrijednost << " " << obj.Jedinica;
    return COUT;
}
//Z1.21
bool operator == (const Masa& m1, const Masa& m2) {
    return m1.Vrijednost == m2.Vrijednost && m1.Jedinica == m2.Jedinica;
}
//Z1.22
bool operator != (const Masa& m1, const Masa& m2) {
    return !(m1 == m2);
}

//planete, zvijezde, meteori, komete, nebulae, crne rupe, ...



class NebeskoTijelo {
protected:
    string _naziv;
    unique_ptr<Udaljenost> _poluprecnik;
    unique_ptr<Masa> _masa;
    string* _sastav;
public:
    _declspec (property (get = GetNaziv, put = SetNaziv)) string Naziv;
    _declspec (property (get = GetPoluprecnik, put = SetPoluprecnik)) Udaljenost Poluprecnik;
    _declspec (property (get = GetMasa, put = SetMasa)) Masa Masa_;
    _declspec (property (get = GetSastav, put = SetSastav)) string Sastav;
    //Z2.1
    NebeskoTijelo(const char* naziv = "") : _naziv(naziv) {
        _sastav = nullptr;
    }
    //Z2.2
    NebeskoTijelo(const char* naziv, Udaljenost poluprecnik, Masa masa, const char* sastav)
    {
        _naziv = naziv;
        _poluprecnik = make_unique<Udaljenost>(poluprecnik);
        _masa = make_unique<Masa>(masa);
        _sastav = new string(sastav);
    }
    //Z2.3
    NebeskoTijelo(const NebeskoTijelo& obj)
    {
        _naziv = obj._naziv;
        _poluprecnik = make_unique<Udaljenost>(*obj._poluprecnik);
        _masa = make_unique<Masa>(*obj._masa);
        _sastav = new string(*obj._sastav);
    }
    //Z2.4
    NebeskoTijelo(NebeskoTijelo&& obj) noexcept : _naziv(move(obj._naziv)),_poluprecnik(move(obj._poluprecnik)),_masa(move(obj._masa))
    {
        _sastav = obj._sastav;
        obj._sastav = nullptr;
    }
    //Z2.5
    string GetNaziv() const { return _naziv; }
    Udaljenost GetPoluprecnik() const {
        if (_poluprecnik == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_poluprecnik;
    }
    Masa GetMasa() const {
        if (_poluprecnik == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_masa;
    }
    string GetSastav() const {
        if (_poluprecnik == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_sastav; 
    }
    //Z2.6
    void SetNaziv(string naziv) { _naziv = naziv; }
    void SetPoluprecnik(Udaljenost poluprecnik)
    {
        if (_poluprecnik == nullptr) _poluprecnik = make_unique<Udaljenost>();
        *_poluprecnik = poluprecnik;
    }
    void SetMasa(Masa masa) {
        if (_masa == nullptr) _masa = make_unique<Masa>();
        *_masa = masa;
    }
    void SetSastav(string sastav) {
        if (_sastav == nullptr) _sastav = new string;
        *_sastav = sastav;
    }
    //Z2.7
    NebeskoTijelo& operator = (const NebeskoTijelo& obj) {
        if (this!= &obj)
        {
            _naziv = obj._naziv;
            if (_poluprecnik == nullptr) _poluprecnik = make_unique<Udaljenost>();
            *_poluprecnik = *obj._poluprecnik;
            if (_masa == nullptr) _masa = make_unique<Masa>();
            *_masa = *obj._masa;
            if (_sastav == nullptr) _sastav = new string;
            *_sastav = *obj._sastav;
        }
        return *this;
    }
    //Z2.8
    virtual void Ispis() {
        cout << "Naziv: " << Naziv << endl;
        cout << "Poluprecnik: " << Poluprecnik << endl;
        cout << "Masa: " << Masa_ << endl;
        cout << "Sastav: " << Sastav << endl;

    }
    //Z2.9
    virtual ~NebeskoTijelo() { delete _sastav; _sastav = nullptr; }
};
//Z2.10
bool operator == (const NebeskoTijelo& n1, const NebeskoTijelo& n2) {
    return n1.Naziv == n2.Naziv
        && n1.Poluprecnik == n2.Poluprecnik
        && n1.Masa_ == n2.Masa_
        && n1.Sastav == n2.Sastav;
}
//Z2.11
bool operator != (const NebeskoTijelo& n1, const NebeskoTijelo& n2) {
    return !(n1 == n2);
}


class Planeta : public NebeskoTijelo {
protected:
    Udaljenost _udaljenostOdSunca; // u AJ (astronomska jedinica) // Npr. 1.5 AJ
    vector<string>* _sateliti;
public:
    _declspec (property (get = GetUdaljenostOdSunca, put = SetUdaljenostOdSunca)) Udaljenost UdaljenostOdSunca;
    _declspec (property (get = GetSateliti, put = SetSateliti)) vector<string> Sateliti;
    //Z3.1
    Planeta(){}
    //Z3.2
    Planeta(const char* naziv, Udaljenost radijus, Masa masa, const char* sastav, Udaljenost doSunca, vector<string> sateliti) : NebeskoTijelo(naziv,radijus,masa,sastav)
    {
        _udaljenostOdSunca = doSunca;
        _sateliti = new vector<string>(sateliti);
    }
    //Z3.3
    Planeta(const Planeta& obj) : NebeskoTijelo(obj)
    {
        _udaljenostOdSunca = obj._udaljenostOdSunca;
        _sateliti = new vector<string>(*obj._sateliti);
    }
    //Z3.4
    Planeta(Planeta&& obj)noexcept:NebeskoTijelo(move(obj))
        ,_udaljenostOdSunca(move(obj._udaljenostOdSunca))
    {
        _sateliti = obj._sateliti;
        obj._sateliti = nullptr;
    }

    //Z3.5
    Udaljenost GetUdaljenostOdSunca() const { return _udaljenostOdSunca; }
    vector<string> GetSateliti() const
    {
        if (_sateliti == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_sateliti;
    }
    //Z3.6
    void SetUdaljenostOdSunca(Udaljenost udaljenost) { _udaljenostOdSunca = udaljenost; }
    void SetSateliti(vector<string> sateliti)
    {
        if (_sateliti == nullptr)
            _sateliti = new vector<string>();
        *_sateliti = sateliti;

    }
    //Z3.7
    Planeta& operator =(const Planeta& obj)
    {
        if (this!=&obj)
        {
            _udaljenostOdSunca = obj._udaljenostOdSunca;
            if (_sateliti == nullptr)
                _sateliti = new vector<string>();
            *_sateliti = *obj._sateliti;
        }
        return *this;
    }
    //Z3.8
    //Dodavanje novog satelita (mjeseca)
    void operator +=(string satelit)
    {
        if (_sateliti == nullptr)
            _sateliti = new vector<string>();
        _sateliti->push_back(satelit);
    }
    //Z3.9
    void Ispis()
    {
        NebeskoTijelo::Ispis();
        cout << "Udaljenost od sunca: " << UdaljenostOdSunca << endl;
        cout << "Sateliti: ";
        for (vector<string>::iterator it = _sateliti->begin(); it < _sateliti->end(); it++)
            cout << *it << " ";
    }
    //Z3.10
    ~Planeta() {
        delete _sateliti; _sateliti = nullptr;
    }
};
//Z3.11
bool operator == (const Planeta& p1, const Planeta& p2) {
    return (NebeskoTijelo&)p1 == (NebeskoTijelo&)p2
        && p1.UdaljenostOdSunca == p2.UdaljenostOdSunca
        && p1.Sateliti == p2.Sateliti;
}
//Z3.12
bool operator != (const Planeta& p1, const Planeta& p2) {
    return !(p1 == p2);
}

enum class Boja { Crvena, Zuta, Plava, Bijela };
//Z4.0
ostream& operator <<(ostream& COUT, const Boja& obj) {
    switch (obj) {
    case Boja::Crvena:  COUT << "crvena"; break;
    case Boja::Zuta: COUT << "zuta"; break;
    case Boja::Plava: COUT << "plava"; break;
    case Boja::Bijela: COUT << "bijela"; break;
    default: break;
    }
    return COUT;
}
enum class Velicina { Patuljak, Div, Superdiv };
ostream& operator <<(ostream& COUT, const Velicina& obj) {
    switch (obj) {
    case Velicina::Patuljak:  COUT << "patuljak"; break;
    case Velicina::Div: COUT << "div"; break;
    case Velicina::Superdiv: COUT << "superdiv"; break;
    default: break;
    }
    return COUT;
}



class Zvijezda : public NebeskoTijelo {
private:
    unique_ptr<float> _absolutnaMagnituda; // Npr. 4.83 
    unique_ptr<int> _povrsinskaTemperatura; // u kelvinima
    pair<Boja, Velicina> _klasifikacija;
    list<Planeta> _planetarniSistem;
public:
    _declspec (property (get = GetAbsolutnaMagnituda, put = SetAbsolutnaMagnituda)) float AbsolutnaMagnituda;
    _declspec (property (get = GetTemperatura, put = SetTemperatura)) int PovrsinskaTemperatura;
    _declspec (property (get = GetBoja, put = SetBoja)) Boja Boja_;
    _declspec (property (get = GetVelicina, put = SetVelicina)) Velicina Velicina_;
    _declspec (property (get = GetPlanetarniSistem, put = SetPlanetarniSistem)) list<Planeta> Planete;
    //Z4.1
    Zvijezda() {}
    //Z4.2
    Zvijezda(const char* nz, Udaljenost pp, Masa masa, const char* sstv, float absMag, int tmp, pair<Boja, Velicina> klas)
        : NebeskoTijelo(nz,pp,masa,sstv)
    {
        _absolutnaMagnituda = make_unique<float>(absMag);
        _povrsinskaTemperatura = make_unique<int>(tmp);
        _klasifikacija = klas;

    }
    //Z4.3
    Zvijezda(const Zvijezda& obj) : NebeskoTijelo(obj), 
        _klasifikacija(obj._klasifikacija),
        _planetarniSistem(obj._planetarniSistem)
    { 
        _absolutnaMagnituda = make_unique<float>(*obj._absolutnaMagnituda);
        _povrsinskaTemperatura = make_unique<int>(*obj._povrsinskaTemperatura);
    }
    //Z4.4
    Zvijezda(Zvijezda&& obj) noexcept : 
        NebeskoTijelo(move(obj)),
        _absolutnaMagnituda(move(obj._absolutnaMagnituda)),
        _povrsinskaTemperatura(move(obj._povrsinskaTemperatura)),
        _klasifikacija(move(obj._klasifikacija)),
        _planetarniSistem(move(obj._planetarniSistem))
    {}
    //Z4.5
    float GetAbsolutnaMagnituda() const
    {
        if (_absolutnaMagnituda == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_absolutnaMagnituda;
    }
    int GetTemperatura() const
    {
        if (_povrsinskaTemperatura == nullptr)
            throw exception(GetErrorMessage(__LINE__, __FUNCTION__));
        return *_povrsinskaTemperatura;
    }
    Boja GetBoja() const { return _klasifikacija.first; }
    Velicina GetVelicina() const { return _klasifikacija.second; }
    list<Planeta> GetPlanetarniSistem() const { return _planetarniSistem; }
    //Z4.6
    void SetAbsolutnaMagnituda(float absolutnaMagnituda)
    {
        if (_absolutnaMagnituda == nullptr) _absolutnaMagnituda = make_unique<float>();
        *_absolutnaMagnituda = absolutnaMagnituda;
    }
    void SetTemperatura(int temperatura)
    {
        if (_povrsinskaTemperatura == nullptr) _povrsinskaTemperatura = make_unique<int>();
        *_povrsinskaTemperatura = temperatura;
    }
    void SetBoja(Boja boja)
    {
        _klasifikacija.first = boja;
    }
    void SetVelicina(Velicina velicina)
    {
        _klasifikacija.second = velicina;

    }
    void SetPlanetarniSistem(list<Planeta> planete)
    {
        _planetarniSistem = planete;
    }
    //Z4.7
    void DodajPlanetu(Planeta p) { _planetarniSistem.push_back(p); }
    //Z4.8
    Zvijezda& operator =(const Zvijezda& obj)
    {
        if (this!=&obj)
        {
            (NebeskoTijelo&)(*this) = obj;
            if (_absolutnaMagnituda == nullptr) _absolutnaMagnituda = make_unique<float>();
            *_absolutnaMagnituda = *obj._absolutnaMagnituda;
            if (_povrsinskaTemperatura == nullptr) _povrsinskaTemperatura = make_unique<int>();
            *_povrsinskaTemperatura = *obj._povrsinskaTemperatura;
            _klasifikacija = obj._klasifikacija;
            _planetarniSistem = obj._planetarniSistem;
        }
        return *this;
    }
    //Z4.9
    void Ispis()
    {
        NebeskoTijelo::Ispis();
        cout << "Absolutna magnituda: " << AbsolutnaMagnituda << endl;
        cout << "Povrsinska temperatura (K): " << PovrsinskaTemperatura << endl;
        cout << "Boja: " << Boja_ << endl;
        cout << "Velicina: " << Velicina_ << endl;
        cout << "----------------------PLANETE--------------------------\n";
        for (list<Planeta>::iterator it = _planetarniSistem.begin(); it != _planetarniSistem.end(); it++) {
            it->Ispis();
            cout << endl;
        }
        cout << "-------------------------------------------------------\n";

    }
    //Z4.10
    ~Zvijezda() {}
};
//Z4.11
bool operator == (const Zvijezda& z1, const Zvijezda& z2) {
    return  (NebeskoTijelo&)z1 == (NebeskoTijelo&)z2
        && z1.AbsolutnaMagnituda == z2.AbsolutnaMagnituda
        && z1.PovrsinskaTemperatura == z2.PovrsinskaTemperatura
        && z1.Boja_ == z2.Boja_
        && z1.Velicina_ == z2.Velicina_
        && z1.Planete == z2.Planete;
}
//Z4.12
bool operator != (const Zvijezda& z1, const Zvijezda& z2) {
    return !(z1 == z2);
}


//Z5.0
vector<NebeskoTijelo*> Kopiraj(vector<NebeskoTijelo*> izvor) {
    vector<NebeskoTijelo*> novi;

    for (size_t i = 0; i < izvor.size(); i++)
    {
        auto planeta = dynamic_cast<Planeta*>(izvor[i]);
        if (planeta != nullptr) {
            novi.push_back(new Planeta(*planeta));
            continue;
        }
    }
    return novi;
}
bool operator == (const vector<NebeskoTijelo*>& v1, const vector<NebeskoTijelo*>& v2);
bool operator != (const vector<NebeskoTijelo*>& v1, const vector<NebeskoTijelo*>& v2);




class Observatorija {
protected:
    unique_ptr<char> _naziv;
    const char* _lokacija;
    string _kontaktTelefon;
    string* _email;
    vector<NebeskoTijelo*> _katalog;
public:
    _declspec (property (get = GetNaziv, put = SetNaziv)) const char* Naziv;
    _declspec (property (get = GetLokacija, put = SetLokacija)) const char* Lokacija;
    _declspec (property (get = GetKontaktTelefon, put = SetKontaktTelefon)) string KontaktTelefon;
    _declspec (property (get = GetEmail, put = SetEmail)) string Email;
    _declspec (property (get = GetKatalog, put = SetKatalog)) vector<NebeskoTijelo*> Katalog;
    //Z5.1
    Observatorija() {
        _lokacija = nullptr;
        _email = nullptr;
    }
    //Z5.2
    Observatorija(const char* naziv, const char* lokacija, string kontaktTelefon, string email, vector<NebeskoTijelo*> katalog) {
        _naziv = UniqueAlokator(naziv);
        _lokacija = Alokator(lokacija);
        _kontaktTelefon = kontaktTelefon;
        _email = new string(email);
        _katalog = Kopiraj(katalog);
    }
    //Z5.3
    Observatorija(const Observatorija& obj) :
        _kontaktTelefon(obj.KontaktTelefon)
    {
        _naziv = UniqueAlokator(obj.Naziv);
        _lokacija = Alokator(obj.Lokacija);
        _email = new string(obj.Email);
        _katalog = Kopiraj(obj.Katalog);
    }
    //Z5.4
    Observatorija(Observatorija&& obj) noexcept :
        _naziv(move(obj._naziv)),
        _kontaktTelefon(move(obj._kontaktTelefon)),
        _katalog(move(obj._katalog))
    {
        _lokacija = obj._lokacija;
        obj._lokacija = nullptr;
        _email = obj._email;
        obj._email = nullptr;
    }
    //Z5.5
    const char* GetNaziv() const { return _naziv.get(); }
    const char* GetLokacija() const { return _lokacija; }
    string GetKontaktTelefon() const { return _kontaktTelefon; }
    string GetEmail() const {
        if (_email == nullptr)
            return "";
        return*_email;
    }
    vector<NebeskoTijelo*> GetKatalog() const { return _katalog; }
    //Z5.6
    void SetNaziv(const char* naziv) {
        _naziv = UniqueAlokator(naziv);
    }
    void SetLokacija(const char* lokacija) {
        delete[] _lokacija;
        _lokacija = Alokator(lokacija);
    }
    void SetKontaktTelefon(string telefon) {
        _kontaktTelefon = telefon;
    }
    void SetEmail(string email) {
        if (_email == nullptr)
            _email = new string;
        *_email = email;
    }
    void SetKatalog(vector<NebeskoTijelo*> katalog) {
        _katalog = Kopiraj(katalog);
    }
    //Z5.7
    Observatorija& operator= (const Observatorija& obj) {
        if (this == &obj)
            return *this;
        Naziv = obj.Naziv;
        Lokacija = obj.Lokacija;
        KontaktTelefon = obj.KontaktTelefon;
        Email = obj.Email;
        Katalog = obj.Katalog;
        return *this;
    }
    //Z5.8
    bool ValidirajTelefon() {
        //Neka su dozvoljeni formati -->
        //+38762111222 
        //+387 62 111-222
        //+(387)62 111-222
        string format1 = "\\+387[\\d]{8}";
        string format2 = "\\+387 [\\d]{2} [\\d]{3}\\-[\\d]{3}";
        string format3 = "\\+\\(387\\)[\\d]{2} [\\d]{3}\\-[\\d]{3}";
        string pravilo = "(" + format1 + ")|(" + format2 + ")|(" + format3 + ")";
        regex pattern(pravilo);
        return regex_match(this->KontaktTelefon, pattern);
    }
    //Z5.9
    bool ValidirajEmail() {
        //U prvom dijelu email-a, znak '.' ili '_' smije se pojaviti maksimalno jednom (ostali specijalni znakovi su zabranjeni)
        // Prvo dio emaila ne smije pocinjati niti zavrsavati znakom '.' ili '_'
        //Mora postojati znak '@'
        //Zavrsetak mora biti validna domena tipa: gmail.com, bih.net, outlook.com, edu.fit.ba
        string pravilo = "[\\w]+[._]?[\\w]+@(gmail.com|bih.net|hotmail.com|outlook.com|edu.fit.ba)";
        regex pattern(pravilo);
        return regex_match(this->Email, pattern);
    }

    //Z5.10
    template<class T>
    void DodajNebeskoTijelo(T nebeskoTijelo) {
        if (typeid(T) == typeid(NebeskoTijelo) || typeid(T) == typeid(Planeta) || typeid(T) == typeid(Zvijezda))
            _katalog.push_back(new T(nebeskoTijelo));
    }
    //Z5.11
    ~Observatorija() {
        delete[] _lokacija;
        _lokacija = nullptr;
        delete _email;
        _email = nullptr;
        for (size_t i = 0; i < _katalog.size(); i++)
        {
            delete _katalog[i];
            _katalog[i] = nullptr;
        }
    }
};
//Z5.12
ostream& operator <<(ostream& COUT, const Observatorija& obj) {
    COUT << "Naziv: " << obj.Naziv << endl;
    COUT << "Lokacija (adresa): " << obj.Lokacija << endl;
    COUT << "Kontakt telefon: " << obj.KontaktTelefon << endl;
    COUT << "Email: " << obj.Email << endl;
    for (size_t i = 0; i < obj.Katalog.size(); i++) {
        obj.Katalog[i]->Ispis();
        COUT << endl;
    }
    return COUT;
}
//Z5.13
bool operator == (const Observatorija& o1, const Observatorija& o2) {
   /* return CheckIfIsti(o1.Naziv, o2.Naziv)
        && CheckIfIsti(o1.Lokacija, o2.Lokacija)
        && o1.KontaktTelefon == o2.KontaktTelefon
        && o1.Email == o2.Email
        && o1.Katalog == o2.Katalog;*/
    return true;
}

auto IspisiPoruku = [](const char* tipFunkcije, bool success) {
    cout << tipFunkcije << " se izvrsio " << ((success) ? "uspjesno!" : "bezuspjesno!") << endl;
};

void Zadatak1() {
    Udaljenost sirinaGalaksije; //Proxima Centauri
    sirinaGalaksije.Vrijednost = 130000.0f;
    sirinaGalaksije.Jedinica = JedinicaUdaljenosti::ly;
    cout << "Sirina galaksije Mlijecni put: " << sirinaGalaksije << endl;
    Udaljenost u1(sirinaGalaksije.Vrijednost, sirinaGalaksije.Jedinica);
    IspisiPoruku("User-def. ctor", sirinaGalaksije == u1);
    Udaljenost u2(sirinaGalaksije);
    IspisiPoruku("Copy ctor", sirinaGalaksije == u2);
    Udaljenost u3(move(u1));
    IspisiPoruku("Move ctor", sirinaGalaksije == u3);
    Udaljenost u4;
    u4 = sirinaGalaksije;
    IspisiPoruku("Operator '='", sirinaGalaksije == u4);
    cout << endl;
    Masa masaSjevernjace;
    masaSjevernjace.Jedinica = JedinicaMase::SM;
    masaSjevernjace.Vrijednost = 5.4f;
    cout << "Masa zvijezde Polaris: " << masaSjevernjace << endl;
    Masa m1(masaSjevernjace.Vrijednost, masaSjevernjace.Jedinica);
    IspisiPoruku("User-def. ctor", masaSjevernjace == m1);
    Masa m2(masaSjevernjace);
    IspisiPoruku("Copy ctor", masaSjevernjace == m2);
    Masa m3(move(m1));
    IspisiPoruku("Move ctor", masaSjevernjace == m3);
    Masa m4;
    m4 = masaSjevernjace;
    IspisiPoruku("Operator '='", masaSjevernjace == m4);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak2() {
   NebeskoTijelo sagittariusA;
   sagittariusA.Naziv = "Sagittarius A* - Supermasivna crna rupa";
   sagittariusA.Poluprecnik = Udaljenost(22000000.0f, JedinicaUdaljenosti::km);
   sagittariusA.Masa_ = Masa(4.15e6, JedinicaMase::SM);
   sagittariusA.Sastav = "vodik, helij";
   sagittariusA.Ispis();
   NebeskoTijelo t1(sagittariusA.Naziv.c_str(), sagittariusA.Poluprecnik, sagittariusA.Masa_, sagittariusA.Sastav.c_str());
   IspisiPoruku("User-def. ctor", sagittariusA == t1);
   NebeskoTijelo t2(sagittariusA);
   IspisiPoruku("Copy ctor", sagittariusA == t2);
   NebeskoTijelo t3(move(t1));
   IspisiPoruku("Move ctor", sagittariusA == t3);
   NebeskoTijelo t4;
   t4 = sagittariusA;
   IspisiPoruku("Operator '='", sagittariusA == t4);
   cout << endl << "Dealokacija..." << endl;
}
void Zadatak3() {
    Planeta uran;
    uran.Naziv = "Uran";
    uran.Poluprecnik = Udaljenost(4.007f, JedinicaUdaljenosti::er);
    uran.Masa_ = Masa(15.54f, JedinicaMase::EM);
    uran.Sastav = "vodik, helij, voda, metan, amonijak";
    uran.UdaljenostOdSunca = Udaljenost(19.21f, JedinicaUdaljenosti::au);
    uran += "Miranda";
    uran += "Umbriel";
    uran += "Titania";
    uran += "Oberon";
    uran.Ispis();
    cout << endl;
    Planeta p1(uran.Naziv.c_str(), uran.Poluprecnik, uran.Masa_, uran.Sastav.c_str(), uran.UdaljenostOdSunca, uran.Sateliti);
    IspisiPoruku("User-def. ctor", uran == p1);
    Planeta p2(uran);
    IspisiPoruku("Copy ctor", uran == p2);
    Planeta p3(move(p1));
    IspisiPoruku("Move ctor", uran == p3);
    Planeta p4;
    p4 = uran;
    IspisiPoruku("Operator '='", uran == p4);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak4() {
    Zvijezda vyCma;
    vyCma.Naziv = "VY Canis Majoris";
    vyCma.Poluprecnik = Udaljenost(2069.0f, JedinicaUdaljenosti::sr);
    vyCma.Masa_ = Masa(17.5, JedinicaMase::SM);
    vyCma.Sastav = "vodik, helij, litij, ...";
    vyCma.AbsolutnaMagnituda = -0.72f;
    vyCma.PovrsinskaTemperatura = 3490;
    vyCma.Boja_ = Boja::Crvena;
    vyCma.Velicina_ = Velicina::Superdiv;
    Planeta p1("CMa-1", Udaljenost(0.5f, JedinicaUdaljenosti::er), Masa(1.3f, JedinicaMase::EM), "zeljezo", Udaljenost(0.7f, JedinicaUdaljenosti::au), {});
    Planeta p2("CMa-2", Udaljenost(0.7f, JedinicaUdaljenosti::er), Masa(2.0f, JedinicaMase::EM), "zeljezo", Udaljenost(5.3f, JedinicaUdaljenosti::au), {});
    vyCma.DodajPlanetu(p1);
    vyCma.DodajPlanetu(p2);
    vyCma.Ispis();
    Zvijezda z1(vyCma.Naziv.c_str(), vyCma.Poluprecnik, vyCma.Masa_, vyCma.Sastav.c_str(),
        vyCma.AbsolutnaMagnituda, vyCma.PovrsinskaTemperatura, pair<Boja, Velicina>(vyCma.Boja_, vyCma.Velicina_));
    z1.Planete = vyCma.Planete;
    IspisiPoruku("User-def. ctor", vyCma == z1);
    Zvijezda z2(vyCma);
    IspisiPoruku("Copy ctor", vyCma == z2);
    Zvijezda z3(move(z1));
    IspisiPoruku("Move ctor", vyCma == z3);
    Zvijezda z4;
    z4 = vyCma;
    IspisiPoruku("Operator '='", vyCma == z4);
    cout << endl << "Dealokacija..." << endl;
}
void Zadatak5() {
   Observatorija zvjezdarnica;
   zvjezdarnica.Naziv = "Zvjezdarnica";
   zvjezdarnica.Lokacija = "Sarajevo, BiH";
   zvjezdarnica.Email = "zvjezdarnica_ba@gmail.com";
   zvjezdarnica.KontaktTelefon = "+(387)62 546-241";
   NebeskoTijelo messier61;
   messier61.Naziv = "Messier 61 - Supermasivna crna rupa";
   messier61.Poluprecnik = Udaljenost(133000000.0f, JedinicaUdaljenosti::km);
   messier61.Masa_ = Masa(70.15e6, JedinicaMase::SM);
   messier61.Sastav = "vodik, helij";
   Planeta nibiru;
   nibiru.Naziv = "Nibiru - planeta Anunnakija";
   nibiru.Poluprecnik = Udaljenost(2.607f, JedinicaUdaljenosti::er);
   nibiru.Masa_ = Masa(21.3f, JedinicaMase::EM);
   nibiru.Sastav = "voda, zeljezo, amonijak";
   nibiru.UdaljenostOdSunca = Udaljenost(10.3f, JedinicaUdaljenosti::au);
   nibiru.Sateliti = vector<string>();
   Zvijezda uyScuti;
   uyScuti.Naziv = "UY Scuti";
   uyScuti.Poluprecnik = Udaljenost(3500.0f, JedinicaUdaljenosti::sr);
   uyScuti.Masa_ = Masa(19.45f, JedinicaMase::SM);
   uyScuti.Sastav = "vodik, helij";
   uyScuti.AbsolutnaMagnituda = -0.69f;
   uyScuti.PovrsinskaTemperatura = 4150;
   uyScuti.Boja_ = Boja::Crvena;
   uyScuti.Velicina_ = Velicina::Superdiv;
   zvjezdarnica.DodajNebeskoTijelo<NebeskoTijelo>(messier61);
   zvjezdarnica.DodajNebeskoTijelo<Planeta>(nibiru);
   zvjezdarnica.DodajNebeskoTijelo<Zvijezda>(uyScuti);
   cout << zvjezdarnica << endl;
   cout << "Telefon je u " << (zvjezdarnica.ValidirajTelefon() ? "validnom" : "nevalidnom") << " formatu" << endl;
   cout << "Email je u " << (zvjezdarnica.ValidirajEmail() ? "validnom" : "nevalidnom") << " formatu" << endl;
   
   Observatorija o1(zvjezdarnica.Naziv, zvjezdarnica.Lokacija, zvjezdarnica.KontaktTelefon.c_str(), zvjezdarnica.Email.c_str(), zvjezdarnica.Katalog);
   IspisiPoruku("User-def. ctor", zvjezdarnica == o1);
   Observatorija o2(zvjezdarnica);
   IspisiPoruku("Copy ctor", zvjezdarnica == o2);
   Observatorija o3(move(o1));
   IspisiPoruku("Move ctor", zvjezdarnica == o3);
   Observatorija o4;
   o4 = zvjezdarnica;
   IspisiPoruku("Operator '='", zvjezdarnica == o4);
   cout << endl << "Dealokacija..." << endl;
}

int main() {
    int nastaviDalje = 1;
    while (nastaviDalje) {
        int izbor = 0;
        do {
            system("cls");
            cout << "::Zadaci::" << endl;
            cout << "(1) Zadatak 1" << endl;
            cout << "(2) Zadatak 2" << endl;
            cout << "(3) Zadatak 3" << endl;
            cout << "(4) Zadatak 4" << endl;
            cout << "(5) Zadatak 5" << endl;
            cout << "Unesite broj za testiranje zadatka: -->: ";
            cin >> izbor;
            cout << endl;
        } while (izbor <= 0 || izbor > 5);
        switch (izbor) {
        case 1: Zadatak1(); cout << "Done." << endl; break;
        case 2: Zadatak2(); cout << "Done." << endl; break;
        case 3: Zadatak3(); cout << "Done." << endl; break;
        case 4: Zadatak4(); cout << "Done." << endl; break;
        case 5: Zadatak5(); cout << "Done." << endl; break;
        default:
            break;
        }
        do {
            cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
            cin >> nastaviDalje;
        } while (nastaviDalje != 0 && nastaviDalje != 1);
    }
    return 0;
}

