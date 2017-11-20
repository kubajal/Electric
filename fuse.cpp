#include "fuse.h"
#include "plug.h"
#include "powerstrip.h"
#include "fuse.h"
#include "device.h"

Plug *Fuse::addNewPlug(){
    Plug *p = new Plug("Wtyczka", this, *AvailablePlugID.begin());
    p->Previous = this;
    return p;
}

void Fuse::generateRandomDevice(){
    if(Next != NULL)
        Next->generateRandomDevice();
}

Fuse::Fuse(int mc, string n, Plug* p, int id, int nextid) : ElectricDevice(){
    Previous = p;
    MaximumCurrent = mc;
    Next = new Plug("Wtyczka", this, nextid);
    Next->Previous = this;
    Name = n;
    FuseID = id;
    set<int>::iterator it = AvailableFuseID.find(FuseID);
    AvailableFuseID.erase(it);
    FreePlugs.erase(Previous->PlugID);
    TimesFused = 0;
}

Fuse::~Fuse(){
    delete Next;
    Next = NULL;
    FreePlugs.insert(Previous->PlugID);
    Previous = NULL;
    AvailableFuseID.insert(FuseID);
    FuseID = 0;
}

void Fuse::overcurrent(){
    if(Next != NULL)
        Next->overcurrent();
}

void Fuse::print(int n){
    space(n);
    cout << Name << " " << FuseID << ", max prad:" << MaximumCurrent << ", prad:" << Current << ", przeciazen:" << TimesFused;
    if(Current > MaximumCurrent){
        TimesFused++;
        cout << ", ZWARCIE";
    }

    cout << endl;
    if(Next != NULL)
        Next->print(n+1);
}

Plug *Fuse::findID(int x){
    if(Next != NULL)
        return Next->findID(x);
}

void Fuse::update(int c){
    Current += c;
    if(Previous != NULL)
        Previous->update(c);
}

void Fuse::DFS(){
    if(MaximumCurrent < Current){
        Next->overcurrent();
    }
    else if(Next != NULL)
        Next->DFS();

}

void Fuse::save(){
    SaveTo << "f" << endl << Previous->PlugID << endl << MaximumCurrent << endl << FuseID << endl << Next->PlugID << endl;
    if(Next != NULL)
        Next->save();
}
