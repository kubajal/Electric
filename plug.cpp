#include "plug.h"
#include "plug.h"
#include "powerstrip.h"
#include "fuse.h"
#include "device.h"

bool Plug::isFree(){
    return (NextDevice == NULL && NextFuse == NULL && NextPowerStrip == NULL);
}

void Plug::generateRandomDevice(){
    if(isFree())
        NextDevice = new Device(rand() % 100 + 100, "Urzadzenie", randomString(), this, rand() % 5 + 10, *AvailableDeviceID.begin());
    else if(NextPowerStrip != NULL)
        NextPowerStrip->generateRandomDevice();
    else if(NextFuse != NULL)
        NextFuse->generateRandomDevice();
}

Plug *Plug::findID(int x){
    if(x == PlugID)
        return this;
    else{
        if(NextPowerStrip != NULL)
            return NextPowerStrip->findID(x);
        if(NextFuse != NULL)
            return NextFuse->findID(x);
    }
    return NULL;
}

void Plug::print(int n){
    space(n);
    cout << Name << " " << PlugID << endl;
    if(NextDevice != NULL)
        NextDevice->print(n+1);
    if(NextPowerStrip != NULL)
        NextPowerStrip->print(n+1);
    if(NextFuse != NULL)
        NextFuse->print(n+1);
}

void Plug::refresh(){
    TotalCost += Root->Current;

    Root->DFS();
    int l = 20;
    while(l--){
        Plug *f = Root->findID(rand() % (*FreePlugs.begin()) + 1);
        if(f != NULL && f->isFree()){
            f->newDevice(rand() % 100 + 50, "Urzadzenie", randomString(), rand() % TIME + 15, *AvailableDeviceID.begin());
        }
    }
}


void Plug::unplug(){
    if(Previous != NULL){
        Previous->update(-Current);
    }
    Current = 0;
    if(NextDevice != NULL){
        delete NextDevice;
        NextDevice = NULL;
    }
    else if(NextPowerStrip != NULL){
        delete NextPowerStrip;
        NextPowerStrip = NULL;
    }
    else if(NextFuse != NULL){
        delete NextFuse;
        NextFuse = NULL;
    }
}

Plug::Plug(string n, ElectricDevice* p, int id) : ElectricDevice(){
    Previous = p;
    Name = n;
    NextDevice = NULL;
    NextPowerStrip = NULL;
    NextFuse = NULL;
    PlugID = id;
    set<int>::iterator it = AvailablePlugID.find(PlugID);
    AvailablePlugID.erase(it);
    FreePlugs.insert(PlugID);
}

Plug::~Plug(){

    if(NextDevice != NULL){
        delete NextDevice;
        NextDevice = NULL;
    }
    else if(NextPowerStrip != NULL){
        delete NextPowerStrip;
        NextPowerStrip = NULL;
    }
    else if(NextFuse != NULL){
        delete NextFuse;
        NextFuse = NULL;
    }
    Previous = NULL;
    AvailablePlugID.insert(PlugID);
    FreePlugs.erase(PlugID);
    PlugID = 0;
}

void Plug::newDevice(int c, string n, string t, int ttd, int id){
    try{
        NextDevice = new Device(c, n, t, this, ttd,  id);
        if(NextDevice == NULL)
            throw "Nie udalo sie przydzielic pamieci dla urzadzenia.";
    }
    catch(string w){
            cout << w << endl;
    }
}

void Plug::newFuse(int mc, string n, int id){
    try{
        NextFuse = new Fuse(mc, "Bezpiecznik", this, id, *AvailablePlugID.begin());
        if(NextFuse == NULL)
            throw "Nie udalo sie przydzielic pamieci dla bezpiecznika.";
    }
    catch(string w){
            cout << w << endl;
    }
}

void Plug::newPowerStrip(int n, int id){
    try{
        NextPowerStrip = new PowerStrip("Listwa", n, this, id);
        if(NextPowerStrip == NULL)
            throw "Nie udalo sie przydzielic pamieci dla listwy.";
    }
    catch(string w){
            cout << w << endl;
    }
}

bool Plug::isFused(){
    if(NextFuse != NULL){
        if(NextFuse->Current > NextFuse->MaximumCurrent)
            return true;
    }
    return false;
}

void Plug::update(int c){
    Current += c;
    if(Previous != NULL)
        Previous->update(c);
}

void Plug::overcurrent(){
    if(NextDevice != NULL)
        NextDevice->overcurrent();
    else if(NextFuse != NULL)
        NextFuse->overcurrent();
    else if(NextPowerStrip != NULL)
        NextPowerStrip->overcurrent();
}

void Plug::DFS(){
    if(NextDevice != NULL){
        NextDevice->roll();
    }
    else if(NextFuse != NULL)
        NextFuse->DFS();
    else if(NextPowerStrip != NULL)
        NextPowerStrip->DFS();
}


void Plug::save(){
    if(NextDevice != NULL){
        NextDevice->save();
    }
    else if(NextFuse != NULL){
        NextFuse->save();
    }
    else if(NextPowerStrip != NULL){
        NextPowerStrip->save();
    }
}

void Plug::loadStrip(){
    if(LoadFrom.is_open()){
        int n, id;
        vector<int> v;

        LoadFrom >> n >> id;
        for(int i = 0; i < n; i++){
            int y;
            LoadFrom >> y;
            v.push_back(y);
        }
        try{
            NextPowerStrip = new PowerStrip("Listwa", n, this, id, v);
            if(NextPowerStrip == NULL)
                throw "Nie udalo sie przydzielic pamieci dla listwy. ";
        }
        catch(string w){
            cout << w << endl;\
        }
    }
}

void Plug::loadDevice(){
    if(LoadFrom.is_open()){
        int current, ttd, id;
        string name, type;
        LoadFrom >> current >> name >> type >> ttd >> id;
        try{
            NextDevice = new Device(current, name, type, this, ttd, id);
            if(NextDevice == NULL)
                throw "Nie udalo sie przydzielic pamieci dla urzadzenia.";
        }
        catch(string w){
            cout << w << endl;
        }
    }
}

void Plug::loadFuse(){
    if(LoadFrom.is_open()){
        int maxcurrent, id, nextid;
        LoadFrom >> maxcurrent >> id >> nextid;
        try{
            NextFuse = new Fuse(maxcurrent, "Bezpiecznik", this, id, nextid);
            if(NextFuse == NULL)
                throw "Nie udalo sie przydzielic pamieci dla bezpiecznika.";
        }
        catch(string w){
                cout << w << endl;
        }
    }
}
