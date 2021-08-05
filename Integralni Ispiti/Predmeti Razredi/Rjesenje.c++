#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<iterator>

using namespace std;
enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char* crt = "\n---------------------------------\n";
const char* ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char* ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };

bool ProvjeriValidnostBrojaTelefona(string telefon) {
	return regex_match(telefon, regex("(\\+)([0-9]{3})(\\()([0-9]{2})(\\))([-])([0-9]{3})([-])([0-9]{3})"));
}
template<class T1, class T2>
class Kolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	Kolekcija(const Kolekcija& k) {
		_trenutno = k._trenutno;
		_elementi1 = new T1[k._trenutno];
		_elementi2 = new T2[k._trenutno];
		for (size_t i = 0; i < k._trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
	}
	Kolekcija& operator= (const Kolekcija& k) {
		if (this != &k) {
			delete[] _elementi1;
			delete[] _elementi2;
			_trenutno = k._trenutno;
			_elementi1 = new T1[k._trenutno];
			_elementi2 = new T2[k._trenutno];
			for (size_t i = 0; i < k._trenutno; i++)
			{
				_elementi1[i] = k._elementi1[i];
				_elementi2[i] = k._elementi2[i];
			}
		}
		return *this;
	}
	void AddElement(const T1& el1,const T2& el2) {
		T1* t1 = new T1[_trenutno + 1];
		T2* t2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			t1[i] = _elementi1[i];
			t2[i] = _elementi2[i];
		}
		delete[]_elementi1; delete[]_elementi2;
		_elementi1 = t1;
		_elementi2 = t2;
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;
	}
	void RemoveElement(int lokacija) {
		for (size_t i = lokacija; i < _trenutno - 1; i++)
		{
			_elementi1[i] = _elementi1[i + 1];
			_elementi2[i] = _elementi2[i + 1];
		}
		_trenutno--;
	}
	T1& GetElement1(int lokacija) const { return _elementi1[lokacija]; }
	T2& GetElement2(int lokacija) const { return _elementi2[lokacija]; }
	int GetTrenutno() const { return _trenutno; }

	friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
		for (size_t i = 0; i < obj.GetTrenutno(); i++)
			cout << obj.GetElement1(i) << "   " << obj.GetElement2(i) << endl;
		return COUT;
	}
	~Kolekcija()
	{
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
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
	Datum& operator=(const Datum& obj) {
		if (this != &obj)
		{
			*_dan = *obj._dan;
			*_mjesec = *obj._mjesec;
			*_godina = *obj._godina;
		}
		return *this;
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}

	bool operator==(const Datum& obj) { return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina; }
	friend ostream& operator<< (ostream& COUT, const Datum& obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
};
char* Alociraj(const char* t)
{
	if (t == nullptr)return nullptr;
	int vel = strlen(t) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, t);
	return novi;
}

