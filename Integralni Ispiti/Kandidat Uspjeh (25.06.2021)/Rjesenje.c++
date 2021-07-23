#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

mutex m;
bool ValidirajBrojTelefona(string brTf) {
    return regex_match(brTf, regex("[+][0-9]{2,3}\\s?[0]?[0-9]{2}\\s?[0-9]{2,3}?\\s?\\-?[0-9]{2,3}"));
}

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
    bool _omoguciDupliranje;
    void Delete(){ delete[]_elementi1;  delete[]_elementi2;}
public:          
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _omoguciDupliranje = omoguciDupliranje;
    }
    Kolekcija(const Kolekcija& obj) {
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
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this!=&obj)
        {
            _trenutno = obj._trenutno;
            _omoguciDupliranje = obj._omoguciDupliranje;
            Delete();
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
    void AddElement(const T1& el1, const T2& el2) {
        if (!_omoguciDupliranje)
            for (size_t i = 0; i < _trenutno; i++)
                if (_elementi1[i] == el1 || _elementi2[i] == el2)
                    throw exception("Nije moguce dodati isti element!");

        T1* temp1 = new T1[_trenutno + 1];
        T2* temp2 = new T2[_trenutno + 1];
        for (size_t i = 0; i < _trenutno; i++)
        {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        Delete();
        _elementi1 = temp1;
        _elementi2 = temp2;
        _elementi1[_trenutno] = el1;
        _elementi2[_trenutno++] = el2;
    }
    Kolekcija<T1, T2> operator ()(int from, int to) {
        if(from < 0 || to > _trenutno)
            throw exception("Lokacija nije validna!");

        Kolekcija<T1, T2> nova;
        for (size_t i = from; i <= to; i++)
            nova.AddElement(_elementi1[i], _elementi2[i]);
        return nova;
           
    }
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }

    bool operator==(const Datum& obj) {return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina;}

    Datum& operator=(const Datum& obj) {
        if (this != &obj)
        {
            *_dan = *obj._dan;
            *_mjesec = *obj._mjesec;
            *_godina = *obj._godina;

        }
        return *this;
    }
    int toDays()const
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    bool operator>(const Datum& drugi)
    {
        return this->toDays() > drugi.toDays();
    }

    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

class Predmet {
    char* _naziv;
    Kolekcija<Datum*, int>* _ocjene;
public:
    Predmet(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = nullptr;
        if (ocjena > 0)
            AddOcjena(datum, ocjena);
    }

    void AddOcjena(const Datum& d, int ocjena) {
        if (_ocjene == nullptr)
            _ocjene = new Kolekcija<Datum*, int>;
        _ocjene->AddElement(new Datum(d), ocjena);
    }
    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv() const { return _naziv; }
    Kolekcija<Datum*, int>&  GetOcjene() { return *_ocjene; }
    float ProsjekPredmet() const {
        if (_ocjene->getTrenutno() == 0) return 0;
        float sum = 0.0f;
        for (size_t i = 0; i < _ocjene->getTrenutno(); i++)
            sum += _ocjene->getElement2(i);
        return float(sum /= _ocjene->getTrenutno());
    }
    friend ostream& operator<< (ostream& cout, const Predmet& obj) {
        cout << "Naziv:" << obj._naziv << "\n";
        for (size_t i = 0; i < obj._ocjene->getTrenutno(); i++)
            cout << "Ocjena:" << obj._ocjene->getElement2(i) << "\tDatum:" << *obj._ocjene->getElement1(i) << "\n";
        cout << "Prosjek:" << obj.ProsjekPredmet();
        return cout;
    }
    bool operator==(const Predmet& obj) {
        if (strcmp(obj._naziv, _naziv) == 0)
        {
            if (_ocjene->getTrenutno() == obj._ocjene->getTrenutno())
            {
                for (size_t i = 0; i < _ocjene->getTrenutno(); i++) 
                {
                    if (*_ocjene->getElement1(i) == *obj._ocjene->getElement1(i)
                        && _ocjene->getElement2(i) == obj._ocjene->getElement2(i))
                        return true;
                }
            }
        }
        return false;
                
    }
};
class Uspjeh {
    eRazred _razred;
    //char* se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet*, const char*> _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
    }
  
   
    Kolekcija<Predmet*, const char*>& GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << obj._razred << "\n";
        for (size_t i = 0; i < obj._polozeniPredmeti.getTrenutno(); i++)
            COUT << *obj._polozeniPredmeti.getElement1(i) << "\tNapomena:" << obj._polozeniPredmeti.getElement2(i) << "\n";
        return COUT;
    }
    void DodajPredmet(const Predmet& p, const char* napomena) {
        _polozeniPredmeti.AddElement(new Predmet(p), napomena);
    }
    float Total() {
        if (_polozeniPredmeti.getTrenutno() == 0) return 0;
        float sum = 0.0f;
        for (size_t i = 0; i < _polozeniPredmeti.getTrenutno(); i++)
            sum += _polozeniPredmeti.getElement1(i)->ProsjekPredmet();
        return float(sum /= _polozeniPredmeti.getTrenutno());
    }
};

