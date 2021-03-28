#include "RectDp.h"
#include "DiskDp.h"
#include "math.h"
#include<iostream>

using namespace std;
//constructor, copy and destructor**********************************************
RectDp::RectDp(unsigned int dim){
  p = dim;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i] = new double[2];
    coordinates[i][0] = -INFINITY;
    coordinates[i][1] = INFINITY;
  }
}

RectDp::RectDp(unsigned int dim, double** coords){
  p = dim;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i] = new double[2];
    coordinates[i][0] = coords[i][0];
    coordinates[i][1] = coords[i][1];
  }
}

RectDp::RectDp(const RectDp &rect){
  p = rect.p;
  coordinates = new double*[p]; 
  for(unsigned int i = 0; i < p; i++) {
    coordinates[i] = new double[2];
    coordinates[i][0] = rect.coordinates[i][0];
    coordinates[i][1] = rect.coordinates[i][1];
  }
}

RectDp::~RectDp(){
  for(unsigned int i = 0; i < p; i++) {delete(coordinates[i]);}
  delete [] coordinates;
  coordinates = NULL;
}
//accessory*********************************************************************
double** RectDp::get_coordinates(){return coordinates;}
unsigned int RectDp::get_p(){return p;}

double RectDp::min_ab(double a, double b){if (a < b) {return a;} else {return b;}}
double RectDp::max_ab(double a, double b){if (a > b) {return a;} else {return b;}}

//CleanRectDp*******************************************************************
void RectDp::CleanRectDp(){
  for(unsigned int i = 0; i < p; i++) {delete(coordinates[i]);}
  delete [] coordinates;
  coordinates = NULL;
}

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
  double* pnt = new double[p];
  for (unsigned int k = 0; k < p; k++){
    pnt[k] = c[k];
    if (c[k] <= coordinates[k][0]){ pnt[k] = coordinates[k][0];}
    if (c[k] >= coordinates[k][1]){ pnt[k] = coordinates[k][1];}
  }
  //discriminant----------------------------------------------------------------
  double* dx2 = new double[p];
  bool dx2kpos = true;
  for (unsigned int k = 0; k < p; k++){
    dx2[k] = 0;
    for (unsigned int j = 0; j < p; j++){if (j != k){dx2[k] = dx2[k] + (pnt[j] - c[j]) * (pnt[j] - c[j]);}}
    dx2[k] = r * r - dx2[k];
    dx2kpos = dx2kpos && (dx2[k] > 0);
  }
  //----------------------------------------------------------------------------
  if(!dx2kpos) {coordinates[0][0] =  coordinates[0][1];}
  else{
    for (unsigned int k = 0; k < p; k++){
      coordinates[k][0] = max_ab(coordinates[k][0], c[k] - sqrt(dx2[k])); 
      coordinates[k][1] = min_ab(coordinates[k][1], c[k] + sqrt(dx2[k]));
    }
  }
  //memory----------------------------------------------------------------------
  delete [] pnt;
  delete [] dx2;
  pnt = NULL;
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
  double* dx2 = new double[p];
  bool dx2_pos = true;
  for (unsigned int k = 0; k < p; k++){
    dx2[k] = 0;
    for (unsigned int j = 0; j < p; j++){if (j != k){dx2[k] = dx2[k] + (pnt_max[j] - c[j]) * (pnt_max[j] - c[j]);}}
    dx2[k] = r * r - dx2[k];
    dx2_pos = dx2_pos && (dx2[k] > 0);
  }
  if (dx2_pos){
    for(unsigned int k = 0; k < p; k++){
      coordinates[k][0] = max_ab(coordinates[k][0], c[k] + sqrt(dx2[k])); 
      coordinates[k][1] = min_ab(coordinates[k][1], c[k] - sqrt(dx2[k]));  
    }
  }
  //memory----------------------------------------------------------------------
  delete [] pnt_max;
  delete [] dx2;
  pnt_max = NULL;
  dx2 = NULL;
}
//******************************************************************************

