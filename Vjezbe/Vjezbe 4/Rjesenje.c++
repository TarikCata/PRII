#include <iostream>
using namespace std;

//Koristene skracenice u komentarima
// dflt. = default
// user-def. = user-defined (korisnicki-definirano)
// ctor = constructor (konstruktor)
// copy ctor = copy constructor (konstruktor kopije)
// move ctor = move constructor (konstruktor premjestanja)

//Z0.1
char* AlocirajIKopiraj(const char* tekst)
{
	if (tekst == nullptr) return nullptr;
	int vel = strlen(tekst) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, tekst);
	return novi;
}

int Min(int broj1, int broj2) { return (broj1 <= broj2) ? broj1 : broj2; }
int Max(int broj1, int broj2) { return (broj1 >= broj2) ? broj1 : broj2; }

//Z0.2 :: Vratiti broj znamenki za dati broj
int IzracunajBrojZnamenki(int broj)
{
	int brojac = 0;
	while (broj > 0)
	{
		broj /= 10;
		brojac++;
	}
	return brojac;
}

//Z0.3 :: Pretvoriti (int) u (char*). Obezbijediti da je 'broj' u opsegu [INT_MIN, INT_MAX]
char* IntToStr(int broj)
{
	broj = Min(broj, INT_MAX);
	broj = Max(broj, INT_MIN);
	int vel = IzracunajBrojZnamenki(broj) + 1;
	char* tekst = new char[vel];
	_itoa_s(broj, tekst, vel, 10);
	return tekst;
}

bool PrijestupnaGodina(int godina) {
	return (((godina % 4 == 0) && (godina % 100 != 0)) ||
		(godina % 400 == 0));
}

//Z0.4 :: Vratiti broj dana za dati mjesec (Voditi racuna o prijestupnim godinama)
int GetBrojDanaUMjesecu(int mjesec, int godina)
{
	switch (mjesec) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		return PrijestupnaGodina(godina) ? 29 : 28;
	default:
		return 30;
	}
}

class Datum
{
private:
	int* _dan;
	int* _mjesec;
	int* _godina;
public:
	//Z1.1 :: Dflt. ctor 
	Datum() : _dan(nullptr), _mjesec(nullptr), _godina(nullptr) {}

	//Z1.2 :: User-def. ctor
	Datum(int d, int m, int g)
	{
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}

	//Z1.3 :: Copy ctor
	Datum(const Datum& obj)
	{
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}

	//Z1.4 :: Move ctor
	Datum(Datum&& obj)
	{
		_dan = obj._dan;
		obj._dan = nullptr;
		_mjesec = obj._mjesec;
		obj._mjesec = nullptr;
		_godina = obj._godina;
		obj._mjesec = nullptr;
	}

	//Z1.8 :: dtor
	~Datum()
	{
		delete _dan, _mjesec, _godina;
		_dan = _mjesec = _godina = nullptr;
	}


	//Z1.5 :: Operator = 
	Datum& operator =(const Datum& obj)
	{
		if (this == &obj)
			return *this;
		if (this != &obj)
		{
			_dan = new int;
			*_dan = *obj._dan;
			_mjesec = new int;
			*_mjesec = *obj._mjesec;
			_godina = new int;
			*_godina = *obj._godina;
		}
		return *this;
	}

	//Z1.6 :: Getteri
	int GetDan() const { return *_dan; }
	int GetMjesec() const { return *_mjesec; }
	int GetGodina() const { return *_godina; }

	//Z1.7 :: Setteri
	void SetDan(int dan)
	{
		if (_dan == nullptr) _dan = new int;
		*_dan = dan;
	}
	void SetMjesec(int mjesec)
	{
		if (_mjesec == nullptr) _mjesec = new int;
		*_mjesec = mjesec;
	}
	void SetGodina(int godina)
	{
		if (_godina == nullptr) _godina = new int;
		*_godina = godina;
	}


	friend ostream& operator<<(ostream& COUT, const Datum obj);
	friend bool operator == (const Datum& d1, const Datum& d2);
	friend bool operator != (const Datum& d1, const Datum& d2);
	friend Datum operator +(Datum& obj, int brojDana);
	friend bool operator > (const Datum& d1, const Datum& d2);
	friend bool operator >= (const Datum& d1, const Datum& d2);


};

