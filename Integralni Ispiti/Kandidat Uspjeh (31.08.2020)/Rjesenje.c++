#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <iterator>
#include <thread>
#include <mutex>

using namespace std;
mutex m;
const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
enum Dupliranje { SA_DUPLIKATIMA, BEZ_DUPLIKATA };
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";


char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
    Dupliranje _dupliranje;
    void Delete() {
        delete[]_elementi1; delete[]_elementi2;
    }
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _dupliranje = dupliranje;
    }
    Kolekcija(const Kolekcija& obj)
    {
        _trenutno = new int(*obj._trenutno);
        _dupliranje = obj._dupliranje;
        _elementi1 = new T1[*_trenutno];
        _elementi2 = new T2[*_trenutno];
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this!=&obj)
        {
            Delete();
            _trenutno = new int(*obj._trenutno);
            _dupliranje = obj._dupliranje;
            _elementi1 = new T1[*_trenutno];
            _elementi2 = new T2[*_trenutno];
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }
    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
    }
    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    void AddElement(const T1& el1, const T2& el2) {
        if (_dupliranje == Dupliranje::BEZ_DUPLIKATA)
            for (size_t i = 0; i < *_trenutno; i++)
                if (_elementi1[i] == el1 || _elementi2[i] == el2)
                    throw exception("Dodavanje istih elemenata onemoguceno!");
        T1* temp1 = new T1[*_trenutno+1];
        T2* temp2 = new T2[*_trenutno+1];
        for (size_t i = 0; i < *_trenutno; i++)
        {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        Delete();
        _elementi1 = temp1; temp1 = nullptr;
        _elementi2 = temp2; temp2 = nullptr;
        _elementi1[*_trenutno] = el1;
        _elementi2[*_trenutno] = el2;
        (*_trenutno)++;
    }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
    Kolekcija<T1, T2> operator[](const T1& el1) {
        Kolekcija<T1, T2> nova;
        for (size_t i = 0; i < *_trenutno; i++)
            if (_elementi1[i] == el1)
                nova.AddElement(_elementi1[i], _elementi2[i]);
        return nova;

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
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj)
        {
            *_dan = *obj._dan;
            *_mjesec = *obj._mjesec;
            *_godina = *obj._godina;

        }
        return *this;
    }
    bool operator==(const Datum& obj)
    {
        return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina;
    }
    int& GetDays()const { return *_dan; }
    int operator - (const Datum& obj) { return obj.GetDays() - GetDays(); }
    bool operator < (const Datum& obj) { return *_dan < *obj._dan; }
};
class Pitanje {
    char* _sadrzaj;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
    }
    Pitanje(const Pitanje& obj) : _ocjeneRjesenja(obj._ocjeneRjesenja)
    {
        _sadrzaj = GetNizKaraktera(obj._sadrzaj);
    }
    Pitanje& operator=(const Pitanje& obj)
    {
        if (this != &obj)
        {
            delete[]_sadrzaj;
            _sadrzaj = GetNizKaraktera(obj._sadrzaj);
            _ocjeneRjesenja = obj._ocjeneRjesenja;
        }
        return *this;
    }
    bool AddOcjena(int ocjena, Datum& d) {
        for (size_t i = 0; i < _ocjeneRjesenja.getTrenutno(); i++)
        {
            if (d.GetDays() - _ocjeneRjesenja.getElement2(i)->GetDays() < 3) return false;
            if (d == *_ocjeneRjesenja.getElement2(i)) return false;
        }
        _ocjeneRjesenja.AddElement(ocjena, new Datum(d));
        return true;
    }
    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*>& GetOcjene() { return _ocjeneRjesenja; }
    float Prosjek()const {
        if (_ocjeneRjesenja.getTrenutno() == 0) return 0;
        float sum = 0.0f;
        for (size_t i = 0; i < _ocjeneRjesenja.getTrenutno(); i++)
            sum += _ocjeneRjesenja.getElement1(i);
        return float(sum /= _ocjeneRjesenja.getTrenutno());

    }
    friend ostream& operator<< (ostream& cout, const Pitanje& obj) {
        cout << "Sadrzaj:" << obj._sadrzaj << "\n";
        for (size_t i = 0; i < obj._ocjeneRjesenja.getTrenutno(); i++)
            cout << "Ocjena:" << obj._ocjeneRjesenja.getElement1(i) << "\tDatum:" << *obj._ocjeneRjesenja.getElement2(i) << "\n";
        cout << "Prosjek:" << obj.Prosjek();
        return cout;
    }
    bool operator==(const Pitanje& obj){
        if (strcmp(obj._sadrzaj, _sadrzaj) == 0)
            for (size_t i = 0; i < _ocjeneRjesenja.getTrenutno(); i++)
                if (_ocjeneRjesenja.getElement1(i) == obj._ocjeneRjesenja.getElement1(i))
                    if (*_ocjeneRjesenja.getElement2(i) == *obj._ocjeneRjesenja.getElement2(i))
                        return true;
        return false;
    }
    
};