class Osoba {
protected:
	char* _imePrezime;
	Datum* _datumRodjenja;
	string _brojTelefona;
public:
	Osoba(const char* imePrezime, Datum datum) {
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";

	}
	Osoba(const Osoba& obj) :_brojTelefona(obj._brojTelefona) {
		_imePrezime = new char[strlen(obj._imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	Osoba& operator=(const Osoba& o) {
		if (this != &o) {
			delete[] _imePrezime;
			_brojTelefona = o._brojTelefona;
			_imePrezime = new char[strlen(o._imePrezime) + 1];
			strcpy_s(_imePrezime, strlen(o._imePrezime) + 1, o._imePrezime);
			*_datumRodjenja = *o._datumRodjenja;
		}
		return *this;
	}
	virtual ~Osoba() { delete[]_imePrezime; _imePrezime = nullptr; delete _datumRodjenja; _datumRodjenja = nullptr; }
	void Info() { cout << endl; }
	bool setBrojTelefona(string brojTelefona) {
		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}
	bool operator==(const Osoba& obj) { 
		if (strcmp(_imePrezime, obj._imePrezime) == 0)
			if (_brojTelefona == obj._brojTelefona)
				if (*_datumRodjenja == *obj._datumRodjenja)
					return true;
		return false;
	}
};



class Nastavnik : public Osoba {
	Kolekcija<Predmeti, Razredi>* _predmetiRazredi;
public:
	Nastavnik(const char* ime_prezime, Datum d) :Osoba(ime_prezime, d), _predmetiRazredi(new Kolekcija<Predmeti, Razredi>) {}
	Nastavnik(const Nastavnik& n) :Osoba(n), _predmetiRazredi(new Kolekcija<Predmeti, Razredi>(*n._predmetiRazredi)) {}
	Nastavnik& operator=(const Nastavnik& obj) {
		if (this != &obj)
		{
			(Osoba&)(*this) = obj;
			*_predmetiRazredi = *obj._predmetiRazredi;
		}
		return *this;
	}
	///*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	~Nastavnik() {
		delete _predmetiRazredi; _predmetiRazredi = nullptr;
	}
	bool AddPredmetRazred(Predmeti p, Razredi r) {
		int c = 0;
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == p && _predmetiRazredi->GetElement2(i) == r)
				return false;
			if (_predmetiRazredi->GetElement2(i) == r)
				c++;
		}
		if (c == 2)
			return false;
		_predmetiRazredi->AddElement(p, r);
		return true;
	}
	bool RemovePredmetRazred(Predmeti p) {
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			if (_predmetiRazredi[i].GetElement1(i) == p)
				_predmetiRazredi->RemoveElement(i);
		return true;
	}
	void Info() { cout << endl; }
	Kolekcija<Predmeti, Razredi>& getPredmetiRazredi() { return *_predmetiRazredi; }
	bool operator==(const Nastavnik& obj) {
		if( static_cast<Osoba>(obj) == static_cast<Osoba>(*this))
			for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
			{
				if (_predmetiRazredi->GetElement1(i) == obj._predmetiRazredi->GetElement1(i)
					&& _predmetiRazredi->GetElement2(i) == obj._predmetiRazredi->GetElement2(i))
					return true;
			}
		return false;
	}
};
class Ucenik : public Osoba {
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik*> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
	bool ProvjeriImaLiNastavnikRazred(Nastavnik& n)
	{
		for (size_t i = 0; i < n.getPredmetiRazredi().GetTrenutno(); i++)
			if (n.getPredmetiRazredi().GetElement2(i) == _razred)
				return true;
		return false;
	}
	bool ZabranaDodavanjeIstogNastavnika(Nastavnik& n)
	{
		for (size_t i = 0; i < _nastavnici.size(); i++)
			if (*_nastavnici[i] == n)
				return false;
		return true;
	}
	bool PostojiLiNastavnikZaOcjenu(Predmeti p)
	{
		for (size_t i = 0; i < _nastavnici.size(); i++)
			if (_nastavnici[i]->getPredmetiRazredi().GetElement1(i) != p)
				return false;
		return true;
	}
public:
	Ucenik(const char* imePrezime, Datum datum, int brojUdnevniku, Razredi r) : Osoba(imePrezime, datum)
	{
		_brojUDnevniku = brojUdnevniku;
		_razred = r;
	}
	Ucenik(const Ucenik& ob) : Osoba(ob) 
	{

		_brojUDnevniku = ob._brojUDnevniku;
		_razred = ob._razred;
		for (size_t i = 0; i < _nastavnici.size(); i++)
			_nastavnici.push_back(new Nastavnik(*ob._nastavnici[i]));
		_predmetiOcjene = ob._predmetiOcjene;
	
	}
	bool AddNastavnik(Nastavnik& n) {
		if (!ProvjeriImaLiNastavnikRazred(n) || !ZabranaDodavanjeIstogNastavnika(n))
			return false;
		_nastavnici.push_back(new Nastavnik(n));
		return true;	
	}
	bool AddPredmetOcjenu(Predmeti p, int ocjena) {
		bool provjera = false;
		for (size_t i = 0; i < _nastavnici.size(); i++)
			if (_nastavnici[i]->getPredmetiRazredi().GetElement1(i) == p)
				provjera = true;
		if (!provjera) return false;
		_predmetiOcjene.AddElement(p, ocjena);
		return true;
	}
	~Ucenik() {
		for (size_t i = 0; i < _nastavnici.size(); i++)
		{
			delete _nastavnici[i];
			_nastavnici[i] = nullptr;
		}
	}
	void Info() { cout << endl; }
	vector<Nastavnik*>& getNastavnici() { return _nastavnici; }
	Kolekcija<Predmeti, int>& getPredmetiOcjene() { return _predmetiOcjene; }
	friend ostream& operator<<(ostream& cout, const Ucenik& obj) {
		cout << obj._imePrezime << "\n" << *obj._datumRodjenja << "\n" << obj._brojTelefona << "\n" << obj._brojUDnevniku;
		return cout;
	}
	float GetProsjekByNastavnik(const char* ime)
	{
		float sum = 0.0f;
		int cnt = 0;
		Nastavnik nastavnik(ime, Datum());
		for (auto n : _nastavnici)
		{
			if (*n == nastavnik)
				for (size_t i = 0; i < _predmetiOcjene.GetTrenutno(); i++)
				{
					for (size_t j = 0; j < n->getPredmetiRazredi().GetTrenutno(); j++)
					{
						if (_predmetiOcjene.GetElement1(i) == _nastavnici[i]->getPredmetiRazredi().GetElement1(j))
						{
							sum += _predmetiOcjene.GetElement2(i);
							cnt++;
						}
					}
				}
		}
		return float(sum /= cnt);
	}
};


void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U.
	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int> kolekcija1;
	int brojElemenata = 15;
	for (size_t i = 0; i < brojElemenata; i++)
		kolekcija1.AddElement(i, i);

	kolekcija1.RemoveElement(0);//uklanja element na osnovu lokacije
	cout << kolekcija1 << endl;

	cout << kolekcija1.GetElement1(0) << " " << kolekcija1.GetElement2(0) << endl;
	cout << kolekcija1 << endl;
	Kolekcija<int, int> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));
	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/
	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;
	
	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;
	
	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;
	
	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;
	
	if (adel.RemovePredmetRazred(Historija))
		cout << "Predmet uklonjen!" << endl;
	
	Nastavnik goran(adel);
	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;
	
	Kolekcija<Predmeti, Razredi>& predmetiRazredi = jasmin.getPredmetiRazredi();
	
	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	///*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET*/
	///*ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU */
	if (denis.AddNastavnik(jasmin))
		cout << "Nastavnik uspjesno dodan" << endl;
	///*ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA*/
	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;
	///*DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET*/
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "ocjena uspjesno dodana" << endl;

	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;
	
	vector<Nastavnik*>& nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;
	
	Kolekcija<Predmeti, int>& uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;
	
	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause");
}