//Z1.9 :: Ispisati datum
ostream& operator << (ostream& COUT, const Datum obj)
{
	COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina << endl;
	return COUT;
}

//Z1.10 :: Porediti dva datuma po vrijednostima atributa
bool operator == (const Datum& d1, const Datum& d2)
{
	return *d1._dan == *d2._dan
		&& *d1._mjesec == *d2._mjesec
		&& *d1._godina == *d2._godina;

}

bool operator != (const Datum& d1, const Datum& d2)
{
	return !(d1 == d2);
}

//Z1.11 :: Kreirati novi datum kao rezultat dodavanja varijable 'brojDana' na objekat 'obj'
Datum operator + (Datum& obj, int brojDana)
{
	int dan = *obj._dan, mjesec = *obj._mjesec, godina = *obj._godina;
	for (int i = 0; i < brojDana; i++) {
		if (dan + 1 <= GetBrojDanaUMjesecu(mjesec, godina))
			dan++;
		else {
			dan = 1;
			if (mjesec + 1 <= 12)
				mjesec++;
			else {
				mjesec = 1;
				godina++;
			}
		}
	}
	return Datum(dan, mjesec, godina);

}

//Z1.12 :: Provjeriti da li je 'd1' veci (noviji datum) od 'd2'
bool operator > (const Datum& d1, const Datum& d2)
{
	return (*d1._godina * 365 + *d1._mjesec * 30 + *d1._dan)
			> (*d2._godina * 365 + *d2._mjesec * 30 + *d2._dan);

}

bool operator >= (const Datum& d1, const Datum& d2)
{
	return (*d1._godina * 365 + *d1._mjesec * 30 + *d1._dan)
		>= (*d2._godina * 365 + *d2._mjesec * 30 + *d2._dan);

}

bool operator <(const Datum& d1, const Datum& d2)
{
	return !(d1 >= d2);
}

bool operator <=(const Datum& d1, const Datum& d2)
{
	return !(d1 > d2);
}

//Z1.13 Izracunati razliku (u danima) izmedju objekata 'd1' i 'd2'
int operator -(Datum& d1, Datum& d2)
{
	int razlika = 0;
	if (d1 == d2)
		return razlika;
	else if (d1 < d2)
		while (d1 + razlika != d2)
			razlika++;
	else
		while ((d2 + razlika) != d1)
			razlika++;
	return razlika;

}

class Clan {
	const int _clanId;
	char _korisnickoIme[30];
	char _lozinka[20];
	Datum* _datumRegistracije;
	bool* _spol;
	static int _clanIdCounter;
public:
	//Z2.0 :: Vratiti vrijednost statickog atributa _clanIdCounter
	static int GetCounter() { return Clan::_clanIdCounter; }

	//Z2.1 :: Dflt. ctor  [Postaviti _clanId na vrijednost statickog brojaca. Zatim, uvecati brojac]
	Clan() :_clanId(++_clanIdCounter), _datumRegistracije(nullptr), _spol(nullptr)
	{
		strcpy_s(_korisnickoIme, 30, "");
		strcpy_s(_lozinka, 20, "");

	}

	//Z2.2 :: User-def. ctor [Postaviti _clanId na vrijednost statickog brojaca. Zatim, uvecati brojac]
	Clan(const char* korisnickoIme, const char* lozinka, Datum datumReg, bool spol) :_clanId(++_clanIdCounter)
	{
		strcpy_s(_korisnickoIme, 30, korisnickoIme);	strcpy_s(_lozinka, 20, lozinka);
		_datumRegistracije = new Datum(datumReg.GetDan(), datumReg.GetMjesec(), datumReg.GetGodina());
		_spol = new bool; *_spol = spol;

	}