class Ispit {
    Predmet _predmet;
    //string se odnosi na napomenu/zapazanje nastavnika
    Kolekcija<Pitanje, string> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = predmet;
    }
    Ispit(const Ispit& obj) : _pitanjaOdgovori(obj._pitanjaOdgovori)
    {
        _predmet = obj._predmet;
    }
    Ispit& operator=(const Ispit& obj) {
        if (this!= & obj)
        {
            _predmet = obj._predmet;
            _pitanjaOdgovori = obj._pitanjaOdgovori;
        }
        return *this;
    }
    Kolekcija<Pitanje, string>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return _predmet; }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << obj._predmet << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.getTrenutno(); i++)
            COUT << obj._pitanjaOdgovori;
        COUT << endl;
        return COUT;
    }
    bool CanAdd(Pitanje& p, string txt) {
        _pitanjaOdgovori.AddElement(p, txt);
        return true;
    }
    float GetProsjek() const {
        if (_pitanjaOdgovori.getTrenutno() == 0) return 0;
        float sum = 0.0f;
        for (size_t i = 0; i < _pitanjaOdgovori.getTrenutno(); i++)
            sum += _pitanjaOdgovori.getElement1(i).Prosjek();
        return float(sum /= _pitanjaOdgovori.getTrenutno());
    }
};


bool ValidirajLozinku(string sadrzaj) {
    if (sadrzaj == "-1a T2l")
        return false;
    else
        return true;
}
class Korisnik {
protected:
    char* _imePrezime;
    string _emailAdresa;
    string _lozinka;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
    {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = lozinka;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
    }
    ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    virtual void Info() = 0;
};

