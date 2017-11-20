#ifndef OTHER
#define OTHER

#define MAXCURRENT 100                          //maksymalny prad w obwodzie
#define MAXFUSE 1000                            //maksymalny prad bezpiecznika
#define TIME 10                                 //czas "zycia" urzadzenia

#include <string>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <set>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

class ElectricDevice;                           // klasa bazowa - abstrakyjne urzadzenie elektryczne
class Plug;                                     // wtyczka - zawsze posredniczy miedzy dwoma dowolnymi urzadzeniami, pelni role krawedzi w grafie
class Device;                                   // urzadzenie, ktore generuje obciazenie w obowdzie, jest lisciem w drzewie
class Fuse;                                     // bezpiecznik - przy przeciazeniu wylacza wszystkich w poddrzewie
class PowerStrip;                               // listwa z wtyczkami - pelni role rozgalezienia w grafie

void space(int n);                              // robi wciecia przy wyswietlaniu drzewa - strona wizualna
string randomString();                          // zwraca slowo typu "lodowka", "komputer", "telewizor", itp.

void init();                                    // inicjalizacja progamu

void fillBuf();                                 // funkcje sluzace do sprawdzania
bool validateName();                            // czy uzytkownik nie wprowadza
int validateNumber();                           // liter gdy proszony jest o liczbe
int validateCommand();                          // itp

void welcome();                                 // wiadomosc powitalna
void printAll();                                // wyswietlenie grafu
void wait();                                    // opoznienie
void menu();                                    // wyswietla menu
void run();                                     // uruchomienie progamu
void simulate();                                // symulacja
void generateRandomStructure();                 // generuje losowa strukture
void saveAll();                                 // zapisuje strukture do pliku "data.txt"
void load();                                    // wczytuje strukture z pliku o nazwie "data.txt"
void exit();                                    // przy wyjsciu z programu usuwa wszystkie dynamiczne struktury

extern set<int> AvailableID;                    // struktury
extern set<int> AvailablePlugID;                // potrzebne
extern set<int> AvailableFuseID;                // do
extern set<int> AvailablePSID;                  // ladnego      // potrzebne przy nadawaniu numerow identyfikacyjnych
extern set<int> AvailableDeviceID;              // wygladu
extern set<int, std::greater<int>> FreePlugs;   // programu

extern int TotalCost;                                // dotychczasowa ilosc jednostek pradu, jaka pobral uklad
extern int TotalTime;                           // dotychczasowy czas symluacji
extern long long NumberOfDevices;               // licznik ile bylo urzadzen w obwodzie do sporzadzenia statystyk

extern Plug *Root;                              // korzen drzewa
extern string Buf;                              // walidacja danych od uzytkownika

extern ofstream SaveTo;                         // zapisywanie do pliku
extern ifstream LoadFrom;                       // wczytywanie z pliku

#endif // OTHER