	//Z2.3 :: Copy ctor [kopirati obj._clanId u _clanId]
	Clan(const Clan& obj) :_clanId(obj._clanId)
	{
		_datumRegistracije = new Datum(*obj._datumRegistracije);
		strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);
		strcpy_s(_lozinka, 20, obj._lozinka);
		_spol = new bool(*obj._spol);
	}

	//Z2.4 :: Move ctor [kopirati obj._clanId u _clanId]
	Clan(Clan&& obj) :_clanId(obj._clanId)
	{
		_datumRegistracije = obj._datumRegistracije; obj._datumRegistracije = nullptr;
		strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);//strcpy_s(_korisnickoIme, 30, "");
		strcpy_s(_lozinka, 20, obj._lozinka);// strcpy_s(_lozinka, 20, "");
		_spol = new bool(*obj._spol);
		obj._spol = nullptr;
	}

	//Z2.5 :: operator dodjele
	Clan& operator = (const Clan& obj)
	{
		if (this == &obj) return *this;
		if (this != &obj)
		{
			_datumRegistracije = new Datum;
			*_datumRegistracije = *obj._datumRegistracije;
			strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);
			strcpy_s(_lozinka, 20, obj._lozinka);
			_spol = new bool;
			*_spol = *obj._spol;
		}
		return *this;
	}

	//Z2.6 :: Getteri
	const char* GetKorisnickoIme() const { return _korisnickoIme; }
	const char* GetLozinka() const { return _lozinka; }
	Datum GetDatumPrijave() const { return *_datumRegistracije; }
	bool GetSpol() const { return *_spol; }

	//Z2.7 :: Setteri
	void SetKorisnickoIme(const char* korisnickoIme)
	{
		strcpy_s(_korisnickoIme, 30, _korisnickoIme);
	}
	void SetLozinka(const char* lozinka)
	{
		strcpy_s(_lozinka, 20, _lozinka);
	}
	void SetDatumRegistracije(Datum datumRegistracije)
	{
		if (_datumRegistracije == nullptr)
			_datumRegistracije = new Datum;
		*_datumRegistracije = datumRegistracije;
	}
	void SetSpol(bool spol)
	{
		if (_spol == nullptr) _spol = new bool;
		*_spol = spol;
	}
	friend ostream& operator<<(ostream&, const Clan&);
	friend bool operator ==(const Clan& c1, const Clan& c2);
	//Z2.8 :: dtor
	~Clan()
	{
		delete _datumRegistracije; _datumRegistracije = nullptr;
		delete _spol; _spol = nullptr;
	}
};
int Clan::_clanIdCounter = 1; // Inicijalizacija statickog atributa

//Z2.9 :: Ispisati podatke o clanu
ostream& operator <<(ostream& COUT, const Clan& clan)
{
	COUT << "Korisnicko ime: " << clan._korisnickoIme << endl;
	COUT << "Datum registracije: " << *clan._datumRegistracije << endl;
	COUT << "Spol: " << (*clan._spol ? "Muski" : "Zenski") << endl;
	return COUT;

}

//Z2.10 :: operator == [Porediti clanove 'c1' i 'c2' po korisnickom imenu]
bool operator ==(const Clan& c1, const Clan& c2)
{
	return strcmp(c1._korisnickoIme, c2._korisnickoIme) == 0;
}

class Post {
	char* _postId;
	char* _korisnickoIme; //_korisnickoIme clana foruma koji je objavio post
	Datum _datumObjavljivanja;
	char* _sadrzaj;
	static int _postIdCounter;
public:
	//Z3.0 :: Vratiti staticki brojac _postIdCounter
	static int GetCounter() { return Post::_postIdCounter; }



	//Iskoristiti funkciju IntToStr za pretvaranje trenutne vrijednosti statickog atributa '_postIdCounter' u dinamicki niz karaktera
	//Povecati vrijednost '_postIdCounter'
	static char* GetNextPostId() { return IntToStr(Post::_postIdCounter++); }

	//Z3.1 :: Postaviti sve atribute na dflt. vrijednosti
	Post() :_postId(nullptr), _korisnickoIme(nullptr), _sadrzaj(nullptr) {}

	//Z3.2 :: Za inicijalizaciju _postId iskoristiti staticku funkciju GetNextPostId
	Post(const char* korisnickoIme, Datum datumO, const char* sadrzaj) : _datumObjavljivanja(datumO.GetDan(), datumO.GetMjesec(), datumO.GetGodina())
	{
		_postId = Post::GetNextPostId();
		_korisnickoIme = AlocirajIKopiraj(korisnickoIme);
		_sadrzaj = AlocirajIKopiraj(sadrzaj);
	}

