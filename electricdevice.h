#ifndef ELECTRICDEVICE
#define ELECTRICDEVICE

#include "other.h"

class ElectricDevice{
    public:
        int ID;                                 // globalne ID na potrzeby logiki programu
        int Current;                            // prad, jak przeplywa w danej chwili przez to urzadzenie
        string Name;                            // nazwa urzadzenia

        virtual void update(int);               // funkcja, ktora przy symulacji rekurencyjnie uaktualnia cale drzewo
        virtual void save();                    // zapisanie danego urzadzenia do pliku
        ElectricDevice();

        virtual ~ElectricDevice();              // wirtualny destruktor, potrzebny ze wzgledu na polimorfizm
};


#endif // ELECTRICDEVICE

