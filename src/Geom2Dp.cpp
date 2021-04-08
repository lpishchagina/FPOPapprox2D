#include "DiskDp.h"
#include "RectDp.h"
#include "Geom2Dp.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
//#include <list>
#include <Rcpp.h>


using namespace Rcpp;
using namespace std;

//constructor copy**************************************************************
Geom2Dp::Geom2Dp(const Geom2Dp & geom2){
  p = geom2.p;
  label_t = geom2.label_t;
  rect_t = new RectDp(p);
  disks_t_1.clear();
  disks_t_1 = geom2.disks_t_1;
}
//destructor********************************************************************
Geom2Dp::~Geom2Dp(){delete rect_t;}

//accessory*********************************************************************
unsigned int Geom2Dp::get_p(){return p;}

unsigned int Geom2Dp::get_label_t(){return label_t;}

std::list<DiskDp> Geom2Dp::get_disks_t_1(){return disks_t_1;}

//CleanGeometry*****************************************************************
void Geom2Dp::CleanGeometry(){disks_t_1.clear();}

//EmptyGeometry*****************************************************************
bool Geom2Dp::EmptyGeometry(){return rect_t->IsEmpty_rect();}

//InitialGeometry***************************************************************
void Geom2Dp::InitialGeometry(unsigned int dim, unsigned int t, std::list<DiskDp> disks){
  label_t = t;
  disks_t_1.clear();
  disks_t_1 = disks;
}

//UpdateGeometry****************************************************************
void Geom2Dp::UpdateGeometry(DiskDp disk_t){
  //Intersection
  rect_t->Intersection_disk(disk_t);
  // Exclusions
  std::list<DiskDp>::iterator iter = disks_t_1.begin();
  while(iter != disks_t_1.end() && (!rect_t->IsEmpty_rect())){
    if (rect_t->EmptyIntersection(*iter)) {iter = disks_t_1.erase(iter);}//isn't intersection => Remove disks 
    else {
      rect_t->Exclusion_disk(*iter);
      ++iter;
    }
  }
}