	//Z3.3 :: Inicijalizirati '_postId' na osnovu 'obj._postId'
	Post(const Post& obj) :_datumObjavljivanja(obj._datumObjavljivanja)
	{
		_postId = AlocirajIKopiraj(obj._postId);
		_korisnickoIme = AlocirajIKopiraj(obj._korisnickoIme);
		_sadrzaj = AlocirajIKopiraj(obj._sadrzaj);

	}

	//Z3.4 :: Move ctor
	Post(Post&& obj) :_datumObjavljivanja(move(obj._datumObjavljivanja))
	{
		_postId = obj._postId;
		obj._postId = nullptr;
		_korisnickoIme = AlocirajIKopiraj(obj._korisnickoIme);
		obj._korisnickoIme = nullptr;
		_sadrzaj = AlocirajIKopiraj(obj._sadrzaj);
		obj._sadrzaj = nullptr;
	}

	//Z3.5 :: operator dodjele
	Post& operator = (const Post& obj)
	{
		if (this != &obj)
		{
			delete[]_postId;
			_postId = AlocirajIKopiraj(obj._postId);
			delete[]_korisnickoIme;
			_korisnickoIme = AlocirajIKopiraj(obj._korisnickoIme);
			_datumObjavljivanja = obj._datumObjavljivanja;
			delete[]_sadrzaj;
			_sadrzaj = AlocirajIKopiraj(obj._sadrzaj);

		}
		return *this;
	}

	//Z3.6 :: Getteri
	char* GetKorisnickoIme() const { return _korisnickoIme; }
	Datum GetDatumObjavljivanja() const { return _datumObjavljivanja; }
	char* GetSadrzaj() const { return _sadrzaj; }

	//Z3.7 :: Setteri
	//Settovati '_postId' pomocu staticke funkcije
	void SetNewPostId()
	{
		delete[]_postId;
		_postId = Post::GetNextPostId();
	}

	void SetKorisnickoIme(const char* korisnickoIme)
	{
		delete[]_korisnickoIme;
		_korisnickoIme = AlocirajIKopiraj(korisnickoIme);
	}
	void SetDatumObjavljivanja(Datum d)
	{
		_datumObjavljivanja = d;
	}
	void SetSadrzaj(const char* sadrzaj)
	{
		delete[]_sadrzaj;
		_sadrzaj = AlocirajIKopiraj(sadrzaj);
	}

	//Z3.8 :: dtor
	~Post()
	{
		delete[]_postId; _postId = nullptr;
		delete[]_korisnickoIme; _korisnickoIme = nullptr;
		delete[]_sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator <<(ostream& COUT, const Post& p);
};
int Post::_postIdCounter = 1000; // Inicijalizacija statickog atributa

//Z3.9 :: Ispisati podatke o postu
ostream& operator <<(ostream& COUT, const Post& p)
{
	COUT << "Post ID: " << p._postId << endl;
	COUT << "Korisnicko ime: " << p._korisnickoIme << endl;
	COUT << "Datum objavljivanja: " << p._datumObjavljivanja << endl;
	COUT << "Sadrzaj: " << p._sadrzaj << endl;
	return COUT;

}
const int maxBrojPostova = 100;
class Sekcija {
	char* _naziv;
	char* _kratakOpis;
	int _trenutnoPostova;
	Post* _postovi[maxBrojPostova] = { nullptr };
public:
	//Z4.1 :: Dflt. ctor
	Sekcija() :_naziv(nullptr), _kratakOpis(nullptr)
	{
		_trenutnoPostova = 0;
	}
	//Z4.2 :: User-def. ctor
	Sekcija(const char* naziv, const char* kratakOpis)
	{
		_naziv = AlocirajIKopiraj(naziv);
		_kratakOpis = AlocirajIKopiraj(kratakOpis);
		_trenutnoPostova = 0;

	}

