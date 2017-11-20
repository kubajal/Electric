#ifndef PLUG
#define PLUG

#include "other.h"
#include "electricdevice.h"

using namespace std;

class Plug : public ElectricDevice{
    private:
        PowerStrip *NextPowerStrip;             // nastepnicy
        Fuse *NextFuse;
        Device *NextDevice;
    public:
        ElectricDevice *Previous;               // poprzednik
        int PlugID;                             // ID na potrzeby wizualne

        Plug(string, ElectricDevice*, int);
        ~Plug();
        Plug *findID(int x);                    // rekurencyjne znajdowanie podanej wtyczki po ID
        void DFS();                             // przejscie po drzewie typu DFS
        void refresh();                         // gdy jakies urzadzenie jest wpiete do tej wtyczki to uaktualnia jego stan
        void update(int c);                     // rekurencyjnie uaktualnia wartosc pradu w gore
        bool isFree();                          // sprawdza czy nic nie jest podlaczone do wtyczki
        void unplug();                          // odlacza wszystko w dol od danej wtyczki w drzewie
        void newDevice(int, string, string, int, int);  // wpina urzadzenie do wtyczki
        void newPowerStrip(int, int);           // wpina listwe do wtyczki
        void newFuse(int , string, int);        // wpina bezpiecznik do wtyczki
        void print(int n);                      // wyswietla stan wtyczki, i rekurencyjnie wyswietla poddrzewo, n odpowiada za liczbe wciec(strona wizualna)
        void generateRandomDevice();            // zapelnia rekurencyjnie wszystkie wolne wtyczki losowymi urzadzeniami
        void save();                            // zapisuje do pliku
        void loadStrip();                       // wczytuje z pliku listwe
        void loadDevice();                      // wczytuje z pliku urzadzenie
        void loadFuse();                        // wczytuje z pliku bezpiecznik
        bool isFused();                         // sprawdza czy wystapilo przeciazenie
        void overcurrent();                     // przy przeciazeniu wylacza wszystkie urzadzenia w poddrzewie
};

#endif // PLUG

