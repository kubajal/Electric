#ifndef DEVICE
#define DEVICE

#include "other.h"
#include "electricdevice.h"

class Device : public ElectricDevice{
    private:
        int DeviceID;                           // ID na potrzeby wizualne
        int TimeToDeath;                        // czas po ktorym urzadzenie zostanie usuniete z obwodu
        int TimeSwitchedOn;                     // czas wlaczenia, dodatni - oznacza, ze urzadzenie generuje obciazenie, ujmemny - ze jest wylaczone
        int TotalTimeSwitchedOn;                // calkowity czas, jaki urzadzenie bylo do tej pory wlaczone
        Plug *Previous;                         // wskaznik na wtyczke, do kt
        void turnOn();                          // wlaczenie urzedzenia - zaczyna generowac obciazenie
        void turnOff();                         // wylaczenie urzadzenia - przestaje generowac prad
        int Cost;
    public:
        string Type;                            // nazwa typu - np. lodowka, komputer, telewizor, itp.

        Device(int, string, string, Plug*, int, int);
        ~Device();
        bool isTurnedOn();                      // true - urzadzenie generuje prad, false - nie generuje
        void roll();                            // uaktualnia przy symulacji stan urzadzenia
        void print(int n);                      // wyswietla to urzadzenie
        void save();                            // zapisuje urzadzenie
        void overcurrent();
};

#endif // DEVICE

