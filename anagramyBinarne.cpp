#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int licz_jedynki(string tekst){
    int licznik = 0;
    for(char h: tekst){
        if(h == '1'){
            licznik++;
        }
    }
    return licznik;
}

// konwersja BIN -> DEC
int dwojki_na_dzies(string l){ 
    int liczba = 0; 
    int waga = l.size() - 2; // znak bialy na koncu linii
    for(int i = 0; i < l.size(); i++){ 
        if(l[i] == '1'){ 
            int potega = 1;
            for(int j = 0; j < waga - i; j++){ 
                potega *= 2; 
            } 
            liczba += potega; 
        }
        
    } 
    return liczba; 
}

// konwersja DEC -> BIN
string dzies_na_dwojki(int li){
    string binarna;
    while(li > 0){
        if(li%2 == 0){
            binarna = "0"+binarna;
        }
        else{
            binarna = "1"+binarna;
        }
        li /= 2;
    }
    
    return binarna;
}

// obliczanie wartosci bezwzglednej
int wartosc_bezwzgledna(int liczba){
    if(liczba < 0){
        liczba *= -1;
    }
    return liczba;
}

// glowna funkcja
void przetwarzaj_zadania(){
    
    int zrownowazoneLiczby = 0;
    int prawieZrownowazone = 0;
    
    int licznikZera = 0;
    int licznikJedynki = 0;
    
    int liczba_dz = 0;
    int najwLiczbDz = 0;
    int bezCyfryZero = 0;
    
    int sumaRoz = 0, najwSuma = 0;
    int roznica = 0, najwRoznica = 0;
    
    vector<string> liczby_binarne;
    vector<int> liczby_dziesietne;
    
    string linia = "";
    string najwRozBin = "";
    string liczba_str = "";
    
    set<int> unikal_cyfry;
    
    bool maZero = false;
    
    // wejscie do plikow
    ifstream wejdzPlik("anagram.txt");
    ofstream zapisWynikuPlik("wyniki3.txt");
    
    // warunki kontrolne
    if(!wejdzPlik.is_open()){
        cerr << "Blad przy otwieraniu pliku anagram.txt" << endl;
        return;
    }

    if(!zapisWynikuPlik.is_open()){
        cerr << "Blad, plik wyniki3.txt nie moze zostac otwarty" << endl;
        return;
    }
    
    // glowna petla, odczytujaca plik linia po linii
    while(getline(wejdzPlik, linia)){
        
        // ------------- ZADANIE 3.1 --------------- //
        licznikZera = 0;
        licznikJedynki = 0;
        
        for(char c : linia){
            if(c == '0'){
                licznikZera++;
            }
            else if(c == '1'){
                licznikJedynki++;
            }
        }

        if(licznikJedynki == licznikZera){
            zrownowazoneLiczby++;
        } 
        else if(wartosc_bezwzgledna(licznikZera - licznikJedynki) == 1){
            prawieZrownowazone++;
        }
        
        // ------------- ZADANIE 3.2 --------------- //
        
        liczby_binarne.push_back(linia);
        
        // ------------- ZADANIE 3.3 --------------- //
        
        liczby_dziesietne.push_back(dwojki_na_dzies(linia));
        
        // ------------- ZADANIE 3.4 --------------- //
        
        sumaRoz = 0;
        liczba_dz = (dwojki_na_dzies(linia));
        liczba_str = to_string(liczba_dz);
        
        maZero = false; 
        for(char zer: liczba_str){ 
            if(zer == '0'){ 
                maZero = true; 
                break; 
            } 
        } 
        if(!maZero){ 
            bezCyfryZero++; 
        }

        // dodanie unikalnych cyfr do zbioru
        for(char cyfra: liczba_str){
            unikal_cyfry.insert(cyfra);
        }

        // suma unikalnych cyfr
        for(int unik_cyfra: unikal_cyfry){
            sumaRoz += unik_cyfra;
        }
        
        if(sumaRoz > najwSuma){
            najwSuma = sumaRoz;
            najwLiczbDz = liczba_dz;
        }
        
        unikal_cyfry.clear();
    }

// ------------- ZADANIE 3.3 - obliczanie najwiekszej roznicy --------------- //
    
    for(auto it = 0; it<liczby_dziesietne.size()-1; it++){
        roznica = wartosc_bezwzgledna(liczby_dziesietne[it] - liczby_dziesietne[it+1]);
        if(roznica>najwRoznica){
            najwRoznica = roznica;
        }
    }
    
    najwRozBin = dzies_na_dwojki(najwRoznica);

// ------------- ZADANIE 3.1 - zapis --------------- //
    
    zapisWynikuPlik<<"Zadanie 3.1."<<endl;
    zapisWynikuPlik<<"Liczby zrownowazone: "<<zrownowazoneLiczby<<endl;
    zapisWynikuPlik<<"Liczby prawie zrownowazone: "<<prawieZrownowazone<<"\n"<<endl;

// ------------- ZADANIE 3.2 - zapis + sprytny sposob na znalezienie najwiekszej liczby kombinacji --------------- //
    
    zapisWynikuPlik<<"Zadanie 3.2."<<endl;
    for(int i = 0; i<liczby_binarne.size(); i++){
        if(liczby_binarne[i].length()-1 == 8 && licz_jedynki(liczby_binarne[i]) > 3 && licz_jedynki(liczby_binarne[i]) < 6){
            //cout<<liczby_binarne[i]<<endl;
            zapisWynikuPlik<<liczby_binarne[i]<<endl;
        }
    }

// ------------- ZADANIE 3.3 - zapis --------------- //

    zapisWynikuPlik<<"\n";
    zapisWynikuPlik<<"Zadanie 3.3."<<endl;
    zapisWynikuPlik<<"Najwieksza roznica (bin): "<<najwRozBin<<"\n"<<endl;

// ------------- ZADANIE 3.4 - zapis --------------- //
    
    zapisWynikuPlik<<"Zadanie 3.4."<<endl;
    zapisWynikuPlik<<"Ilosc liczb bez zera: "<<bezCyfryZero<<endl;
    zapisWynikuPlik<<"Najwieksza suma roznych cyfr (liczba): "<<najwLiczbDz<<endl;

// ------------- Zamkniecie plikow --------------- //
    
    wejdzPlik.close();
    zapisWynikuPlik.close();
    
}

int main()
{
    przetwarzaj_zadania();
    cout<<"Praca wykonana przez: Bartosz Kucharzyszyn 4P"<<endl;
    
    return 0;
}