	//Z4.3 :: Copy ctor
	Sekcija(const Sekcija& obj)
	{
		_naziv = AlocirajIKopiraj(obj._naziv);
		_kratakOpis = AlocirajIKopiraj(obj._naziv);
		_trenutnoPostova = obj._trenutnoPostova;
		for (size_t i = 0; i < _trenutnoPostova; i++)
		{
			_postovi[i] = new Post(*obj._postovi[i]);
		}
	}

	//Z4.4 :: Move ctor
	Sekcija(Sekcija&& obj)
	{
		_naziv = obj._naziv;
		_kratakOpis = obj._kratakOpis;
		_trenutnoPostova = obj._trenutnoPostova;
		for (size_t i = 0; i < _trenutnoPostova; i++)
		{
			_postovi[i] = obj._postovi[i];
			obj._postovi[i] = nullptr;
		}
		obj._naziv = obj._kratakOpis = nullptr;
		obj._trenutnoPostova = 0;

	}

	//Z4.5 :: operator dodjele
	Sekcija& operator = (const Sekcija& obj)
	{
		if (this == &obj) return *this;
		if (this != &obj)
		{
			delete[]_naziv;
			_naziv = AlocirajIKopiraj(obj._naziv);
			delete[]_kratakOpis;
			_kratakOpis = AlocirajIKopiraj(obj._kratakOpis);
			for (size_t i = 0; i < _trenutnoPostova; i++)
			{
				delete _postovi[i];
				_postovi[i] = nullptr;
			}
			_trenutnoPostova = obj._trenutnoPostova;
			for (size_t i = 0; i < _trenutnoPostova; i++)
			{
				_postovi[i] = new Post(*obj._postovi[i]);
			}
		}
		return *this;

	}

	//Z4.6 :: Getteri
	char* GetNaziv() const { return _naziv; }
	char* GetKratakOpis() const { return _kratakOpis; }
	Post GetPostAtI(int index) const { return *_postovi[index]; }

	//Z4.7 :: Setteri
	void SetNaziv(const char* naziv)
	{
		delete[]_naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}
	void SetKratakOpis(const char* kratakOpis)
	{
		delete[]_kratakOpis;
		_kratakOpis = AlocirajIKopiraj(kratakOpis);
	}

	//Z4.8 :: operator +=  
	//Dodati novi post u niz pokazivaca
	//Onemoguciti dodavanje u slucaju da je popunjen niz pokazivaca
	bool operator +=(Post& p)
	{
		if (_trenutnoPostova == maxBrojPostova)
			return false;
		_postovi[_trenutnoPostova] = new Post(p);
		_trenutnoPostova++;
		return true;
	}

