#include "DiskDp.h"
#include "Geom3Dp.h"

#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//constructor-------------------------------------------------------------------
Geom3Dp::Geom3Dp(unsigned  int dim){
  p = dim;
  label_t = 0;
  disks_t_1.clear();
  fl_empty = true;
  Rcpp::Rcout<<"constr geom"<<std::endl;
}
Geom3Dp::Geom3Dp(unsigned  int dim, unsigned  int t){
  p = dim;
  label_t = t;
  disks_t_1.clear();
  fl_empty = false;
}

Geom3Dp::Geom3Dp(const Geom3Dp & geom3){
  p = geom3.p;
  label_t = geom3.label_t;
  disks_t_1.clear();
  disks_t_1 = geom3.disks_t_1;
  fl_empty = geom3.fl_empty;
  
}

Geom3Dp::~Geom3Dp(){
  disks_t_1.clear();// enough or not ? 
  Rcpp::Rcout<<"destr geom"<<std::endl;
}

//accessory---------------------------------------------------------------------
unsigned int Geom3Dp::get_p(){return p;}

unsigned int Geom3Dp::get_label_t(){return label_t;}

bool Geom3Dp::get_fl_empty() {return fl_empty;}

std::list<DiskDp> Geom3Dp::get_disks_t_1(){return disks_t_1;}
//distance----------------------------------------------------------------------
double Geom3Dp::Dist(double* a, double*b){
  double dist = 0;
  for (unsigned int k = 0; k < p; k++){dist = dist + (a[k] - b[k])*(a[k] - b[k]);}
  return sqrt(dist);
}

//------------------------------------------------------------------------------
bool Geom3Dp::EmptyGeometry(){return fl_empty;}

//------------------------------------------------------------------------------
void Geom3Dp::InitialGeometry(unsigned  int dim, unsigned  int t, std::list<DiskDp> disks){
  p = dim;
  label_t = t;
  fl_empty = false;
  disks_t_1.clear();
  disks_t_1 = disks;
}
//------------------------------------------------------------------------------
void Geom3Dp::CleanGeometry(){disks_t_1.clear();}

//------------------------------------------------------------------------------
void Geom3Dp::UpdateGeometry(DiskDp disk_t){

  std::list<DiskDp>::iterator iter;
  double dist;
  //Remove disks
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    dist = Dist(disk_t.get_center(), disk.get_center());
    if (dist >= (disk.get_radius() + disk_t.get_radius())){ iter = disks_t_1.erase(iter);--iter;}
    ++iter; 
  }
  //Exclusion
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    dist = Dist(disk_t.get_center(), disk.get_center());
    if (dist <= (disk.get_radius() - disk_t.get_radius())){
      fl_empty = true;
      iter = disks_t_1.end();
    }
    else{++iter;}
  }
} 



