#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <regex>
#include <thread>
#include <mutex>
using namespace std;


mutex m;
const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
enum SortirajPo { T1, T2 };

bool ValidirajMail(string mail) {
	return regex_match(mail, regex("(([a-zA-Z]{2,})([\\@])(edu.fit|outlook)(\\.)(com|ba))"));
}

char* Alociraj(const char* sadrzaj) {
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
public:
	Kolekcija(bool omoguciDupliranje = true) {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_omoguciDupliranje = omoguciDupliranje;
	}
	Kolekcija(const Kolekcija& obj)
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
	Kolekcija& operator=(const Kolekcija& obj)
	{
		if (this!= &obj)
		{
			delete[]_elementi1; delete[]_elementi2;
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
		return *this;
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
		delete[]_elementi1; delete[]_elementi2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno++] = el2;
	}		
	void SortirajRastuci(SortirajPo vrsta) {
		bool promena = true;
		while (promena)
		{
			promena = false;
			for (size_t i = 0; i < _trenutno-1; i++)
			{
				if ((_elementi1[i] > _elementi1[i + 1] && vrsta == SortirajPo::T1) || (_elementi2[i] > _elementi2[i + 1] && vrsta == SortirajPo::T2)) {
					swap(_elementi1[i], _elementi2[i + 1]);
					swap(_elementi2[i], _elementi2[i + 1]);
				}
			}
		}
	}
};

class DatumVrijeme {
	int* _dan, * _mjesec, * _godina, * _sati, * _minuti;
public:
	DatumVrijeme(int dan = 1, int mjesec = 1, int godina = 2000, int sati = 0, int minuti = 0) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
		_sati = new int(sati);
		_minuti = new int(minuti);
	}
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti << endl;
		return COUT;
	}
	DatumVrijeme(const DatumVrijeme& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);
	}
	bool operator > (const DatumVrijeme& d)
	{
		return GetMinutes() > d.GetMinutes();
	}
	bool operator < (const DatumVrijeme& d)
	{
		return !(*this > d);
	}
	int GetMinutes() const
	{
		return *_minuti + *_sati * 60 + *_dan * 1440 + *_mjesec * 43200 + *_godina * 518400;
	}
	int operator - (const DatumVrijeme& d)
	{
		return GetMinutes() - d.GetMinutes();
	}
	bool operator==(const DatumVrijeme& obj) {
		return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina && *_sati == *obj._sati && *_minuti == *obj._minuti;
	}
	DatumVrijeme& operator=(const DatumVrijeme& obj) {
		if (this!=&obj)
		{
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
			*_sati = *obj._sati;
			*_minuti = *obj._minuti;
		}
		return *this;
	}
};

class Predmet {
	char* _naziv;
	int _ocjena;
	string _napomena;
public:
	Predmet(const char* naziv = "", int ocjena = 0, string napomena = "") {
		_naziv = Alociraj(naziv);
		_ocjena = ocjena;
		_napomena = napomena;
	}
	Predmet(const Predmet& obj)
	{
		_naziv = Alociraj(obj._naziv);
		_ocjena = obj._ocjena;
		_napomena = obj._napomena;
	}
	~Predmet() {
		delete[] _naziv; _naziv = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Predmet& obj) {
		COUT << obj._naziv << " (" << obj._ocjena << ") " << obj._napomena << endl;
		return COUT;
	}
	string GetNapomena() { return _napomena; }
	char* GetNaziv() const { return _naziv; }
	int GetOcjena() { return _ocjena; }

	void DodajNapomenu(string napomena) {
		_napomena += " " + napomena;
	}
	bool operator==(const Predmet& obj) { return strcmp(_naziv, obj._naziv) == 0; }
	Predmet& operator=(const Predmet& obj)
	{
		if (this!=&obj)
		{
			delete[]_naziv;
			_naziv = Alociraj(obj._naziv);
			_ocjena = obj._ocjena;
			_napomena = obj._napomena;
		}
		return *this;
	}
};

class Uspjeh {
	eRazred* _razred;
	//formalni argument DatumVrijeme se odnosi na vrijeme evidentiranja polozenog predmeta
	Kolekcija<Predmet, DatumVrijeme> _predmeti;
public:
	Uspjeh(eRazred razred) {
		_razred = new eRazred(razred);
	}
	Uspjeh(const Uspjeh& obj) :_predmeti(obj._predmeti)
	{
		_razred = new eRazred(*obj._razred);
	}
	~Uspjeh() { delete _razred; _razred = nullptr; }

