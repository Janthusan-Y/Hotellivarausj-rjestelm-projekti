//Harjoitustyö  (tarkoitus rakentaa 4-5 p ohjelma)
//Janthusan Yogenthiran

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;


//Struct kuvaa yksittäistä huonetta. 
struct Huone {
	int huoneNumero;
	bool onVarattu;    //Varaustila (true = varattu ja false = vapaa)
	int hinta;
	string tyyppi;
	string puhelinNumero;
	string varaajanNimi;
};

//Alustetaan huoneet  
//Lista, johon kaikki huoneet tallennetaan = Vector<Huone>& huoneet
void alustaHuoneet(vector<Huone>& huoneet, int määrä) {
	int yhdenHengenHuoneet = määrä / 2;
	int kahdenHengenHuoneet = määrä / 2;

	//Yhden hengen huoneet
	for (int i = 0; i < yhdenHengenHuoneet; ++i) {
		huoneet.push_back({ i + 1, false, 100, "1hh", "", ""});
	}

	//Kahden hengen huoneet
	for (int i = yhdenHengenHuoneet; i < määrä; ++i) {
		huoneet.push_back({i + 1, false, 150, "2hh", "", ""});
	}
}

//Aliohjelma huoneen varaamiseen 
void varaaHuone(vector<Huone>& huoneet, const string& tyyppi, int öidenMäärä) {
	for (auto& huone : huoneet) {
		if (!huone.onVarattu && huone.tyyppi == tyyppi) {
			cout << "\nSyötä varaajan nimi: ";
			cin.ignore(); //poista rivivaihdot 
			getline(cin, huone.varaajanNimi);

			cout << "Syötä varaajan puhelinnumero: ";
			getline(cin, huone.puhelinNumero);

			//satunainen alennus (0, 10% tai 20%) 
			int alennus = (rand() % 3) * 10;
			float kokonaishinta = öidenMäärä * huone.hinta * (1 - alennus / 100.0);

			huone.onVarattu = true;
			cout << "\nHuone " << huone.huoneNumero << " varattu onnistuneesti!\n";
			cout << "Kokonaishinta (" << alennus << " % alennus): " << kokonaishinta << " euroa.\n";
			return;
		}
	}
	cout << "\nEi vapaita huoneita " << tyyppi << ".\n";
}

//Tällä aliohjelmalla näytetään kaikki vapaat huoneet
	void vapaatHuoneet(const vector <Huone>&huoneet, const string& tyyppi) {
		cout << "Vapaat huoneet (" << tyyppi << "):\n";
		bool found = false;

		for (const auto& huone : huoneet) {
			if (!huone.onVarattu && huone.tyyppi == tyyppi) {
				cout << "Huone numero: " << huone.huoneNumero << ", Hinta: " << huone.hinta << " euroa/yö\n";
				found = true;

			}
		}

		if (!found) {
			cout << "Ei vapaita huoneita " << tyyppi << ".\n";

		}
	}

	//varaus haetaan ns. huoneennumerolla
	void haeVarausNo(const vector<Huone>& huoneet, int huoneNumero) {
		for (const auto& huone : huoneet) {
			if (huone.huoneNumero == huoneNumero && huone.onVarattu) {
				cout << "\nVaraus löytyy\n";
				cout << "Huone: " << huone.huoneNumero << ", Varaaja: " << huone.varaajanNimi
					<< ", Puhelin: " << huone.puhelinNumero << "\n"; 
				return;
			}
		}
		cout << "\nVarausta ei löytynyt.\n";
}
	//varaus haetaan varaajan nimellä 
	void haeVarausNimella(const vector<Huone>& huoneet, const string& nimi) {
		for (const auto& huone : huoneet) {
			if (huone.varaajanNimi == nimi && huone.onVarattu) {
				cout << "\nVaraus löytyy:\n";
				cout << "Huone: " << huone.huoneNumero << ", Puhelin: " << huone.puhelinNumero << "\n";
				return;
			}
		}
		cout << "\nVarausta ei löytynt.\n";

	}

	int main() {

		setlocale(LC_ALL, "fi_FI");

		srand(time(0)); // satunnaislukugeneraattorin alustus 


		int huoneidenMäärä = (rand() % 131 + 40) / 2 * 2;

		vector<Huone> huoneet;
		alustaHuoneet(huoneet, huoneidenMäärä);

		int valinta;
		do {
			cout << "\n**** Hotellivarausjärjestelmä ****\n";
			cout << "1. Näytä vapaat yhden hengen huoneet (1hh)\n";
			cout << "2. Näytä vapaat kahden hengen huoneet (2hh)\n";
			cout << "3. Varaa huone\n";
			cout << "4. Hae varaus varausnumerolla\n";
			cout << "5. Hae varuas varaajan nimellä\n";
			cout << "6. Poistu\n";
			cout << "Valitse toiminto: ";
			cin >> valinta;

			switch (valinta) {

			case 1:
				vapaatHuoneet(huoneet, "1hh");
				break;

			case 2:
				vapaatHuoneet(huoneet, "2hh");
				break;

			case 3: { //Huoneen varaus
				string tyyppi;
				cout << "Syötä huonetyyppi (1hh tai 2hh): ";
				cin >> tyyppi;
				int öidenMäärä;
				cout << "Syötä öiden määrä: ";
				cin >> öidenMäärä;

				if (tyyppi == "1hh" || tyyppi == "2hh") {
					varaaHuone(huoneet, tyyppi, öidenMäärä);

				}
				else {
					cout << "\nVirheellinen huonetyyppi.n";
				}
				break;

			}
			case 4: {
				int huoneNumero;
				cout << "\nSyötä huoneen numero: ";
				cin >> huoneNumero;
				haeVarausNo(huoneet, huoneNumero);
				break;
			}
			case 5: {
				string nimi;
				cout << "\nSyötä varaajan nimi: ";
				cin.ignore();
				getline(cin, nimi);
				haeVarausNimella(huoneet, nimi);
				break;
			}
			case 6: //Ohjelma poistu/lopetus
				cout << "\Kiitos ja Hyvääpäivänjatkoa.\n";
				break;

			default:
				cout << "\nVirheellinen valinta, yritä uudelleen.\n";

			}
		} while (valinta != 6); //Toistetaan kunnes käytäjä valitsee lopettamisen.

		return 0 ;

	}
