#include "DiskDp.h"
#include "math.h"

#include<iostream>
#include <Rcpp.h>

using namespace Rcpp;

using namespace std;

DiskDp::DiskDp(unsigned int dim){
  radius = 0;
  center = new double[dim];
}

DiskDp::DiskDp(unsigned int dim, double* c, double r){
  center = new double[dim];
  radius = r;
  center = c;
}

void DiskDp::InitialDiskDp(double* c, double r){
  radius = r;
  center = c;
}

DiskDp::~DiskDp(){delete [] center; center = NULL;}

double DiskDp::get_radius() {return radius;}

double* DiskDp::get_center(){return center;}






