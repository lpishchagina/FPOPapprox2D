#include "DiskDp.h"
#include "Geom3Dp.h"

#include <iostream>
#include <iterator>
#include <list>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//------------------------------------------------------------------------------
Geom3Dp::Geom3Dp(){
  p = 0;
  label_t = 0;
  disks_t_1.clear();
}

Geom3Dp::Geom3Dp(unsigned  int dim, unsigned  int t){
  p = dim;
  label_t = t;
  disks_t_1.clear();
}
//------------------------------------------------------------------------------
unsigned int Geom3Dp::get_p(){return p;}
int Geom3Dp::get_label_t(){return label_t;}
std::list<DiskDp> Geom3Dp::get_disks_t_1(){return disks_t_1;}

double Geom3Dp::Dist(std::vector<double> a, std::vector<double> b){
  unsigned  int dim = a.size();
  double dist = 0;
  for (unsigned int k = 0; k < dim; k++){dist = dist + (a[k] - b[k])*(a[k] - b[k]);}
  dist = sqrt(dist);
  return dist;
}
//------------------------------------------------------------------------------
void Geom3Dp::InitialGeometry(std::list<DiskDp> disks){disks_t_1 = disks;}
//------------------------------------------------------------------------------
void Geom3Dp::UpdateGeometry(DiskDp disk_t){
  std::list<DiskDp>::iterator iter;
  //Remove disks
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    double dist = Dist(disk_t.get_center(), disk.get_center());
    if (dist >= (disk.get_radius() + disk_t.get_radius())){ iter = disks_t_1.erase(iter);--iter;}
    ++iter; 
  }
  //Exclusion
  iter = disks_t_1.begin();
  while( iter != disks_t_1.end()){
    DiskDp disk = *iter;
    double dist;
    dist = Dist(disk_t.get_center(), disk.get_center());
    if (dist <= (disk.get_radius() - disk_t.get_radius())){
      label_t = -1;
      iter = disks_t_1.end();
    }
    else{++iter;}
  }
} 
//------------------------------------------------------------------------------
bool Geom3Dp::EmptyGeometry(){ if (label_t == -1) {return true;} else {return false;}}
//------------------------------------------------------------------------------
