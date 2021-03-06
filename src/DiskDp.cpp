#include "DiskDp.h"
#include "math.h"

#include<iostream>
#include <Rcpp.h>

using namespace Rcpp;

using namespace std;
//constructor, copy and destructor**********************************************
DiskDp::DiskDp(unsigned int dim){
  p = dim;
  radius = 0;
  center = new double[p];
}

DiskDp::DiskDp(unsigned int dim, double* c, double r){
  p = dim;
  radius = r;
  center = new double[p];
  for (unsigned int i = 0; i < p; i++){center[i] = c[i];}
}

DiskDp::DiskDp(const DiskDp &disk){
  p = disk.p;
  radius = disk.radius;
  center = new double[p];
  for (unsigned int i = 0; i < p; i++){center[i] = disk.center[i];}
}

DiskDp::~DiskDp(){delete [] center; center = NULL;}

//accessory*********************************************************************
unsigned int  DiskDp::get_p()const{return p;}

double DiskDp::get_radius() const{return radius;}

double* DiskDp::get_center()const{return center;}
//InitialDiskDp*****************************************************************
void DiskDp::InitialDiskDp(unsigned int dim, double* c, double r){
  p = dim;
  radius = r;
  for (unsigned int i = 0; i < p; i++){center[i] = c[i];}
}
//******************************************************************************