	//Z4.9 :: dtor
	~Sekcija()
	{
		delete[]_naziv, _kratakOpis;
		_naziv = _kratakOpis = nullptr;
		for (size_t i = 0; i < _trenutnoPostova; i++)
		{
			delete _postovi[i];
			_postovi[i] = nullptr;
		}
	}
	friend ostream& operator << (ostream& COUT, const Sekcija& obj);
};
//Z4.10 :: Ispisati podatke o sekciji [ukljucujuci i postove]
ostream& operator << (ostream& COUT, const Sekcija& obj)
{
	COUT << "Naziv sekcije: " << obj._naziv << endl;
	COUT << "Kratak opis: " << obj._kratakOpis << endl;
	COUT << "Broj postova: " << obj._trenutnoPostova << endl;
	for (size_t i = 0; i < obj._trenutnoPostova; i++)
	{
		cout << "----------------------------------------\n";
		cout << *obj._postovi[i];
	}
	return COUT;
}

const int maxBrojSekcija = 20;
class Forum {
	char* _naziv;
	int _trenutnoSekcija;
	Sekcija _sekcije[maxBrojSekcija];
	int _maxClanova;
	Clan* _clanovi;
	int _trenutnoClanova;
public:
	//Z5.1 :: Dflt. ctor
	Forum() {
		_naziv = nullptr;
		_trenutnoSekcija = 0;
		_maxClanova = 0;
		_clanovi = nullptr;
		_trenutnoClanova = 0;
	}
	//Z5.2 :: User-def. ctor
	Forum(const char* naziv, int maxClanova) {
		_naziv = AlocirajIKopiraj(naziv);
		_trenutnoSekcija = 0;
		_maxClanova = maxClanova;
		_clanovi = new Clan[maxClanova];
		_trenutnoClanova = 0;
	}
	//Z5.3 :: Copy ctor
	Forum(const Forum& obj) {
		_naziv = AlocirajIKopiraj(obj._naziv);
		_trenutnoSekcija = obj._trenutnoSekcija;
		for (size_t i = 0; i < _trenutnoSekcija; i++)
			_sekcije[i] = obj._sekcije[i]; // Sekcija::operator =
		_maxClanova = obj._maxClanova;
		_clanovi = new Clan[_maxClanova];
		_trenutnoClanova = obj._trenutnoClanova;
		for (size_t i = 0; i < _trenutnoClanova; i++)
			_clanovi[i] = obj._clanovi[i]; // Clan::operator = 
	}
	//Z5.4 :: Move ctor
	Forum(Forum&& obj) {
		_naziv = obj._naziv;
		obj._naziv = nullptr;
		_trenutnoSekcija = obj._trenutnoSekcija;
		for (size_t i = 0; i < _trenutnoSekcija; i++)
			_sekcije[i] = obj._sekcije[i]; // Sekcija::operator =
		_maxClanova = obj._maxClanova;
		obj._maxClanova = 0;
		_trenutnoClanova = obj._trenutnoClanova;
		obj._trenutnoClanova = 0;
		_clanovi = obj._clanovi;
		obj._clanovi = nullptr;
	}
	//Z5.5 :: Getteri
	int GetTrenutnoSekcija() const { return _trenutnoSekcija; }
	Sekcija GetSekcijaAtI(int index) const { return _sekcije[index]; }
	int GetBrojClanova() const { return _trenutnoClanova; }
	int MaxBrojClanova() const { return _maxClanova; }
	Clan GetClanAtI(int index) const { return _clanovi[index]; }


	//Z5.6 :: Setteri
	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}

	//Z5.7 :: Setter za _maxClanova
	/*
		Osigurati da je (noviMaxBrojClanova> _maxBrojClanova)
		Kreirati novi niz velicine (noviMaxBrojClanova)
		Kopirati sadrzaj iz starog niza u novi niz
	*/
	void SetMaxClanova(int noviMaxBrojClanova) {
		if (noviMaxBrojClanova > _maxClanova) {
			_maxClanova = noviMaxBrojClanova;
			Clan* temp = _clanovi;
			_clanovi = new Clan[_maxClanova];
			//_trenutnoClanova zadrzava istu vrijednost
			for (size_t i = 0; i < _trenutnoClanova; i++)
				_clanovi[i] = temp[i]; // Clan::operator = 
			delete[] temp;
			temp = nullptr;
		}
	}

	//Z5.8 Operator += (dodavanje nove sekcije)
	bool operator += (const Sekcija sekcija) {
		if (_trenutnoSekcija == maxBrojSekcija)
			return false;
		_sekcije[_trenutnoSekcija] = sekcija; // Sekcija::operator = 
		_trenutnoSekcija++;
		return true;
	}

	//Z5.9 :: operator += (dodavanje novog clana)
	//Ukoliko brojac dosegne vrijednost '_maxClanova', uraditi prosirivanje niza za 10 koristenjem metode 'SetMaxClanova'
	void operator += (const Clan clan) {
		if (_trenutnoClanova == _maxClanova)
			SetMaxClanova(_maxClanova + 10);
		_clanovi[_trenutnoClanova] = clan; // Clan::operator = 
		_trenutnoClanova++;
	}

	//Z5.10 :: dtor
	~Forum() {
		delete[] _naziv, _clanovi;
		_naziv = nullptr, _clanovi = nullptr;
	}

	friend ostream& operator <<(ostream& COUT, const Forum& f);
};

