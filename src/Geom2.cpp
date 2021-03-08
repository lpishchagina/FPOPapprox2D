#include "DiskDp.h"
#include "RectDp.h"
#include "Geom2.h"
#include <iostream>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//-----------------------------constructor--------------------------------------//
Geom2::Geom2(){
  label_t = 0;
  rect_t = RectDp();
  disks_t_1.clear();
}

Geom2::Geom2(unsigned  int t){
  unsigned int dim = 2;
  label_t = t;
  rect_t = RectDp(dim);
  disks_t_1.clear();
}


Geom2::Geom2(unsigned  int t,  std::list<DiskDp> disks){
  unsigned int dim = 2;
  label_t = t;
  rect_t = RectDp(dim);
  disks_t_1 = disks;
}

//----------------------------accessory-----------------------------------------//
unsigned int Geom2::get_label_t(){return label_t;}
RectDp Geom2::get_rect_t(){return rect_t;}
std::list<DiskDp> Geom2::get_disks_t_1(){return disks_t_1;}

void Geom2::fillDisks(std::list<DiskDp> disks){
  disks_t_1.swap(disks);
}

//-----------------------remove_disk, add_disk----------------------------------//
void Geom2::remove_disk(DiskDp disk){
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

void Geom2::add_disk(DiskDp disk){
  disks_t_1.push_back(disk);
}

//--------------------------------IsEmpty---------------------------------------//
bool Geom2::IsEmpty(){return rect_t.IsEmpty_rect();}

//--------------intersection-rect_disk, exclusion_rect_disk---------------------//
void Geom2::intersection_rect_disk(DiskDp disk){rect_t.intersectionD2(disk);}

void Geom2::exclusion_rect_disk(DiskDp disk){rect_t.exclusionD2(disk);}

//-----------------------------UpdateGeom---------------------------------------//
void Geom2::UpdateGeom(DiskDp disk){
  rect_t.intersectionD2(disk);
  if (!IsEmpty()){
    std::list<DiskDp>::iterator it2;
    it2 = disks_t_1.begin();
    while( it2 != disks_t_1.end()){// delete disks sans intersection
      DiskDp disk = *it2;
      RectDp rect = rect_t;
      rect.intersectionD2(disk);
      if(rect.IsEmpty_rect()){
        remove_disk(disk); 
        --it2;
      }
      ++it2;
    }
    it2 = disks_t_1.begin();
    while(it2 != disks_t_1.end()){
      DiskDp disk = *it2;
      rect_t.exclusionD2(disk);
      if(IsEmpty()){it2 = disks_t_1.end();}
      else{++it2;}
    }
  }
}
//---------------------------------End------------------------------------------//
