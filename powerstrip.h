#ifndef POWERSTRIP
#define POWERSTRIP

#include "other.h"
#include "electricdevice.h"

using namespace std;

class PowerStrip : public ElectricDevice{
    private:
        vector <Plug*> ListOfPlugs;             // lista wskaznikow na potomkow
        int PowerStripID;                       // ID na potrzeby wizualne
        Plug *Previous;                         // poprzednik
    public:

        PowerStrip(string, int, Plug*, int);
        PowerStrip(string, int, Plug*, int, vector<int>);
        ~PowerStrip();
        Plug *findID(int x);                    // rekurencyjne znajdowanie podanej wtyczki w drzewie
        void DFS();                             // przejsie po grafie typu DFS przy symulacji
        void update(int c);                     // uaktualnienie wartosci pradow w gore grafu
        void addNPlugs(int);                    // robocza funkcja do tworzenia podanej liczby gniazdek na listwie
        void print(int n);                      // wyswietlenie stanu listwy, potem rekurencyjnie poddrzewa, n - liczba wciec(strona wizualna)
        void generateRandomDevice();            // zapelnia rekurencyjnie wszystkie wolne wtyczki losowymi urzadzeniami
        void save();                            // zapisywanie stanu listwy do pliku
        void overcurrent();                     // rekurencyjnie wylacza wszystkie urzadzenia w poddrzewie po przeciazeniu
};

#endif // POWERSTRIP

