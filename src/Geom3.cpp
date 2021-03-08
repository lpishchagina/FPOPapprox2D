#include "DiskDp.h"
#include "RectDp.h"
#include "Geom3.h"
#include <iostream>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//-----------------------------constructor--------------------------------------//
Geom3::Geom3(){
  label_t = 0;
  disks_t_1.clear();
}

Geom3::Geom3(unsigned  int t){
  label_t = t;
  disks_t_1.clear();
}

Geom3::Geom3(unsigned  int t,  std::list<DiskDp> disks){
  label_t = t;
  disks_t_1 = disks;
}

//----------------------------accessory-----------------------------------------//
unsigned int Geom3::get_label_t(){return label_t;}
std::list<DiskDp> Geom3::get_disks_t_1(){return disks_t_1;}

void Geom3::fillDisks(std::list<DiskDp> disks){
  disks_t_1.swap(disks);
}

//-----------------------remove_disk, add_disk----------------------------------//
void Geom3::remove_disk(DiskDp disk){
  std::list<DiskDp>::iterator it;
  it = disks_t_1.begin();
  while (it != disks_t_1.end()){
    DiskDp disk2 = *it;
    if ((disk.get_center() == disk2.get_center()) && (disk.get_radius() == disk2.get_radius())){
      disks_t_1.erase(it);
      it = disks_t_1.end();
    }
    else{++it;}
  }
}

void Geom3::add_disk(DiskDp disk){
  disks_t_1.push_back(disk);
}


//--------------------------------IsEmpty---------------------------------------//
bool Geom3::IsEmpty(){
 // if (disks_t_1.size() == 0){return true;} //or {return false;}
 // else {return false;}
 return false;
}
//-----------------------------UpdateGeom---------------------------------------//
void Geom3::UpdateGeom(DiskDp disk){
  std::list<DiskDp>::iterator it3;
  it3 = disks_t_1.begin();
  while( it3 != disks_t_1.end()){// delete disks sans interesection
    DiskDp disk2 = *it3;
    double d = disk.dist(disk2);
    if (d >= disk.get_radius() + disk2.get_radius()){
      remove_disk(disk2); 
      --it3;
    }
    ++it3;
  }
}
//---------------------------------End------------------------------------------//
