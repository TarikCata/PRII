#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <iterator>
#include <exception>
#include <thread>
#include <mutex>


using namespace std;
mutex m;
const char* crt = "\n---------------------------------------\n";
//1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
//NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA(NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
//BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
bool Validanformat(string s)
{
	return regex_match(s, regex("([A-Za-z]{5,15})(\\.)(doc|txt|pdf|html)"));
}
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
	DatumVrijeme(const DatumVrijeme& obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		_sati = new int(*obj._sati);
		_minuti = new int(*obj._minuti);

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
	~DatumVrijeme() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;

	}
	friend ostream& operator<< (ostream& COUT,const DatumVrijeme& obj) {
		COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << " " << *obj._sati << ":" << *obj._minuti;
		return COUT;
	}
	bool operator==(const DatumVrijeme& obj) {
		return *_dan == *obj._dan && *_mjesec == *obj._mjesec && *_godina == *obj._godina && *_sati == *obj._sati && *_minuti == *obj._minuti;
	}
};

template<class T1, class T2 = int>
class FITKolekcija {
	T1* _elementi1;
	T2* _elementi2;
	int _trenutno;
	void Delete() { delete[]_elementi1; delete[]_elementi2; }
public:
	FITKolekcija() {
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	FITKolekcija(const FITKolekcija& obj)
	{
		_trenutno = obj._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];

		}
	}
	FITKolekcija& operator=(const FITKolekcija& obj)
	{
		if (this!=&obj)
		{
			_trenutno = obj._trenutno;
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
	~FITKolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi2 = nullptr;
	}
	T1* GetT1() const { return _elementi1; }
	T2* GetT2()const  { return _elementi2; }
	int GetTrenutno() const { return _trenutno; }
	void Dodaj(const T1& el1, const T2& el2) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		Delete();
		_elementi1 = temp1; temp1 = nullptr;
		_elementi2 = temp2; temp2 = nullptr;
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;

	}
	void Sortiraj() {
		bool promjena = true;
		while (promjena)
		{
			promjena = false;
			for (size_t i = 0; i < _trenutno - 1; i++)
			{
				if (_elementi1[i] > _elementi1[i + 1]) {
					T1 temp1 = _elementi1[i];
					T2 temp2 = _elementi2[i];
					_elementi1[i] = _elementi1[i + 1];
					_elementi2[i] = _elementi2[i + 1];
					_elementi1[i + 1] = temp1;
					_elementi2[i + 1] = temp2;
					promjena = true;
				}
			}
		}
	}
	void DodajNaLokaciju(const T1& el1, const T2& el2,int lokacija) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];
		temp1[lokacija] = el1;
		temp2[lokacija] = el2;
		for (size_t i = 0; i < _trenutno+1; i++)
		{
			if (i<lokacija)
			{
				temp1[i] = _elementi1[i];
				temp2[i] = _elementi2[i];
			}
			else if (i > lokacija)
			{
				temp1[i] = _elementi1[i-1];
				temp2[i] = _elementi2[i-1];
			}
		}
		Delete();
		_elementi1 = temp1; temp1 = nullptr;
		_elementi2 = temp2; temp2 = nullptr;
		_elementi1[_trenutno] = el1;
		_elementi2[_trenutno] = el2;
		_trenutno++;
	}
	FITKolekcija<T1, T2>* GetJedinstveni() {
		FITKolekcija<T1, T1>* nova = new FITKolekcija<T1, T1>;
		bool dodaj = true;
		for (size_t i = 0; i < _trenutno; i++)
		{
			dodaj = true;
			for (size_t j = 0; j < nova->GetTrenutno(); j++)
			{
				if (nova->GetT1()[j] == _elementi1[i] && nova->GetT2()[j] == _elementi2[i])
					dodaj = false;
			}
			if (dodaj)
				nova->Dodaj(_elementi1[i], _elementi2[i]);
		}
		return nova;
	}
	friend ostream& operator<< (ostream& COUT,const FITKolekcija& obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj._elementi1[i] << " " << obj._elementi2[i] << endl;
		return COUT;
	}
};