//Z5.11 :: Ispisati podatke o forumu, ispisati sekcije [zajedno sa postovima] te korisnicka imena forumasa [clanova]
ostream& operator <<(ostream& COUT, const Forum& f) {
	COUT << "Forum: " << f._naziv << endl;
	COUT << "Broj sekcija: " << f._trenutnoSekcija << endl;
	for (size_t i = 0; i < f._trenutnoSekcija; i++)
		COUT << "[" << endl << f._sekcije[i] << "] " << endl;
	COUT << "Broj forumasa: " << f._trenutnoClanova << endl;
	for (size_t i = 0; i < f._trenutnoClanova; i++)
		COUT << f.GetClanAtI(i).GetKorisnickoIme() << ",";
	COUT << endl;
	return COUT;
}


void Zadatak1() {
	int broj = 56511;
	cout << "Pretvaranje broja (56511) u str] : " << endl;
	char* stringBroj = IntToStr(broj);
	cout << stringBroj << endl;
	delete[] stringBroj;
	stringBroj = nullptr;
	cout << "Sve prijestupne godine izmedju [1900-2021]: " << endl;
	for (size_t i = 1900; i <= 2021; i++)
		if (PrijestupnaGodina(i))
			cout << i << ", ";
	cout << endl;
	Datum starWarsDay; //dflt. ctor
	starWarsDay.SetDan(4);
	starWarsDay.SetMjesec(5);
	starWarsDay.SetGodina(2021);
	cout << "Star Wars day: " << starWarsDay << endl; // operator <<

	Datum worldUfoDay(starWarsDay.GetDan() - 3, starWarsDay.GetMjesec() + 2, starWarsDay.GetGodina()); //user-def. ctor
	cout << "World Ufo day: " << worldUfoDay << endl;

	Datum laborDay(starWarsDay); //copy ctor
	laborDay.SetDan(1);
	cout << "Labor day (BiH): " << laborDay << endl;

	Datum victoryDay(move(laborDay)); //Move ctor
	victoryDay.SetDan(9);
	cout << "Victory day (BiH): " << victoryDay << endl;

	Datum juneSolstice(21, 6, 2021), juneSolstice_copy;
	juneSolstice_copy = juneSolstice;
	cout << "June Solstice (BiH): " << juneSolstice << endl;
	cout << "Dealokacija ..." << endl;

	Datum datumi[] = { Datum(1,2,2021), Datum(31,12, 2020), Datum(31, 12, 2021) };
	cout << "Razlika u danima: --->" << endl;
	cout << "Razlika izmedju: " << datumi[0] << " i " << datumi[1] << " je " << datumi[0] - datumi[1] << endl; // operator -
	cout << "Razlika izmedju: " << datumi[0] << " i " << datumi[2] << " je " << datumi[0] - datumi[2] << endl; // operator -
	cout << "Razlika izmedju: " << datumi[1] << " i " << datumi[2] << " je " << datumi[1] - datumi[2] << endl; // operator -

	//Testiranje operatora +
	Datum someDatum(5, 5, 2025);
	cout << "Test datum: " << someDatum << endl;
	cout << someDatum << " + 30 dana  = " << someDatum + 30 << endl; // operator +
	cout << "Dealokacija..." << endl;
}

void Zadatak2() {

	Clan almightyBruce;
	almightyBruce.SetKorisnickoIme("almightyBruce");
	almightyBruce.SetDatumRegistracije(Datum(1, 1, 2021));
	almightyBruce.SetSpol(0);
	almightyBruce.SetSpol(1);
	almightyBruce.SetLozinka("its'Goooood");
	cout << almightyBruce << endl;

	Clan crazyMage("CrazyMage", "PA$$w0rd", Datum(3, 12, 2019), 1);
	Clan copyCrazyMage(crazyMage);
	cout << copyCrazyMage << endl;

	Clan azermyth("Azermyth", "azerpass", Datum(1, 4, 2020), 1);
	Clan noviAzer(move(azermyth));
	cout << noviAzer << endl;
	cout << "Testiranje operatora '==' " << endl;
	cout << (crazyMage == copyCrazyMage ? "Isti clan!" : "Razlici clanovi!") << endl;

	Clan aceVentura;
	aceVentura = noviAzer;
	aceVentura.SetKorisnickoIme("8Ventura");
	cout << aceVentura << endl;
	cout << "Dealokacija..." << endl;
}
void Zadatak3() {
	Post p1;
	p1.SetNewPostId();
	p1.SetKorisnickoIme("Neo");
	p1.SetDatumObjavljivanja(Datum(5, 5, 2021));
	p1.SetSadrzaj("Izasao sam iz matrice. Osjecaj je prelijep...");
	cout << p1 << endl;

	Post p2("Trinity", Datum(5, 5, 2021), " Kolega @Neo, you don't say.");
	Post copyp2(p2);
	cout << copyp2 << endl;

	Post p3("Ementaler", Datum(6, 5, 2021), "Pozdrav ljudi. Ovdje Igor sa Hcl-a...");
	Post pr3new(move(p3));
	cout << pr3new << endl;

	Post p4;
	p4 = pr3new;
	p4.SetNewPostId();
	p4.SetKorisnickoIme("Agent Smith");
	p4.SetSadrzaj("Dragi kolega @Neo, pripremite se da vas dealociram.");
	cout << p4 << endl;
	cout << "Dealokacija..." << endl;
}

