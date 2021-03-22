#include "DiskDp.h"
#include "math.h"
#include<iostream>
#include<vector>

using namespace std;

DiskDp::DiskDp(){
  p = 0;
  radius = 0;
  center = vector<double>(0,0);
}

DiskDp::DiskDp(unsigned int dim){
  p = dim;
  radius = 0;
  center = vector<double>(dim,0);
}

DiskDp::DiskDp(unsigned int dim, std::vector<double> c, double r){
  p = dim;
  radius = r;
  center = c;  
}

unsigned int DiskDp::get_p() {return p;}

double DiskDp::get_radius() {return radius;}

std::vector<double> DiskDp::get_center(){return center;}

bool DiskDp::IsEmpty_disk(){ if (radius == 0) {return true;} else {return false;}}





