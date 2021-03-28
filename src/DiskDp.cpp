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
  Rcpp::Rcout<<"--constr disk--"<<std::endl;
}

DiskDp::DiskDp(unsigned int dim, double* c, double r){
  p = dim;
  radius = r;
  center = new double[p];
  for (unsigned int i = 0; i < p; i++){center[i] = c[i];}
  Rcpp::Rcout<<"--constr disk"<<std::endl;
}

DiskDp::DiskDp(const DiskDp &disk){
  p = disk.p;
  radius = disk.radius;
  center = new double[p];
  Rcpp::Rcout<<"--copy disk"<<std::endl;
  for (unsigned int i = 0; i < p; i++){center[i] = disk.center[i];}
  
}

DiskDp::~DiskDp(){delete [] center; center = NULL; Rcpp::Rcout<<"--destr disk"<< std::endl;}
//accessory*********************************************************************
unsigned int  DiskDp::get_p(){return p;}

double DiskDp::get_radius() {return radius;}

double* DiskDp::get_center(){return center;}

void DiskDp::InitialDiskDp(unsigned int dim, double* c, double r){
  p = dim;
  radius = r;
  for (unsigned int i = 0; i < p; i++){center[i] = c[i];}
}
//CleanDiskDp*******************************************************************

void DiskDp::CleanDiskDp(){
  radius = 0;
  delete [] center; center = NULL;
  Rcpp::Rcout<<"--Clean disk--"<<std::endl;
}
//******************************************************************************


