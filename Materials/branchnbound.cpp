// szkielet branch'n'bound
//
// nalezy zastanowic sie nad zamiana wektorow STL na listy STL ze wzgledow wydajnosciowych

#include <vector>
#include <iostream>

using namespace std;

const int N = 5;		// rozmiar problemu (liczba miast dla komiwojazera lub liczba zadan dla problemu szeregowania)

// glowna funkcja rekurencyjna. Parametry:
//
// miastaOdwiedzone    - reprezentuje aktualne rozwiazanie (pelne dla lisci, czesciowe w innych przypadkach)
//                       jest to jedna zmienna wspoldzielona (przekazywana) przez wszystkie wywolania
//
// miastaNieodwiedzone - reprezentuje miasta, ktorych jeszcze nie dodano. Potrzebna jest do wywolywania dalszych rekurencji
//                       jest tylko jedna zmienna wspoldzielona (przekazywana) przez wszystkie wywolania
//
// pozycjaPowrotna     - potrzebna, gdyz podczas powrotow przesuwamy miasta z odwiedzonych z powrotem do nieodzwiedzonych
//                       i musimy jest wstawic dokladnie w ta sama pozycje, z ktorej je wzielismy. Zmienna ta zapamietuje
//                       wlasnie ta pozycje
//
// wartosc             - wartosc funkcji celu aktualnego rozwiazania czesciowego (tj. wektora miastaOdwiedzone. Mozna ja
//                       kazdorazowo wyliczac z tego wektora, ale jest to powolne). Wspoldzielona przez wszystkie wywolania
//
// najRoz              - najlepsze dotad znalezione rozwiazanie (permutacja miast/zadan). Wspoldzielone przez wszystkie
//                       wywolania
//
// najWartosc          - wartosc najleszego do tej pory rozwiazania. Posluzy rowniez za oszacowanie (upper bound).
//                       Wspoldzielona przez wszystkie wywolania
//
void rekurencja( vector<int> & miastaOdwiedzone , vector<int> & miastaNieodwiedzone , int pozycjaPowrotna , int & wartosc , vector<int> & najRoz , int & najWartosc )
{
	// sekcja wypisywania na ekran (informacje diagnostyczno-pogladowe)
	// mozna zakomentowac ktoras sekcje if/else, by wyswietlic kolejnosc odwiedzania lisci/nie-lisci

	if ( miastaOdwiedzone.size() == N )
	{
		cout << "    Lisc ";
		cout << miastaOdwiedzone[0];
		for ( int i = 1; i < miastaOdwiedzone.size(); ++i )
			cout << "," << miastaOdwiedzone[i];
		cout << endl;
	}
	else
	{
		cout << "    Nie-lisc ";
		cout << miastaOdwiedzone[0];
		for ( int i = 1; i < miastaOdwiedzone.size(); ++i )
			cout << "," << miastaOdwiedzone[i];
		cout << endl;
	}


	// sekcja prawdziwa

	if ( miastaOdwiedzone.size() == N )
	{
		// znalezlismy nowe pelne rozwiazanie (lisc), sprawdzamy czy jest nowym najlepszym

		if ( wartosc < najWartosc )
		{
			najWartosc = wartosc;
			najRoz = miastaOdwiedzone;
		}
	}
	else
	{
		// jestesmy w nie-lisci, wiec trzeba sprobowac zejsc w tyle poddrzew ile jeszcze zostalo miast nieodwiedzonych
		// dla kazdego poddrzewa utworzymy osobne wywolanie rekurencyjne, o ile jest sens
		for ( int i = 0; i < miastaNieodwiedzone.size(); ++i )
		{
			int nowy = 1; // tu musi byc wartosc, ktora bedzie wynikala z dodania miasta/zadania miastaNieodwiedzone[i]
			              // do aktualnego rozwiazania czesciowego
						  // czyli jesli obecne rozwiazanie komiwojazera to 3,4,2 a wartosc miastaNieodwiedzone[i] to 5
						  // to nowy = koszt przejscia z miasta 2 do miasta 5
			              // dla problemu szeregowania jest troche bardziej skomplikowane (ale tylko troche )

			// przy okazji, pamietam rozmowe o tym czy waga zadania moze byc zero. Doszlismy do wniosku, ze nie moze...
			// ...ale spoznienie moze byc zerowe, wiec iloczyn waga * spoznienie moze byc zero i w miare schodzenia w dol
			// drzwa dla naszego problemu szeregowania "wartosc" nie musi malec (ale na pewno nie bedzie rosnac). Niewiele
			// to jednak zmienia.

			// zwiekszamy wartosc czesciowego rozwiazania (w dol drzewa)
			wartosc += nowy;

			// jesli jest sens wchodzic w poddrzewo. Ten if ma byc odkomentowany. Zakomentowalem go, bo u mnie w kazdym
			// wezle jest to samo (now = 1 powyzej) i zawsze bedzie obcinac
			// if ( wartosc < najWartosc )
			{
				miastaOdwiedzone.push_back( miastaNieodwiedzone[i] );
				miastaNieodwiedzone.erase( miastaNieodwiedzone.begin() + i );

				rekurencja( miastaOdwiedzone , miastaNieodwiedzone , i , wartosc , najRoz , najWartosc );
			}

			// zmniejszamy wartosc czesciowego rozwiazania (w gore drzewa, albo w ogole nie zeszlismy
			//  i trzeba przywrocic stara wartosc)
			wartosc -= nowy;
		}
	}

	miastaNieodwiedzone.insert( miastaNieodwiedzone.begin() + pozycjaPowrotna , miastaOdwiedzone.back() );
	miastaOdwiedzone.pop_back();
}

int policzWartoscFunkcjiCelu( vector<int> & rozwiazanie )
{
	return 1; // do uzupelnienia, tutaj dalem duzo, bo inaczej
}

int main( int argc , char ** argv )
{
	vector<int> odwiedzone;
	vector<int> nieodzwiedzone;

	// wybieramy sobie pierwsze miasto jako 1, bo wszystkie N podrzew na pierwszym poziomie sa rownowazne
	// tj. przykadowe permutacje 123456 oraz 456123 reprezentuja to samo rozwiazanie
	odwiedzone.push_back( 1 );

	for ( int i = 2; i <= N; ++i )
		nieodzwiedzone.push_back( i );

	vector<int> najlepszeRozwiazanie;

	// wektor najlepszeRozwiazanie ustalamy albo poprzez jakas heurystyke
	// (np. zachalnna, dla komiwojazera bedzie to algorytm najblizszych sasiadow,
	// dla szeregowania zadan moze to byc np. algorytm NEH)
	//
	// mozemy tez wybrac "losowe" rozwiazanie jak ponizej

	for ( int i = 1; i <= N; ++i )
		najlepszeRozwiazanie.push_back( i );	// proste rozwiazanie 1 , 2 , 3 , ... , N-1 , N

	int najlepszaWartosc = policzWartoscFunkcjiCelu( najlepszeRozwiazanie );

	int aktualnaWartosc = najlepszaWartosc;

	// odpalamy rekurencje
	rekurencja( odwiedzone , nieodzwiedzone , 0 /* chyba bez znaczenia czy bedzie to 0 czy nie */ , aktualnaWartosc , najlepszeRozwiazanie , najlepszaWartosc );

	return 0;
}
