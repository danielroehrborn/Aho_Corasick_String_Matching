//std::ofstream out("C:\\Users\\xxx\\Desktop\\out.txt");
//std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
//std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

//std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
//std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
//std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!




#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Spell {
private:
	string scrollName;
public:
	Spell() : scrollName("") { }
	Spell(string name) : scrollName(name) { }
	virtual ~Spell() { }
	string revealScrollName() {
		return scrollName;
	}
};

class Fireball : public Spell {
private: int power;
public:
	Fireball(int power) : power(power) { }
	void revealFirepower() {
		cout << "Fireball: " << power << endl;
	}
};

class Frostbite : public Spell {
private: int power;
public:
	Frostbite(int power) : power(power) { }
	void revealFrostpower() {
		cout << "Frostbite: " << power << endl;
	}
};

class Thunderstorm : public Spell {
private: int power;
public:
	Thunderstorm(int power) : power(power) { }
	void revealThunderpower() {
		cout << "Thunderstorm: " << power << endl;
	}
};

class Waterbolt : public Spell {
private: int power;
public:
	Waterbolt(int power) : power(power) { }
	void revealWaterpower() {
		cout << "Waterbolt: " << power << endl;
	}
};

class SpellJournal {
public:
	static string journal;
	static string read() {
		return journal;
	}
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

	if (Fireball* s = dynamic_cast<Fireball*>(spell)) {
		s->revealFirepower();
	}
	else if (Frostbite*s = dynamic_cast<Frostbite*>(spell)) {
		s->revealFrostpower();
	}
	else if (Thunderstorm*s = dynamic_cast<Thunderstorm*>(spell)) {
		s->revealThunderpower();
	}
	else if (Waterbolt*s = dynamic_cast<Waterbolt*>(spell)) {
		s->revealWaterpower();
	}
}
/*
dat.txt:
10
thunder 48096
faPkdmElxiyjROOhuFHbaKpmmVAXQcPTiwtCiJC 28248 BVObzwbRESpqhpvjiDGmlVJ
frost 67386
fbiNbSjyFGXofbuNXGMhJNkDhhWzjAQQHXJuREWcpKtFZGxdHEUUyfRCmqxykCxJA 95277 OtSUtXkEDqSOYo
water 9241
zrWyPgdQNfbxYwblqVDuFgg 41156 BSkBUrnGiyXtrauVHXjepOsNzHCBxlKCcZhvPxDBmEGacemoreZpCsNlzBBIaSS
thunder 64405
noeIkFrhKXerEdMmSUoWKsDtOOnTwoRSWVEDDDfXrsZLDavzFmKjbOLACcJWiafftBPrHrDcBcWpm 2583 zWOgnrlJtbBabVEiHFeDopplrynLWeGaIBzusjysQFdGmYbDecojmkkivJqxlNahSZjJMKTAKjMfxAquIc
mTnzepygwRtKHXpfhlJERNMbSFpXwydcsnPPy 88529 BWHFActuaAWqPIMwwvLFKkKcQyBuIopancVKxFItfLLdFlglsRjAY
QivcjGDoqoZKuiDcFHqRBdtuPRrisYZoSyQuERxvPiYZNfbWTZHqwLiCeebfYSAgSZiOc 92226 OAAeqEXEmijuQqDEDYBlklSWURxcLxHlFBYuWSWMYHWJVHXigdjohAundoufZ

Expected:
Thunderstorm: 48096
6
Frostbite: 67386
5
Waterbolt: 9241
6
Thunderstorm: 64405
18
6
15
*/
class Wizard {
public:
	Spell *cast() {
		Spell *spell;
		string s; cin >> s;
		int power; cin >> power;
		if (s == "fire") {
			spell = new Fireball(power);
		}
		else if (s == "frost") {
			spell = new Frostbite(power);
		}
		else if (s == "water") {
			spell = new Waterbolt(power);
		}
		else if (s == "thunder") {
			spell = new Thunderstorm(power);
		}
		else {
			spell = new Spell(s);
			cin >> SpellJournal::journal;
		}
		return spell;
	}
};

int main_magic_spell() {
	std::ifstream in("C:\\Users\\xxx\\Desktop\\dat.txt");
	std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	int T;
	cin >> T;
	Wizard Arawn;
	while (T--) {
		Spell *spell = Arawn.cast();
		counterspell(spell);
	}
	return 0;
}