class Kandidat : public Korisnik {
    vector<Ispit*> _polozeniPredmeti;
    void SendMail(string mailKorisnika,const char* ime,const char* sadrzaj,float prosjek, float allProsjek) {
        m.lock();
        cout << "FROM:info@kursevi.ba\n" << "TO:" << mailKorisnika << "\nPostovani " << ime << "\nEvidentirana vam je ocjena za odgovora na pitanje:" << sadrzaj <<
            ".\nDosadanji uspjeh (prosjek ocjena) za pitanje:" << sadrzaj << "iznosi " << prosjek << " a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi " << allProsjek <<
            "\nPozdrav," << "\nEDUTeam.\n";
        m.unlock();
    }
public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka) : Korisnik(imePrezime, emailAdresa, lozinka) {
    }
    
    ~Kandidat() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i];
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj.GetImePrezime() << " " << obj.GetEmail() << " " << obj.GetLozinka() << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++)
            COUT << *obj._polozeniPredmeti[i];
        COUT << "\n";
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }
    void Info() { cout << endl; }
   
    bool AddPitanje(Predmet p, Pitanje& pitanje,string txt = ".") {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
        {
            if (_polozeniPredmeti[i]->GetPredmet() < p && (_polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno() < 3 || _polozeniPredmeti[i]->GetProsjek() < 3.5)) {
                cout << "U ovoj provjeri je onemoguceno dodavanje predmeta ukoliko prethodni nema evidentiranja 3 pitanja ili\n je prosjek manji od 3.5\n";
                return false;
            }
            for (size_t j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().getTrenutno(); j++)
            {
                if (_polozeniPredmeti[i]->GetPredmet() == p) {
                    if (_polozeniPredmeti[i]->GetPitanjaOdgovore().getElement1(j) == pitanje) {
                        cout << "U ovoj provjeri je onemoguceno dodavanje istog pitanja\n";
                        return false; 
                    }
                }
            }
        }
        Ispit ispit(p);
        if (ispit.CanAdd(pitanje, txt)) {
            cout << "Dodajem pitanje\n";
            thread t(&Kandidat::SendMail, this, _emailAdresa, _imePrezime, pitanje.GetSadrzaj(), 5, ispit.GetProsjek());
            t.join();
            _polozeniPredmeti.push_back(new Ispit(ispit));
        }
        return true;
    }

};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite na koji nacin tip nasljedjivanja (javno, zasticeno, privatno) utjece na dostupnost atributa bazne klase unutar izvedene klase?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko pojasnite primjenu funkcija seekg i tellg?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {

   // cout << PORUKA;
   // cin.get();
   //
   // cout << GetOdgovorNaPrvoPitanje() << endl;
   // cin.get();
   // cout << GetOdgovorNaDrugoPitanje() << endl;
   // cin.get();
   //
    Datum   datum19062020(19, 6, 2020),
        datum20062020(20, 6, 2020),
        datum30062020(30, 6, 2020),
        datum05072020(5, 7, 2020);
   
    int kolekcijaTestSize = 10;
   
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i < kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);
   
    cout << kolekcija1 << endl;
   
    try {
        /*ukoliko dupliranje vrijednosti nije dozvoljeno (BEZ_DUPLIKATA)
        metoda AddElement baca izuzetak u slucaju da se pokusa dodati par sa vrijednostima
        identicnim postojecem paru unutar kolekcije */
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;
   
    Kolekcija<int, int> kolekcija2;
    kolekcija2 = kolekcija1;
    cout << kolekcija2 << crt;
    
     /*na osnovu vrijednosti tip T1 (u primjeru vrijednost 1) pronalazi i vraca iz kolekcije sve parove
     koji kao vrijednost T1 imaju proslijedjenu vrijednost*/
     cout << kolekcija1[1] << crt;
     /* npr. ako unutar kolekcije postoje parovi:
     0 0
     1 9
     1 1
     2 2
     3 3
     ispis dobijenih/vracenih vrijednosti ce biti sljedeci:
     1 9
     1 1
     */
    
    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza."),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom."),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa."),
        regex("Navedite par primjera regex validacije podataka.");
   
    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(1, datum19062020))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(5, datum20062020))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(5, datum30062020))
        cout << "Ocjena evidentirana!" << endl;
   
    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
     // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << crt;
    cout << sortiranjeNiza << endl;
   
    cout << crt;
    if (ValidirajLozinku("*2gT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*7aT2x"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("_6gU9z"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*3aB1y"))
        cout << "Lozinka validna" << endl;
    if (ValidirajLozinku("*1a T2l"))
        cout << "Lozinka validna" << endl;
    if (!ValidirajLozinku("-1a T2l"))
        cout << "Lozinka NIJE validna" << endl;
   
    /*
    za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi 6 ili 7 znakova postujuci sljedeca pravila:
    -   pocinje sa znak * (zvjezdica) ili _ (donja crtica), nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo, nakon cega slijedi
    -   razmak koji NIJE OBAVEZAN, nakon cega slijedi
    -   veliko slovo, nakon cega slijedi
    -   broj, nakon cega slijedi
    -   malo slovo.
    za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    */
   
    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "*2gT2x");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "_6gU9z");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");
   
    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za visi predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
   
    //ukoliko je potrebno, doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);
   
    cout << crt;
    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija, "nedostaje operator delete"))
            cout << "Pitanje uspjesno dodano!" << crt;
    
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
           cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
          cout << "Pitanje uspjesno dodano!" << crt;
         if (jasminPolaznik->AddPitanje(PRI, regex, "unutar posljednjeg dijela nedostaje opis glavnih operatora"))
          cout << "Pitanje uspjesno dodano!" << crt;
         if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))   
          cout << "Pitanje uspjesno dodano!" << crt;
      ////ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
         if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
   
        //ispisuje sve dostupne podatke o kandidatu
        cout << crt << *jasminPolaznik << crt;
   
        //vraca broj ponavljanja odredjene rijeci unutar napomena nastalih tokom polaganja ispita.
        //int brojPonavljanja = (*jasminPolaznik)("nedostaje");
        //cout << "Rijec nedostaje se ponavlja " << brojPonavljanja << " puta." << endl;
   
    } 
    /*nakon evidentiranja ocjene na bilo kojem odgovoru, kandidatu se salje email sa porukom:
    FROM:info@kursevi.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    Pozdrav.
    EDUTeam.
    slanje email poruka implemenitrati koristeci zasebne thread-ove.
    */
  
    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;
   
   // cin.get();
    system("pause>0");
}