enum vrstaDokumenta { PDF, DOC, TXT, HTML };
char* Alocira(const char* t) {
	int vel = strlen(t) + 1;
	char* n = new char[vel];
	strcpy_s(n, vel, t);
	return n;
}
class Dokument {
	vrstaDokumenta _vrsta;
	string _naziv;
	string _sadrzaj;
	int _brojStranica;
public:
	Dokument() { _brojStranica = 0; }
	Dokument(vrstaDokumenta vrsta, string naziv) {
		_naziv = naziv; _vrsta = vrsta; _brojStranica = 0;
	}
	Dokument(const Dokument& d)
	{
		_vrsta = d._vrsta;
		_naziv = d._naziv;
		_sadrzaj = d._sadrzaj;
		_brojStranica = d._brojStranica;
	}
	Dokument& operator=(const Dokument& d) {
		if (this!=&d)
		{
			_vrsta = d._vrsta;
			_naziv = d._naziv;
			_sadrzaj = d._sadrzaj;
			_brojStranica = d._brojStranica;
		}
		return *this;
	}
	string GetNaziv() const { return _naziv; };
	string GetSadrzaj() const  { return _sadrzaj; };
	vrstaDokumenta GetVrsta() const { return _vrsta; };
	void UvecajBrojStranica()  { _brojStranica++; }
	int GetBrojStranica()  { return _brojStranica; }
	friend ostream& operator<<(ostream& COUT,const Dokument& obj) {
		COUT << obj._naziv << "." << obj._vrsta << " (" << obj._brojStranica << ")\n" << obj._sadrzaj << endl;
		return COUT;
	}
	void DodajSadrzaj(string s) {
		_sadrzaj += s;
		_brojStranica = _sadrzaj.length() / (float)30 + 0.9;
	}
};
class Uredjaj {
protected:
	char* _proizvodjac;
	char* _model;
public:
	Uredjaj(const char* proizvodjac,const char* model) {
		int vel = strlen(proizvodjac) + 1;
		_proizvodjac = new char[vel];
		strcpy_s(_proizvodjac, vel, proizvodjac);
		vel = strlen(model) + 1;
		_model = new char[vel];
		strcpy_s(_model, vel, model);
	}
	Uredjaj(const Uredjaj& obj)
	{
		_proizvodjac = Alocira(obj._proizvodjac);
		_model = Alocira(obj._model);
	}
	~Uredjaj() {
		delete[] _proizvodjac; _proizvodjac = nullptr;
		delete[] _model; _model = nullptr;
	}
	friend ostream& operator<<(ostream& COUT,const Uredjaj& obj) {
		COUT << obj._proizvodjac << "." << obj._model << endl;
		return COUT;
	}
};

void Ispis(string txt) {
	lock_guard<mutex> guard(m);
	this_thread::sleep_for(chrono::seconds(1));
	cout << "Printam " << txt << "\n";
}
class Printer : public Uredjaj {
	FITKolekcija<DatumVrijeme, Dokument> _printaniDokumenti;
	vector<string> _zabranjeneRijeci;
public:
	Printer(const char* proizvodjac, const char* model) : Uredjaj(proizvodjac, model) {}
	Printer(const Printer& obj) : Uredjaj(obj), _printaniDokumenti(obj._printaniDokumenti), _zabranjeneRijeci(obj._zabranjeneRijeci)
	{

	}

	FITKolekcija<DatumVrijeme, Dokument>& GetPrintaniDokumenti() { return _printaniDokumenti; };
	vector<string>& GetZabranjeneRijeci() { return _zabranjeneRijeci; };
	bool DodajZabranjenuRijec(string s) {
		for (auto zabranjena : _zabranjeneRijeci)
			if (zabranjena == s)
				return false;
		_zabranjeneRijeci.push_back(s);
		return true;
	}

