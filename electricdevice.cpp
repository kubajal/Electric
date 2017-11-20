#include "electricdevice.h"

ElectricDevice::ElectricDevice(){
    ID = *(AvailableID.begin());
    AvailableID.erase(AvailableID.begin());
    Current = 0;
}

ElectricDevice::~ElectricDevice(){
    AvailableID.insert(ID);

    ID = 0;
    Current = 0;
    Name = "";
}

void ElectricDevice::update(int x){ }

void ElectricDevice::save(){ }
