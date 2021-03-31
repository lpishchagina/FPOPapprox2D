#include "DiskDp.h"
#include "Geom3Dp.h"

#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//constructor copy**************r***********************************************
Geom3Dp::Geom3Dp(const Geom3Dp & geom3){
  p = geom3.p;
  label_t = geom3.label_t;
  disks_t_1.clear();
  disks_t_1 = geom3.disks_t_1;
  fl_empty = geom3.fl_empty;
}

//accessory*********************************************************************
unsigned int Geom3Dp::get_p(){return p;}

unsigned int Geom3Dp::get_label_t(){return label_t;}

bool Geom3Dp::get_fl_empty() {return fl_empty;}

std::list<DiskDp> Geom3Dp::get_disks_t_1(){return disks_t_1;}

//Dist**************************************************************************
double Geom3Dp::Dist(double* a, double*b){
  double dist = 0;
  for (unsigned int k = 0; k < p; k++){dist = dist + (a[k] - b[k])*(a[k] - b[k]);}
  return sqrt(dist);
}

//CleanGeometry*****************************************************************
void Geom3Dp::CleanGeometry(){disks_t_1.clear();}

//EmptyGeometry*****************************************************************
bool Geom3Dp::EmptyGeometry(){return fl_empty;}

//InitialGeometry***************************************************************
void Geom3Dp::InitialGeometry(unsigned  int dim, unsigned  int t, std::list<DiskDp> disks){
  label_t = t;
  fl_empty = false;
  disks_t_1.clear();
  disks_t_1 = disks;
}

//UpdateGeometry****************************************************************
void Geom3Dp::UpdateGeometry(DiskDp disk_t){
  std::list<DiskDp>::iterator iter;
  //Remove disks
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    if (Dist(disk_t.get_center(), disk.get_center()) >= (disk.get_radius() + disk_t.get_radius())){iter = disks_t_1.erase(iter);--iter;}
    ++iter; 
  }
  //Exclusion
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    if (Dist(disk_t.get_center(), disk.get_center()) <= (disk.get_radius() - disk_t.get_radius())){ 
      fl_empty = true;
      iter = disks_t_1.end();
    }
    else{++iter;}
  }
} 
//******************************************************************************