class Kandidat {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;

    void PosaljiMail(string email, const char* ime, eRazred razred, float zaRazredProsjek, float zaSkolovanje) {
        m.lock();
        cout << "FROM:info@fit.ba\n" << "TO:" << email << "\nPostovani " << ime << ", evidentirali ste uspjeh za " << (razred) <<
            "  razred.Dosadasnji uspjeh (prosjek)\nna nivou " << (razred) << " iznosi " << zaRazredProsjek << ", a ukupni uspjeh u toku skolovanja iznosi " << zaSkolovanje <<
            ".\nPozdrav,\nFITTeam.\n";
        m.unlock();
    }
    void SendMsg(float prosjek, eRazred r) {
        m.lock();
        cout << "Svaka cast za uspjeh " << prosjek << " u " << r << " razredu.\n";
        m.unlock();
    }
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        if (ValidirajBrojTelefona(brojTelefona))
            _brojTelefona = brojTelefona;
        else
            _brojTelefona = "NOT VALID";
    }
    Kandidat(const Kandidat& obj) : _uspjeh(obj._uspjeh)
    {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            delete[]_imePrezime;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _uspjeh = obj._uspjeh;
        }
        return *this;
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    float Dosad(eRazred r) {
        if (_uspjeh.size() == 0) return 0;
        float sum = 0.0f;
        for (auto u : _uspjeh)
        {
            if (u.GetERazred() == r) {
                for (int i = 0; i < u.GetPredmeti().getTrenutno(); i++)
                    sum += u.GetPredmeti().getElement1(i)->ProsjekPredmet();
                return float(sum /= u.GetPredmeti().getTrenutno());
            }
        }
    }
    bool AddPredmet(eRazred razred,const Predmet& predmet,const char* napomena) {
         if (predmet.ProsjekPredmet() < 2.5)  
             return false;

         for (auto uspjeh : _uspjeh)
         {
             if(razred == uspjeh.GetERazred())
                 for (size_t i = 0;  i < uspjeh.GetPredmeti().getTrenutno(); i++)
                 {
                     if (uspjeh.GetPredmeti().getTrenutno() >= 5) return false;
                     if (*uspjeh.GetPredmeti().getElement1(i) == predmet) return false;
                 } 
         }

         Uspjeh uspjeh(razred);
         uspjeh.DodajPredmet(predmet, napomena);
         thread t(&Kandidat::PosaljiMail, this, _emailAdresa, GetImePrezime(), razred, Dosad(razred), uspjeh.Total());
         t.join();
         if (ValidirajBrojTelefona(GetBrojTelefona()) && predmet.ProsjekPredmet() > 4.5)
         {
             thread t_sms(&Kandidat::SendMsg, this, uspjeh.Total(), uspjeh.GetERazred());
             t_sms.join();
         }
         _uspjeh.push_back(uspjeh);
         return true;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
    float GetProsjecanBrojDana()
    {
        float sum = 0.0f;
        for (int i = 0; i < _uspjeh.size(); i++)
            for (int j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++)
            {
                for (int k = 0; k < _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno() - 1; k++)
                    sum = _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k)->toDays() + _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k + 1)->toDays();
                return sum / _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno();

            }

    }
    Kolekcija<Predmet, float> operator()(Datum* from, Datum* to)
    {
        Kolekcija<Predmet, float> nova;
        for (auto uspjeh : _uspjeh)
           for (size_t i = 0; i < uspjeh.GetPredmeti().getTrenutno(); i++)
               for (size_t j = 0; j < uspjeh.GetPredmeti().getElement1(i)->GetOcjene().getTrenutno(); j++)
                   if (uspjeh.GetPredmeti().getElement1(i)->GetOcjene().getElement1(j) > from && uspjeh.GetPredmeti().getElement1(i)->GetOcjene().getElement1(j) < to)
                       nova.AddElement(*uspjeh.GetPredmeti().getElement1(i), GetProsjecanBrojDana());
        return nova;
    }
   
};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite ulogu i nacin koristenja generickog tipa future<>?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    //cout << PORUKA;
    //cin.get();
    //
    //cout << GetOdgovorNaPrvoPitanje() << endl;
    //cin.get();
    //cout << GetOdgovorNaDrugoPitanje() << endl;
    //cin.get();
    //
    Datum
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);
    
    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);
    
    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;
    
    ///*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    //ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    
    //parametri: nazivPredmeta, datum, prva ocjena
    Predmet Matematika("Matematika", datum19062021, 5),
        Fizika("Fizika", datum20062021, 5),
        Hemija("Hemija", datum30062021, 2),
        Engleski("Engleski", datum05072021, 5);
    
    Matematika.AddOcjena(datum05072021, 3);
    Matematika.AddOcjena(datum05072021, 3);
    
    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
    cout << Matematika << crt;
    //
    //
    ///*
    //broj telefona mora biti u formatu
    //- znak +
    //- pozivni broj drzave (2 ili 3 cifre)
    //- pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
    //- prvi dio broja (2 ili 3 cifre)
    //- razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
    // - drugi dio broja (2 ili 3 cifre)
    //ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
    //*/
    //
    if (ValidirajBrojTelefona("+38761222333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222-333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222 333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+387061222 333"))
        cout << "Broj telefona validan" << crt;
    if (!ValidirajBrojTelefona("+38761 222 333"))
        cout << "Broj NIJE telefona validan" << crt;
    if (!ValidirajBrojTelefona("+387 61222 333"))
        cout << "Broj NIJE telefona validan" << crt;
    //
    //
    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "+38761222333");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "+387061222 333");
    Kandidat brojTelefonaNotValid("Ime Prezime", "korisnik@klix.ba", "+387 61222 333");
    //
    ///*
    //uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    //tom prilikom onemoguciti:
    //- dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
    //- dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    //- dodavanje vise od 5 predmeta na nivou jednog razreda
    //razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    //Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    //*/

    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
     if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
       cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
       cout << "Predmet uspjesno dodan!" << crt;
   //Matematiku je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;
    
    ///*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    //FROM:info@fit.ba
    //TO: emailKorisnika
    //Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    //na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    //Pozdrav.
    //FIT Team.
    //ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". 
    // Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, 
    // u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“
    //slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    //*/
    cout << jasmin << crt;
    
    ////vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    ////float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(new Datum(18, 06, 2021), new  Datum(21, 06, 2021));
    cout << jasminUspjeh << crt;
    
    cin.get();
    system("pause>0");
}