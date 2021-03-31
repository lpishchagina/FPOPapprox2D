#include "RectDp.h"
#include "DiskDp.h"
#include "math.h"
#include<iostream>
#include <Rcpp.h>

using namespace Rcpp;

using namespace std;
//constructor, copy and destructor**********************************************
RectDp::RectDp(){
  p = 0;
  coordinates = nullptr; 
}

RectDp::RectDp(unsigned int dim){
  Rcpp::Rcout<<"consr rect=> ";
  p = dim;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {coordinates[i] = new double[2];}
  for (unsigned int i = 0; i < p; i++) {
    coordinates[i][0] = -INFINITY;
    coordinates[i][1] = INFINITY;
  }
  Rcpp::Rcout<<" <= constr rect"<<std::endl;
}

RectDp::RectDp(unsigned int dim, double** coords){
  p = dim;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {coordinates[i] = new double[2];}
  for (unsigned int i = 0; i < p; i++) {
    coordinates[i][0] = coords[i][0];
    coordinates[i][1] = coords[i][1];
  }
}

RectDp::RectDp(const RectDp &rect){
  Rcpp::Rcout<<"copy rect=> "<<std::endl;
  p = rect.p;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {coordinates[i] = new double[2];}
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i][0] = rect.coordinates[i][0];
    coordinates[i][1] = rect.coordinates[i][1];
  }
  Rcpp::Rcout<<" <= copy rect"<<std::endl;
}

/*
RectDp RectDp::operator=(const RectDp& rect){
  Rcpp::Rcout<<"oper = rect => "<<std::endl;
  for(unsigned int i = 0; i < p; i++) {delete [] coordinates[i];  Rcpp::Rcout<<"!!!!!i=>"<<i<< std::endl;}
  delete [] coordinates;
  p = rect.p;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {coordinates[i] = new double[2];}
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i][0] = rect.coordinates[i][0];
    coordinates[i][1] = rect.coordinates[i][1];
  }
  Rcpp::Rcout<<"<= oper = rect "<<std::endl;
  return *this;
}
*/

RectDp::~RectDp(){
  Rcpp::Rcout<<" destr rect=>";
  for(unsigned int i = 0; i < p; i++) {delete[]coordinates[i];  Rcpp::Rcout<<" i="<<i;}
  delete[]coordinates;
  coordinates = NULL;
  Rcpp::Rcout<<"<= destr rect";
}

//accessory*********************************************************************
double** RectDp::get_coordinates(){return coordinates;}
unsigned int RectDp::get_p(){return p;}

double RectDp::min_ab(double a, double b){if (a < b) {return a;} else {return b;}}
double RectDp::max_ab(double a, double b){if (a > b) {return a;} else {return b;}}

//InitialRectDp*****************************************************************

void RectDp::InitialRectDp(unsigned int dim){
  p = dim;
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i][0] = -INFINITY;
    coordinates[i][1] = INFINITY;
    Rcpp::Rcout<<" INIT coordinates[i]="<<coordinates[i][0]<< coordinates[i][1]<<std::endl;
  }
}
/*
//CleanRectDp*******************************************************************

void RectDp::CleanRectDp(){
  Rcpp::Rcout<<" clear rect=>"<<std::endl;
  for(unsigned int i = 0; i < p; i++) {  Rcpp::Rcout<<" i=>"<<i<<"p="<<p<<"coord i0= "<<coordinates[i][0]<<std::endl;delete [] coordinates[i];}
  Rcpp::Rcout<<" 1clear rect=>"<<std::endl;
  delete [] coordinates;
  Rcpp::Rcout<<" 2clear rect=>"<<std::endl;
  coordinates = NULL;
  Rcpp::Rcout<<" clear rect"<<std::endl;
}
*/
//IsEmpty_rect******************************************************************
bool RectDp::IsEmpty_rect(){
  for (unsigned int k = 0; k < p; k++){if (coordinates[k][0] >= coordinates[k][1]){return true;}}
  return false;
}

//Intersection_disk*************************************************************
void RectDp::Intersection_disk(DiskDp disk){
  double r = disk.get_radius();        
  double* c = disk.get_center();            
  //-point----------------------------------------------------------------------
  double* pnt_min = new double[p];
  for (unsigned int k = 0; k < p; k++){
    pnt_min[k] = c[k];
    if (c[k] <= coordinates[k][0]){ pnt_min[k] = coordinates[k][0];}
    if (c[k] >= coordinates[k][1]){ pnt_min[k] = coordinates[k][1];}
  }
  //discriminant----------------------------------------------------------------
  double* dx2 = new double[p];
  double dx2i = 1;
  unsigned int i = 0;
  while ((dx2i > 0)&&(i < p)){
    dx2i = 0;
    for (unsigned int j = 0; j < p; j++){if (j != i){dx2i = dx2i + (pnt_min[j] - c[j]) * (pnt_min[j] - c[j]);}}
    dx2i = r * r - dx2i;
    dx2[i] = dx2i;
    ++i;
  }
  //----------------------------------------------------------------------------
  if (i != p) {coordinates[0][0] =  coordinates[0][1];}
  else{
    for (unsigned int k = 0; k < p; k++){
      coordinates[k][0] = max_ab(coordinates[k][0], c[k] - sqrt(dx2[k])); 
      coordinates[k][1] = min_ab(coordinates[k][1], c[k] + sqrt(dx2[k]));
    }
  }
  //memory----------------------------------------------------------------------
  delete [] pnt_min;
  delete [] dx2;
  pnt_min = NULL;
  dx2 = NULL;
}

//Exclusion_disk****************************************************************
void RectDp::Exclusion_disk(DiskDp disk){
  double r = disk.get_radius();        
  double* c = disk.get_center(); 
  //-point_max------------------------------------------------------------------
  double* pnt_max = new double[p];
  for (unsigned int k = 0; k < p; k++){
    if (abs(c[k] - coordinates[k][1]) >= abs(c[k] - coordinates[k][0])) {pnt_max[k] = coordinates[k][1];}
    else{pnt_max[k] = coordinates[k][0];}
  }
  //discriminant----------------------------------------------------------------
  for (unsigned int k = 0; k < p; k++){
    double dx2 = 0;
    for (unsigned int j = 0; j < p; j++){if (j != k){dx2 = dx2 + (pnt_max[j] - c[j]) * (pnt_max[j] - c[j]);}}
    dx2 = r * r - dx2;
    if (dx2 > 0){
      if (pnt_max[k] == coordinates[k][0]){coordinates[k][1] = min_ab(coordinates[k][1], c[k] - sqrt(dx2));}
      else {coordinates[k][0] = max_ab(coordinates[k][0], c[k] + sqrt(dx2));}
    }
  }
  //memory----------------------------------------------------------------------
  delete [] pnt_max;
  pnt_max = NULL;
}
//******************************************************************************