	Kolekcija<Predmet, DatumVrijeme>* GetPredmeti() { return &_predmeti; }
	eRazred* GetERazred() { return _razred; }
	friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
		COUT << *obj._razred << " " << obj._predmeti << endl;
		return COUT;
	}
	void AddPredmet(Predmet& p, DatumVrijeme& d) {
		_predmeti.AddElement(p, d);
	}
	float GetProsjek()const {
		if (_predmeti.getTrenutno() == 0) return 0;
		float sum = 0.0f;
		for (size_t i = 0; i < _predmeti.getTrenutno(); i++)
			sum += _predmeti.getElement1(i).GetOcjena();
		return float(sum /= _predmeti.getTrenutno());
	}
};

class Kandidat {
	char* _imePrezime;
	string _emailAdresa;
	string _brojTelefona;
	vector<Uspjeh> _uspjeh;
public:
	Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
		_imePrezime = Alociraj(imePrezime);
		_emailAdresa = ValidirajMail(emailAdresa)?emailAdresa:"notSet@fit.ba";
		_brojTelefona = brojTelefona;
	}
	~Kandidat() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
		COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
		return COUT;
	}
	vector<Uspjeh>* GetUspjeh() { return &_uspjeh; }
	string GetEmail() { return _emailAdresa; }
	string GetBrojTelefona() { return _brojTelefona; }
	char* GetImePrezime() { return _imePrezime; }
	
	void SendMail(string mail,eRazred raz,const char * ime) {
		m.lock();
		cout << crt << "FROM:info@edu.fit.ba" << "\nTO:" << mail << "\nPostovani " << ime << ",evidentirali smo uspjeh za " << to_string(raz) <<
			" razred." <<"\nPozdrav," << "\nFIT Team." << endl;
		m.unlock();
	}
	void SendSms(float prosjek,eRazred raz) {
		m.lock();
		cout << "Svaka cast za uspjeh " << prosjek << " u " << to_string(raz) << " razredu" << endl;
		m.unlock();
	}
	bool CanAdd(eRazred raz, Predmet& p, DatumVrijeme& d) {
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			if(*i->GetERazred() == raz)
				for (size_t j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
				{
					if (i->GetPredmeti()->getElement1(j) == p) return false;
					if (d - i->GetPredmeti()->getElement2(j) < 5) return false;
				}
		return true;

	}
	bool AddPredmet(eRazred raz,Predmet& p,DatumVrijeme& d) {
		if (!CanAdd(raz, p, d)) return false;
		for (size_t i = 0; i < _uspjeh.size(); i++)
			if (*_uspjeh[i].GetERazred() == raz) {
				_uspjeh[i].AddPredmet(p, d);
				thread t(&Kandidat::SendMail, this, _emailAdresa, raz, _imePrezime);
				t.join();
				if (_uspjeh[i].GetProsjek() > 4.5)
				{
					thread t_sms(&Kandidat::SendSms, this, _uspjeh[i].GetProsjek(), raz);
					t_sms.join();
				}
			}
		Uspjeh uspjeh(raz);
		uspjeh.AddPredmet(p, d);
		thread tr(&Kandidat::SendMail, this, _emailAdresa, *uspjeh.GetERazred(), GetImePrezime());
		tr.join();
		if (uspjeh.GetProsjek() > 4.5)
		{
			thread p(&Kandidat::SendSms, this, uspjeh.GetProsjek(), raz);
			p.join();
		}
		_uspjeh.push_back(uspjeh);
		return true;
	}
	int BrojPonavljanjaRijeci(string word)
	{
		int brojPonavljanja = 0;
		for (size_t i = 0; i < _uspjeh.size(); i++)
			for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
			{
				regex r("(\\b" + word + "\\b|\\B" + word + "\\B)");
				string napomena = _uspjeh[i].GetPredmeti()->getElement1(j).GetNapomena();
				auto start = sregex_iterator(napomena.begin(), napomena.end(), r);
				auto end = sregex_iterator();
				brojPonavljanja += distance(start, end);
			}
		return brojPonavljanja;
	}
	vector<Predmet> operator()(DatumVrijeme d1,DatumVrijeme d2) {
		vector<Predmet> p;
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			for (size_t j = 0; j < i->GetPredmeti()->getTrenutno(); j++)
				if (i->GetPredmeti()->getElement2(j) > d1 && i->GetPredmeti()->getElement2(j) < d2)
					p.push_back(i->GetPredmeti()->getElement1(j));
		return p;
	}
	Uspjeh* operator[](eRazred r)
	{
		for (vector<Uspjeh>::iterator i = _uspjeh.begin(); i != _uspjeh.end(); i++)
			if (*i->GetERazred() == r)
				return i._Ptr;
		return nullptr;
	}
};


