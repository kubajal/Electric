#include "other.h"
#include "plug.h"
#include "powerstrip.h"
#include "fuse.h"
#include "device.h"

using namespace std;

set<int> AvailableID;
set<int> AvailablePlugID;
set<int> AvailableFuseID;
set<int> AvailablePSID;
set<int> AvailableDeviceID;
set<int, std::greater<int> > FreePlugs;

ofstream SaveTo;
ifstream LoadFrom;

int TotalCost;
int TotalTime;
long long NumberOfDevices;

Plug *Root = NULL;
string Buf;

void init()
{
    for(int i = 1; i < 1000; i++){
        AvailablePlugID.insert(i);
        AvailableFuseID.insert(i);
        AvailablePSID.insert(i);
        AvailableDeviceID.insert(i);
        AvailableID.insert(i);
    }
    try{
        Root = new Plug("Wtyczka", NULL, *AvailablePlugID.begin());
        if(Root == NULL)
            throw "Nie udalo sie przydzielic pamieci dla korzenia.";
    }
    catch(string w){
            cout << w << endl;
    }

}

void space(int n){
    for(int i = 0; i < n; i++)
        cout << "  ";
}
string randomString()
{
    vector <string> a = {"Lodowka", "Mikrofalowka", "Telewizor", "Radio", "Kuchenka", "Glosniki", "Konsola",  "Komputer", "Lampa", "Laptop", "Router", "Telefon", "Wiertarka", "Mikser", "Blender", "Szybkowar"};
    return a[rand() % a.size()];
}

bool comp(int a, int b){
    return a > b;
}

void fillBuf(){
    Buf.clear();
    cin >> Buf;
    if(*(Buf.end()) == 10)
        *(Buf.end()) = 0;
}

bool validateName(){
    fillBuf();
    if(Buf.size() > 10)
        return 0;
    for(unsigned int i = 0; i < Buf.size(); i++)
        if(!(Buf[i] <= 'z' && Buf[i] >= 'a'))
            return false;
    return true;
}

int validateNumber(){
    fillBuf();
    if(Buf.size() > 10)
        return 0;
    for(unsigned int i = 0; i < Buf.size(); i++){
        if(!(Buf[i] <= '9' && Buf[i] >= '0')){
            return 0;
        }
    }
    return stoi(Buf);
}

int validateCommand(){
    fillBuf();
    if(Buf.size() != 1)
        return 0;
    if(!(Buf[0] <= '9' && Buf[0] >= '0'))
        return 0;
    return stoi(Buf);
}

void welcome()
{
    cout << "Praca na zaliczenie projektu z przedmiotu PROI. Etap trzeci." << endl;
    cout << "Program do symulacji obwodu elektrycznego w budynku." << endl;
    cout << "Jakub Jalowiec, semestr 15Z, grupa D2I1 WEiTI." << endl << endl << "---" << endl << endl;
    cout << "INSTRUKCJA OBSLUGI" << endl << endl;
    cout << "Uzytkownik zaczyna z jednym hipotetycznym zrodlem pradu, do ktorego moze dowolnie podlaczac 3 typy urzadzen elektrycznych: bezpiecznik, listwa, urzadzenie wykonawcze. Do bezpiecznikow i listw mozna dalej samodzielnie dolaczac kolejne rodzaje urzadzen. Kazde urzadzenie otrzymuje numer ID i to po nim jest ono rozpoznawane przez program. Ponadto, uzytkownik moze wygenerowac podana liczbe urzadzen, pobierajacych prad. Nie moze ona byc wieksza niz liczba wolnych wtyczek." << endl;
    cout << "Nazwy urzadzen musza skladac sie maksymalnie z 10 znakow, ktore sa malymi literami" << endl;
    cout << endl << endl << "---" << endl << endl;
}

void printAll()
{
    system("cls");
    welcome();
    Root->print(0);
    cout << endl;
    cout << "=================================================" << endl;
    cout << "dotychczasowy calkowity pobor: " << TotalCost << endl;
    if(TotalTime)
        cout << "srednia ilosc urzadzen w sieci: " << (double)NumberOfDevices/TotalTime << endl;
    else
        cout << "srednia ilosc urzadzen w sieci: " << 0 << endl;
    cout << "dotychczasowy czas symulacji: " << TotalTime << endl;
    cout << "-------------------------------------------------" << endl;
}

void wait()
{
    int t = 250;
    Sleep(t);
    cout << ".";
    Sleep(t);
    cout << ".";
    Sleep(t);
    cout << ".";
    Sleep(t);
    cout << endl;
}

