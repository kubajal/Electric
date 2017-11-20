#ifndef FUSE
#define FUSE

#include "other.h"
#include "electricdevice.h"

class Fuse : public ElectricDevice{
    private:
        int FuseID;                             // ID na potrzeby wizualne
        Plug *Next;                             // wskaznik na nastepna wtyczke
        Plug *addNewPlug();                     // przy tworzeniu bezpiecznika tworzona jest od razu wtyczka z nim zwiazana, do ktorej dalej mozna podpinac rzeczy
        Plug *Previous;                         // wskaznik na poprzednika
        int TimesFused;                         // ile razy wywalilo korki?
    public:
        float MaximumCurrent;                   // maksymalny prad, jaki moze plynac przez bezpiecznik.

        Fuse(int, string, Plug*, int, int);
        ~Fuse();
        void DFS();                             // przejscie po drzewie typu DFS przy symulacji
        void update(int c);                     // uaktualnienie wartosci pradu przy wlaczeniu lub wylaczniu urzadzenia
        void print(int n);                      // wyswietlenie stanu bezpiecznika i dalej rekurencyjnie poddrzewa, n odpowiada za liczbe wciec(strona wizualna)
        Plug *findID(int x);                    // rekurencyjne znajdywanie wskaznika na dana wtyczke w drzewie
        void generateRandomDevice();            // tworzy losowe urzadzenie, ktore obciaza uklad
        void save();                            // zapisywanie do pliku bezpiecznika
        void overcurrent();                     // przy przeciazeniu wylacza wszystkie urzadzenia w poddrzewie
};

#endif // FUSE

