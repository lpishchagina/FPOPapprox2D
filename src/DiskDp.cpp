#include "DiskDp.h"
#include "math.h"
#include<iostream>
#include<vector>

using namespace std;

//############################## constructor #####################################//
DiskDp::DiskDp(unsigned int dim): center(vector<double>(dim,0)), radius(0){}

DiskDp::DiskDp(std::vector<double> c, double r):center(c), radius(r){}

//############################## accessory #######################################//

double DiskDp::get_radius() {return radius;}
std::vector<double> DiskDp::get_center(){return center;}

bool DiskDp::IsEmpty_disk(){
  if (radius == 0) {return true;}
  else{return false;}
}
/*
void DiskDp::intersection(DiskDp disk){
  double r = disk.get_radius();
  std::vector<double> c = disk.get_center();
  double d = dist(center, c);
  if (d >= (radius + disk.get_radius())){radius = 0;}
}
*/
double DiskDp::dist(DiskDp disk2){
  std::vector<double> c = disk2.get_center();
  unsigned int dim = c.size();
  double d = 0;
  for(unsigned int i = 0; i < dim; i++){d = d + (center[i] - c[i])*(center[i] - c[i]);}
  d = sqrt(d);
  return d;
}

//################################## End #########################################//