	void Printaj(DatumVrijeme& d,Dokument& doc) {
		_printaniDokumenti.Dodaj(d, doc);
		if (!Validanformat(doc.GetNaziv().c_str()))
			throw exception("Naziv dokumenta nije u ispravnom formatu");
		for (size_t i = 0; i < _zabranjeneRijeci.size(); i++)
			if (doc.GetSadrzaj().find(_zabranjeneRijeci[i]) != string::npos)
				throw exception("U dokumentu postoje zabranjene rijeci!");
		thread t(Ispis, doc.GetSadrzaj());
		t.detach();
	}
	float GetProsjecanBrojStranicaPoDatumu(DatumVrijeme& datum) {
		if (_printaniDokumenti.GetTrenutno() == 0) return 0;
		float ukupno = 0.0f;
		for (size_t i = 0; i < _printaniDokumenti.GetTrenutno(); i++)
			if (_printaniDokumenti.GetT1()[i] == datum)
			{
				bool check = true;
				if (!Validanformat(_printaniDokumenti.GetT2()[i].GetNaziv()))
					check = false;
				for (auto rijec : _zabranjeneRijeci)
					if (rijec == _printaniDokumenti.GetT2()[i].GetSadrzaj())
					{
						check = false;
						break;
					}
				ukupno += _printaniDokumenti.GetT2()[i].GetBrojStranica();
			}
		return float(ukupno /= _printaniDokumenti.GetTrenutno());
	}
	string GetTopZabranjenuRijec() {
		int brojac = 0, trenuto = 0;
		auto it = _zabranjeneRijeci.begin();
		for (auto i : _zabranjeneRijeci)
		{
			trenuto = 0;
			for (size_t j = 0; j < _printaniDokumenti.GetTrenutno(); j++)
				if (_printaniDokumenti.GetT2()[j].GetSadrzaj().find(i) != string::npos)
					trenuto++;
			if (trenuto > brojac)
			{
				brojac = trenuto;
				*it = i;
			}
		}
		return *it;
	}
	friend ostream& operator<<(ostream& cout, Printer& p) {
		cout << static_cast<Uredjaj&>(p) << "\n";
		cout << "Printani dokumenti:\n";
		for (size_t i = 0; i < p._printaniDokumenti.GetTrenutno(); i++)
			cout << p._printaniDokumenti.GetT2()[i].GetNaziv() << endl;
		cout << "Zabranjene rijeci:\n";
		for (vector<string>::iterator i = p._zabranjeneRijeci.begin(); i != p._zabranjeneRijeci.end(); i++)
			cout << *i << endl;
		return cout;
	}
};