void Zadatak4() {
	Sekcija letNaMars("Let na mars, all about...", "Neki opis...");
	Post p1("bad_karma13", Datum(2, 3, 2020), "Ispucao je losu srecu na Cybertrucku.. Ovo uspijeva 100%");
	Post p2("monkey_see_monkey_do", Datum(3, 3, 2020), "Kad ono uzlijece Elon sa svojima? xD");
	Post p3("cerealKillerHoho", Datum(3, 3, 2020), "Teraformiranje Marsa ce se pokazati kao prevelik zalogaj za nasu generaciju...");
	Post p4("dr_Michio_Kaku", Datum(3, 3, 2020), "Ovo je prvi korak u kolonizaciji Suncevog sistema...");
	letNaMars += p1;
	letNaMars += p2;
	letNaMars += p3;
	Sekcija mars2(letNaMars);
	mars2 += p4;
	
	Sekcija mars3(move(mars2));
	Post p5("superSonic", Datum(3, 3, 2020), "Zelimo novo gostovanje g.Muska kod Joe Rogena!");
	mars3 += p5;
	
	
	
	Sekcija mars4;
	mars4 = mars3;
	cout << mars4 << endl;
	cout << "Dealokacija..." << endl;
}

void Zadatak5() {
	Forum nebula("Nebula:: forum o fizici i metafizici", 10);
	Clan arwen_dor("arwenix", "L0trI$L1fe", Datum(11, 1, 2021), 0);
	Clan thomasAnderson("neo", "one", Datum(12, 1, 2021), 1);
	Clan rickC_137("rickestRick", "wabalubadubdub", Datum(3, 3, 2021), 1);
	
	//Dodavanje clanova preko operatora +=
	nebula += arwen_dor;
	nebula += thomasAnderson;
	nebula += rickC_137;
	//
	Sekcija newAge("New Age", "Sta predstavlja New Age?");
	Post p1("arwenix", Datum(3, 3, 2020), "Postoji niz proturijecnih definicija o novom fenomenu ...");
	Post p2("neo", Datum(4, 3, 2020), "Nova religija? Ili ipak samo nova paradigma? ...");
	Post p3("rickestRick", Datum(5, 3, 2020), "Ovisi od konteksta u kojem se pojavljuje");
	newAge += p1; // dodavanje posta
	newAge += p2; // dodavanje posta
	newAge += p3; // dodavanje posta
	//
	Sekcija telepatija("Telepatija i telekineza", "Parapsiholoski fenomeni");
	Post p4("arwenix", Datum(6, 3, 2020), "Na ovom podrucju najvise se proslavio Uri Geller ...");
	Post p5("neo", Datum(7, 3, 2020), "Medju poznatije slucajeve ubraja se i Nina Kulagina...");
	telepatija += p4; // dodavanje posta
	telepatija += p5; // dodavanje posta
	//
	nebula += newAge; // dodavanje sekcije
	nebula += telepatija; // dodavanje sekcije
	//
	Forum copy_of_nebula(nebula);
	Forum nebula_prime(move(copy_of_nebula));
	cout << nebula_prime;
	cout << "Dealokacija..." << endl;
}

int main() {
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
	return 0;
}