void main() {
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR AE BITI OZNACENO KAO "RE"
	3. SPA�AVAJTE PROJEKAT KAKO BI SE SPRIJEEILO GUBLJENJE URA?ENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKO?ER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIENI ONIMA KOJI SU KORI�TENI U TESTNOM CODE-U, OSIM U SLUEAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOANE FUNKCIJE MO�ETE IMENOVATI I DODAVATI PO �ELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAEENO.
	7. IMATE POTPUNU SLOBODU DA U MAIN FUNKCIJI, ZA POTREBE TESTIRANJA, DODAJETE VISE POZIVA ILI SALJETE DRUGE VRIJEDNOSTI PARAMETARA
	****************************************************************************/

	DatumVrijeme temp,
		datum19062019_1015(19, 6, 2019, 10, 15),
		datum20062019_1115(20, 6, 2019, 11, 15),
		datum30062019_1215(30, 6, 2019, 12, 15),
		datum05072019_1231(5, 7, 2019, 12, 31);

	const int kolekcijaTestSize = 9;
	Kolekcija<int, int> kolekcija1(false);
	for (size_t i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i + 1, 20 - i);
	
	try {
		//ukoliko nije dozvoljeno dupliranje elemenata, metoda AddElement baca izuzetak
		kolekcija1.AddElement(6, 15);
	}
	catch (exception& err) {
		cout << err.what() << endl;
	}
	cout << kolekcija1 << endl;
	
	//na osnovu vrijednosti parametra sortira clanove kolekcije u rastucem redoslijedu 
	kolekcija1.SortirajRastuci(SortirajPo::T2);
	cout << kolekcija1 << endl;
	

	Kolekcija<int, int> kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	//
	Kolekcija<int, int> kolekcija3;
	kolekcija3 = kolekcija1;
	cout << kolekcija3 << crt;
	
	//napomena se moze dodati i prilikom kreiranja objekta
	Predmet Matematika("Matematika", 5, "Ucesce na takmicenju"),
		Fizika("Fizika", 5),
		Hemija("Hemija", 2),
		Engleski("Engleski", 5);
	Fizika.DodajNapomenu("Pohvala za ostvareni uspjeh");
	cout << Matematika << endl;
	
	
	//email adresa mora biti u formatu: text@outlook.com ili text@edu.fit.ba
	//u slucaju da email adresa nije validna, postaviti je na defaultnu: notSet@edu.fit.ba
	//za provjeru koristiti regex
	
	
	Kandidat jasmin("Jasmin Azemovic", "jasmin@outlook.com", "033 281 172"); 
	Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
	Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");
	


	//uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
	//tom prilikom onemoguciti:
	//- dodavanje istoimenih predmeta na nivou jednog razreda,
	//- dodavanje vise predmeta u kratkom vremenskom periodu (na nivou jednog razreda, razmak izmedju dodavanja pojedinih predmeta mora biti najmanje 5 minuta).
	//- razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
	//- Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
	//
	if (jasmin.AddPredmet(DRUGI, Fizika, datum20062019_1115))
		cout <<  "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(DRUGI, Hemija, datum30062019_1215))
		cout << "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Engleski, datum19062019_1015))
		cout <<  "Predmet uspjesno dodan!" << crt;
	if (jasmin.AddPredmet(PRVI, Matematika, datum20062019_1115))
		cout <<  "Predmet uspjesno dodan!" << crt;
	//ne treba dodati Matematiku jer je vec dodana u prvom razredu
	if (jasmin.AddPredmet(PRVI, Matematika, datum05072019_1231))
		cout << "Predmet uspjesno dodan!" << crt;
	//////ne treba dodati Fiziku jer nije proslo 5 minuta od dodavanja posljednjeg predmeta
	if (jasmin.AddPredmet(PRVI, Fizika, datum20062019_1115))
		cout << "Predmet uspjesno dodan!" << crt;
	//
	/*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
	FROM:info@edu.fit.ba
	TO: emailKorisnika
	Postovani ime i prezime, evidentirali ste uspjeh za X razred.
	Pozdrav.
	FIT Team.
	
	ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh X.X u X razredu".
	slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.*/
	
	
	cout << "USPJEH ISPISATI KORISTECI OSTREAM_ITERATOR" << endl;
	cout << jasmin << endl;
	//vraca broj ponavljanja odredjene rijeci u napomenama, koristiti sregex_iterator
	cout << "Rijec takmicenje se pojavljuje " << jasmin.BrojPonavljanjaRijeci("takmicenju") << " puta." << endl;
	
	//vraca niz predmeta koji su evidentiranih u periodu izmedju vrijednosti proslijedjenih parametara
	vector<Predmet> jasminUspjeh = jasmin(DatumVrijeme(18, 06, 2019, 10, 15), DatumVrijeme(21, 06, 2019, 10, 10));
	for (size_t i = 0; i < jasminUspjeh.size(); i++)
		cout << jasminUspjeh[i] << endl;

	Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
	if (uspjeh_Irazred != nullptr)
		cout << *uspjeh_Irazred << endl;
	 
	system("pause>0");
}