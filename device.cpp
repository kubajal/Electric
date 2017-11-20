#include "device.h"
#include "plug.h"
#include "powerstrip.h"
#include "fuse.h"
#include "device.h"

using namespace std;

void Device::print(int n){
    space(n);
    cout << Name << " " << DeviceID;
    if(TimeSwitchedOn < 0)
        cout << ", wylaczony";
    else
        cout << ", prad: " << Current;
    cout << ", typ: " << Type;
    if(TotalTimeSwitchedOn > 0) cout << ", sr prad: " << float(Cost)/TotalTimeSwitchedOn << endl;
    else cout << ", sr prad: " << Current << endl;
}

Device::Device(int c, string n, string t, Plug* p, int ttd, int id) : ElectricDevice(){
    Cost = 0;
    TotalTimeSwitchedOn = 0;
    Previous = p;
    Current = c;
    Name = n;
    Type = t;
    TimeToDeath = ttd;
    TimeSwitchedOn = rand() % TIME + TIME;
    p->update(Current);

    DeviceID = id;
    set<int>::iterator it = AvailableDeviceID.find(DeviceID);
    if(it != AvailableDeviceID.end())
      AvailableDeviceID.erase(it);
}

Device::~Device(){
    Previous = NULL;
    AvailableDeviceID.insert(DeviceID);
    DeviceID = 0;
}

void Device::overcurrent(){
    if(isTurnedOn())
       turnOff();
}

void Device::roll(){
    NumberOfDevices++;
    TimeToDeath--;
    if(TimeToDeath == 0){
        Previous->unplug();
    }
    else if(TimeSwitchedOn > 1){
        Cost += Current;
        TotalTimeSwitchedOn++;
        Previous->update(-Current);
        int newCurrent = Current + (rand() % 30) - 15;
        Previous->update(newCurrent);
        Current = newCurrent;
        TimeSwitchedOn--;
    }
    else if(TimeSwitchedOn == 1){
        Cost += Current;
        TotalTimeSwitchedOn++;
        turnOff();
    }
    else if (TimeSwitchedOn == -1 || TimeSwitchedOn == 0){
        turnOn();
    }
    else if (TimeSwitchedOn < -1){
        TimeSwitchedOn++;
    }
    if(Current < 0)
        Current = -Current;
}

void Device::turnOn(){
    Previous->update(Current);
    TimeSwitchedOn = rand() % 10 + 5;
}

bool Device::isTurnedOn(){
    if(TimeSwitchedOn >= 0)
        return true;
    return false;
}

void Device::turnOff(){
    Previous->update(-Current);
    TimeSwitchedOn = - (rand() % 5 + 2);
}

void Device::save(){
    SaveTo << "d" << endl << Previous->PlugID << endl << Current << endl << Name << endl << Type << endl << TimeToDeath << endl << DeviceID << endl;
}