void main()
{
	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
	3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT
	5. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
	6. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNAČENO.
	****************************************************************************/

#pragma region TestiranjeDatumVrijeme
	DatumVrijeme danas(1, 2, 2017, 10, 15);
	DatumVrijeme sutra(danas);
	DatumVrijeme prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region FITKolekcija
	int v6 = 6, v13 = 13, v32 = 32, v63 = 63, v98 = 98, v109 = 109, v196 = 196;
	
	FITKolekcija<int, int> brojevi;
	brojevi.Dodaj(v196, v6);
	brojevi.Dodaj(v13, v32);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v63, v13);
	brojevi.Dodaj(v98, v196);
	brojevi.Dodaj(v196, v6);
	//
	cout << brojevi << crt;
	//SORTIRANJE ČLANOVA KOLEKCIJE SE VRŠI U RASTUĆEM REDOSLIJEDU NA OSNOVU VRIJEDNOSTI ELEMENTA TIPA T1
	brojevi.Sortiraj();
	cout << brojevi << crt;
	//BROJ 2 SE ODNOSI NA LOKACIJU/INDEKS UNUTAR LISTE NA KOJI JE POTREBNO DODATI NOVE ELEMENTE
	brojevi.DodajNaLokaciju(v109, v6, 2);
	cout << brojevi << crt;
	brojevi.Sortiraj();
	cout << brojevi << crt;
	
	/*METODA GetJedinstveni VRAĆA LISTU JEDINSTVENIH ELEMENATA TJ. ELEMENATA KOJI NE SADRŽE DUPLIKATE (POJAM DUPLIKAT SE ODNOSI NA ISTE VRIJEDNOSTI ELEMENATA T1 I T2). ELEMENTI KOJI SE DUPLIRAJU SE U OVOJ LISTI TREBAJU POJAVITI SAMO JEDNOM.*/
	FITKolekcija<int, int>* jedinstveni = brojevi.GetJedinstveni();
	cout << *jedinstveni << crt;
	*jedinstveni = brojevi;
	cout << *jedinstveni << crt;
	
	Dokument ispitPRIII(DOC, "ispitPRIII.doc");
	//BROJ STRANICA DOKUMENTA SE AUTOMATSKI ODREĐUJE PRILIKOM DODAVANJA SADRŽAJA. ZA POTREBE ISPITA PRETPOSTAVLJAMO DA NA JEDNU STRANICU MOŽE STATI 30 ZNAKOVA UKLJUČUJUĆI I RAZMAKE
	ispitPRIII.DodajSadrzaj("NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO RE");
	cout << "Broj stranica -> " << ispitPRIII.GetBrojStranica() << endl;
	Dokument ispitBaze(DOC, "ispitBaze.doc");
	ispitBaze.DodajSadrzaj("PROGRAMSKI CODE SE TAKOĐER NALAZI U FAJLU CODE.TXT");
	cout << ispitBaze << endl;//ISPISUJE SVE DOSTUPNE PODATKE O DOKUMENTU
	////
	Printer hp3200("HP", "3200");
	//PRINTER NEĆE DOZVOLITI PRINTANJE DOKUMENATA U ČIJEM SADRŽAJU SE NALAZI NEKA OD ZABRANJENIH RIJEČI
	hp3200.DodajZabranjenuRijec("RE");// :)
	hp3200.DodajZabranjenuRijec("RAT");
	hp3200.DodajZabranjenuRijec("UBITI");
	hp3200.DodajZabranjenuRijec("RE");// ONEMOGUĆITI PONAVLJANJE ZABRANJENIH RIJEČI, KORISTITI ITERATORE
	hp3200.DodajZabranjenuRijec("MRZITI");
	try
	{
		/* 
		DA BI PRINTER ISPRINTAO NEKI DOKUMENT MORAJU BITI ZADOVOLJENA SLJEDEĆA PRAVILA:
		1. NAZIV DOKUMENTA MORA BITI U SLJEDEĆEM FORMATU npr: ispitPRIII.doc
		NAZIV DOKUMENTA MOŽE SADRŽAVATI SAMO SLOVA (NAJMANJE 5, NAJVIŠE 15), A EKSTENZIJA MOŽE
		BITI SAMO NEKA OD DOZVOLJENIH VRSTOMDOKUMENTA
		2. SADRŽAJ DOKUMENTA U SEBI NE SMIJE POSJEDOVATI NITI JEDNU ZABRANJENU RIJEČ
		UKOLIKO NEKI OD NAVEDENIH USLOVA NIJE ZADOVOLJEN FUNKCIJA TREBA DA BACI EXCEPTION SA
		ODGOVARAJUĆOM PORUKOM, ALI ĆE DOKUMENT BITI POHRANJEN U KOLEKCIJU _printaniDokumenti.
		UKOLIKO DOKUMENT ISPUNJAVA SVE USLOVE ZA PRINTANJE POTREBNO JE NA KONZOLU ISPISATI
		SADRŽAJ DOKUMENTA KOJI SE PRINTA
	
		*/
		hp3200.Printaj(danas, ispitPRIII);
		hp3200.Printaj(danas, ispitBaze);
	
		/*
		IMPLEMENTIRATI PRINTANJE U ZASEBNIM NITIMA UZ KORIŠTENJE sleep_for FUNKCIJE
		VODITI RAČUNA O DIJELJENJU ZAJEDNIČKIH RESURSA
		*/
	
	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}
	
	//KOD POREĐENJA DATUMA PRINTANJA NIJE POTREBNO POREDITI MINUTE, SAMO DATUM I SATE
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp3200.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp3200.GetTopZabranjenuRijec() << crt;
	
	Printer hp4000(hp3200);
	cout << "Prosjecan broj printanih stranica za " << danas << " je -> " << hp4000.GetProsjecanBrojStranicaPoDatumu(danas) << crt;
	cout << "Najcesce koristena zabranjena rijec je -> " << hp4000.GetTopZabranjenuRijec() << crt;
	//hp4000.UkloniDokumente();//UKLANJA SVE DOKUMENTE KOJI NISU ZADOVOLJILI USLOVE ZA PRINTANJE
	cout << hp4000 << crt;

#pragma endregion
	system("pause");
}