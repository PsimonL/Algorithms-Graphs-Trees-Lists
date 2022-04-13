/*Opracuj odpowiednie struktury danych dla następującego problemu: 
Piszesz program dla obsługi turnieju tenisowego. 
Zawodnicy rejestrują się na turniej podając nazwisko oraz ranking WTA lub ATP (liczbę z zakresu 10-13000). 
Po zakończeniu rejestracji organizator chce by zostały automatycznie wygenerowane pary na pierwszą rundą na zasadzie:
pierwszy z ostatnim, drugi z przedostatnim itd. 
Jeśli ilość zawodników jest nieparzysta to ten "środkowy" automatycznie awansuje do rundy drugiej i nie jest wypisywany w paringach.
Szczegóły implementacji: Z klawiatury (przez cin) są podawane kolejno: liczba zawodników N oraz zawodnicy po kolei w postaci {Nazwisko, Ranking}. Na wyjściu (poprzez cout) program zwraca pary A-B oddzielone spacją {A-B C-D E-F}. W przypadku źle wprowadzonych danych (np ranking zawodnika poza zakresem) wypisz komunikat "Niepoprawne dane". W przypadku gdy kilka zawodników ma taki sam ranking - są one ustawiane alfabetycznie.
*/
#include <iostream>

using namespace std;

struct dane{
    int nrRanking;
    string nazwisko;
    dane *next= nullptr;
};

void lista(string nazwisko, int x, dane *&head){
    dane *dodanieZawodnika = new dane; //dynamiczna alokacja
    dodanieZawodnika -> nazwisko = nazwisko;
    dodanieZawodnika -> nrRanking = x;
    if(!head){
        head = dodanieZawodnika;
        return;
    }
    if(head -> nrRanking < dodanieZawodnika -> nrRanking){
        dodanieZawodnika -> next = head;
        head = dodanieZawodnika;
        return;
    }
    dane *pom = head;
    while(pom -> next  &&  pom -> next -> nrRanking >= dodanieZawodnika -> nrRanking){
        pom = pom -> next;
    }
    dodanieZawodnika -> next = pom -> next;
    pom -> next = dodanieZawodnika;
}

void wypisPar(dane *head, int liczba){

    int liczbaPar = liczba / 2;//liczba par
    dane *pomx = head;
    dane *pomy = head;
    while (liczbaPar){
        cout << pomx -> nazwisko;
        cout << '-';
        pomx = pomx -> next;
        pomy = head;
        for (int i = 0; i < liczba - 1; i ++){
            pomy = pomy -> next;
        }
        cout << pomy -> nazwisko<<' ';
        liczba --; liczbaPar --;
    }
}


int main(){
    int N; dane *head = nullptr;
    cin >> N;
    int pomdlaN = N;
    if (N <2){
        cout << "Wpisano niepoprawne dane!" << endl;
    }
    else{
        int x;
        string nazwisko;
        while (N > 0){
            cin >>nazwisko>> x;
            if (x < 10  ||  x > 13000){
                cout << "Wpisano niepoprawne dane!" << endl;
                return -1; //!!!!!!!!!
            }
            lista(nazwisko, x, head);
            N --;
        }
        wypisPar(head, pomdlaN);
    }
    return 0;
}