void menu()
{
    while(1){
        int p, q, r, s;

        printAll();

        cout << "1 - operacja na poszczegolnej wtyczce, 2 - symulacja obwodu, 3 - wygenerowanie losowego obwodu(obwod musi byc pusty), 4 - dolaczenie do wszystkich wolnych wtyczek losowych urzadzen, 5 - zapisz, 6 - wczytaj, 7 - wyjdz." << endl;
        while(!(p = validateCommand()))
            cout << "Podaj komende jeszcze raz." << endl;
        switch(p)
        {
            case 1:
            {
                cout << "Podaj numer wtyczki" << endl;
                while(!(q = validateNumber())){
                    cout << "Podaj poprawny numer." << endl;
                }
                Plug *f = Root->findID(q);
                if(f == NULL){
                    cout << "Nie znaleziono gniazdka o podanym ID.";
                    wait();
                    continue;
                }
                cout << "1 - odpiecie wszystkiego od gniazdka, 2 - dodanie czegos do gniazdka." << endl;
                while(!(r = validateCommand())){
                    cout << "Podaj poprawna komende." << endl;
                }
                switch(r)
                {
                    case 1:
                    {
                        f->unplug();
                        break;
                    }
                    case 2:
                    {
                        if(!f->isFree()){
                            cout << "Do podanego gniazdka jest juz cos podlaczone. Prosze odpiac to co jest podlaczone i wtedy podlaczyc cos nowego lub wybrac inne gniazdko." << endl;
                            Sleep(2500);
                            continue;
                        }
                        cout << "Podaj co chcesz zrobic: 1 - dolaczyc bezpiecznik, 2 - dolaczyc listwe, 3 - urzadzenie" << endl;
                        while(!(s = validateCommand())){
                            cout << "Podaj poprawna komende." << endl;
                        }
                        if(s == 1){
                            int t;

                            cout << "Podaj maksymalna moc bezpiecznika." << endl;
                            while(!(t = validateNumber()))
                                cout << "Podaj poprawna liczbe, wyrazajaca moc bezpiecznika." << endl;
                            f->newFuse(t, "Bezpiecznik", *AvailableFuseID.begin());
                        }
                        else if(s == 2){
                            int t;

                            cout << "Podaj ile wtyczek ma miec listwa." << endl;
                            while(!(t = validateNumber()))
                                cout << "Podaj poprawna liczbe, wyrazajaca liczbe wtyczek." << endl;
                            f->newPowerStrip(t, *AvailablePSID.begin());
                        }
                        else if(s == 3){
                            int c;
                            string n, t;

                            cout << "Podaj prad jaki pobiera to urzadzenie." << endl;
                            while(!(c = validateNumber()))
                                cout << "Podaj poprawna liczbe, wyrazajaca prad, jaki pobiera dane urzadzenie." << endl;
                            cout << "Podaj nazwe dla tego urzadzenia." << endl;
                            while(!(validateName()))
                                cout << "Podaj poprawna nazwe dla urzadzenia." << endl;
                            n = Buf;
                            cout << "Podaj typ tego urzadzenia." << endl;
                            while(!(validateName()))
                                cout << "Podaj poprawny typ urzadzenia." << endl;
                            t = Buf;
                            f->newDevice(c, n, t, 50, *AvailableFuseID.begin());
                        }
                        else{
                            cout << "Nieprawidlowa komenda." << endl;
                            continue;
                        }
                        break;
                    }
                }
                continue;
            }
            case 2:
            {
                simulate();
                continue;
            }
            case 3:
            {
                generateRandomStructure();
                continue;
            }
            case 4:
            {
                Root->generateRandomDevice();
                continue;
            }
            case 5:
            {
                saveAll();
                break;
            }
            case 6:
            {
                load();
                break;
            }
            case 7:
                exit();
                return;
            default:
                continue;

        }
    }
}

void simulate(){
    int k = 20;
    while(k--){
        printAll();
        TotalTime++;

        Root->refresh();
    }
}

void generateRandomStructure(){
    if(!Root->isFree()){
        cout << "Juz istnieje jakas struktura. Generowac losowa strukture mozna tylko od zera." << endl;
        wait();
        return;
    }
    Root->newFuse(2000, "Bezpiecznik", *AvailableFuseID.begin());
    Plug *f = Root->findID(2);
    f->newPowerStrip(rand()%5 + 5, *AvailablePSID.begin());
    printAll();
    int l = 0;
    while(l < 5){
        l++;
        int r = rand() % (*AvailablePlugID.begin() - 1) + 1;
        f = Root->findID(r);
        if(f->isFree()){
            int k = rand() % 2;
            if(k == 1){
                f->newFuse(rand() % MAXCURRENT + 100 , "Bezpiecznik",  *AvailableFuseID.begin());
            }
            else{
                f->newPowerStrip(rand() % 5 + 3,  *AvailablePSID.begin());
            }
        }
        printAll();
    }
    Root->generateRandomDevice();
}

void run()
{
    srand(time(0));
    init();
    menu();
}

void saveAll()
{
    SaveTo.open("data.txt", std::ofstream::out);
    wait();
    Root->save();
    SaveTo.close();
}

void load()
{
    try{
    LoadFrom.open("data.txt", std::ofstream::in);
    if(!LoadFrom.is_open()){
           string w = "Nie znaleziono pliku.";
           throw w;
       }
    }
    catch(string w){
        cout << w <<  endl;
        wait();
        return;
    }
    Root->unplug();
    string r;
    while(LoadFrom >> r)
    {
        if(r == "f"){
            int plug;
            LoadFrom >> plug;
            Plug *p = Root->findID(plug);
            p->loadFuse();
            printAll();
        }
        else if(r == "d"){
            int plug;
            LoadFrom >> plug;
            Plug *p = Root->findID(plug);
            p->loadDevice();
        }
        else if(r == "p"){
            int plug;
            LoadFrom >> plug;
            Plug *p = Root->findID(plug);
            p->loadStrip();
            printAll();
        }
    }
    LoadFrom.close();
}

void exit(){
    Root->unplug();
    delete Root;
}
