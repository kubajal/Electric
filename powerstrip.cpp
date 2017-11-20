#include "powerstrip.h"
#include "plug.h"
#include "powerstrip.h"
#include "fuse.h"
#include "device.h"

void PowerStrip::addNPlugs(int n){
    for(int i = 0; i < n; i++){
        Plug *newPlug = new Plug("Wtyczka", this, *AvailablePlugID.begin());
        newPlug->Previous = this;
        ListOfPlugs.push_back(newPlug);
    }
}

void PowerStrip::generateRandomDevice(){
    for(int i = 0; i < ListOfPlugs.size(); i++){
        if(ListOfPlugs[i] != NULL)
             ListOfPlugs[i]->generateRandomDevice();
    }
}

Plug *PowerStrip::findID(int x){
    for(int i = 0; i < ListOfPlugs.size(); i++){
        Plug *p = ListOfPlugs[i]->findID(x);
        if(p != NULL)
            return p;
    }
    return NULL;
}

void PowerStrip::print(int n){
    space(n);
    cout << Name << " " << PowerStripID << ", liczba gniazdek: " << ListOfPlugs.size() << endl;
    for(int i = 0; i < ListOfPlugs.size(); i++)
        ListOfPlugs[i]->print(n+1);
}

PowerStrip::PowerStrip(string n, int x, Plug* p, int id) : ElectricDevice(){
    Previous = p;
    Name = n;
    addNPlugs(x);
    PowerStripID = id;
    set<int>::iterator it = AvailablePSID.find(PowerStripID);
    AvailablePSID.erase(PowerStripID);
}

PowerStrip::PowerStrip(string n, int x, Plug* p, int id, vector<int> v) : ElectricDevice(){
    Previous = p;
    Name = n;
    PowerStripID = id;
    for(int i = 0; i < v.size(); i++){
        Plug *newPlug = new Plug("Wtyczka", this, v[i]);
        newPlug->Previous = this;
        ListOfPlugs.push_back(newPlug);
    }
    set<int>::iterator it = AvailablePSID.find(PowerStripID);
    AvailablePSID.erase(PowerStripID);
    FreePlugs.erase(Previous->PlugID);
}

PowerStrip::~PowerStrip(){
    for(int i = ListOfPlugs.size() - 1; i >= 0; i--){
        delete ListOfPlugs[i];
        ListOfPlugs.pop_back();
    }
    FreePlugs.insert(Previous->PlugID);
    Previous = NULL;
    AvailablePSID.insert(PowerStripID);
    PowerStripID = 0;
}

void PowerStrip::update(int c){
    Current += c;
    if(Previous != NULL)
       Previous->update(c);
}

void PowerStrip::DFS(){
    for(vector<Plug*>::iterator it = ListOfPlugs.begin(); it != ListOfPlugs.end(); it++)
        if(*it != NULL)
            (*it)->DFS();
}

void PowerStrip::overcurrent(){
    for(vector<Plug*>::iterator it = ListOfPlugs.begin(); it != ListOfPlugs.end(); it++)
        if(*it != NULL)
            (*it)->overcurrent();
}

void PowerStrip::save(){
    SaveTo << "p" << endl << Previous->PlugID << endl << ListOfPlugs.size() << endl << PowerStripID << endl;
    for(int i = 0; i < ListOfPlugs.size(); i++){
        SaveTo << ListOfPlugs[i]->PlugID << endl;
    }
    for(int i = 0; i < ListOfPlugs.size(); i++)
        ListOfPlugs[i]->save();
}
