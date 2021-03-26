#include "RectDp.h"
#include "DiskDp.h"
#include "math.h"
#include<iostream>

using namespace std;
//constructor and destructor----------------------------------------------------
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
  for(unsigned int i = 0; i < p; i++) {coordinates[i] = new double[2];}
  coordinates = coords;
}

RectDp::~RectDp(){
  for(unsigned int i = 0; i < p; i++) {delete(coordinates[i]);}
  delete [] coordinates;
  coordinates = NULL;
}
//accessory---------------------------------------------------------------------
void RectDp::InitialRectDp(double** coords){coordinates = coords;}

double** RectDp::get_coordinates(){return coordinates;}
unsigned int RectDp::get_p(){return p;}

double RectDp::min_ab(double a, double b){if (a < b) {return a;} else {return b;}}
double RectDp::max_ab(double a, double b){if (a > b) {return a;} else {return b;}}

//------------------------------------------------------------------------------
void RectDp::point_max_min(double* pnt_max, double* pnt_min, DiskDp disk){
  double* c = disk.get_center();
  for (unsigned int k = 0; k < p; k++){
    if (abs(c[k] - coordinates[k][1]) >= abs(c[k] - coordinates[k][0])) {
      pnt_max[k] = coordinates[k][1];    pnt_min[k] = coordinates[k][0]; 
    }
    else{pnt_max[k] = coordinates[k][0];  pnt_min[k] = coordinates[k][1];}
  }
}
//IsEmpty_rect------------------------------------------------------------------
bool RectDp::IsEmpty_rect(){
  for (unsigned int k = 0; k < p; k++){if (coordinates[k][0] >= coordinates[k][1]){return true;}}
  return false;
}
//Intersection_disk-------------------------------------------------------------
void RectDp::Intersection_disk(DiskDp disk){
  double r = disk.get_radius();        
  double* c = disk.get_center();            
  bool fl = true;                                                    //empty set
  //-points_min_max-------------------------------------------------------------
  double* pnt_max = new double[p];
  double* pnt_min = new double[p];
  point_max_min(pnt_max, pnt_min, disk);
  //----------------------------------------------------------------------------
  for (unsigned int k = 0; k < p; k ++){
    //--------------------------------------------------------------------------
    bool fl_ck = true;
    for (unsigned int j = 0; j < p; j++){if (j != k) { fl_ck = (fl_ck) && (c[j] >= coordinates[j][0]) && (c[j] <= coordinates[j][1]);}}
    if (fl_ck == true) { 
      coordinates[k][0] = max_ab(coordinates[k][0], c[k] - r);                
      coordinates[k][1] = min_ab(coordinates[k][1], c[k] + r);                        
      fl = false;  
    }
    else{
      //discriminant------------------------------------------------------------
      double sum_dif_b = 0;
      double sum_dif_t = 0;
      for (unsigned int j = 0; j < p; j++){
        if (j != k){
          sum_dif_b = sum_dif_b + (pnt_min[j] - c[j]) * (pnt_min[j] - c[j]);
          sum_dif_t = sum_dif_t + (pnt_max[j] - c[j]) * (pnt_max[j] - c[j]);
        }
      }
      double db_4 = r * r - sum_dif_b;
      double dt_4 = r * r - sum_dif_t;
      //------------------------------------------------------------------------
      if(db_4 > 0 || dt_4 > 0){ 
        double b1 = INFINITY;       //intersection points
        double t1 = INFINITY;
        double b2 = -INFINITY;
        double t2 = -INFINITY;
        if (db_4 > 0){
          b1 = c[k] - sqrt(db_4);
          b2 = c[k] + sqrt(db_4);
        }
        if (dt_4 > 0){
          t1 = c[k] - sqrt(dt_4);
          t2 = c[k] + sqrt(dt_4);
        }
        coordinates[k][0] = max_ab(coordinates[k][0], min_ab(b1, t1)); 
        coordinates[k][1] = min_ab(coordinates[k][1], max_ab(b2, t2));
        fl = false;
      }
    }
  }
  if (fl) {coordinates[0][0] = coordinates[0][1];}  //empty set
  //memory----------------------------------------------------------------------
  delete [] pnt_max;
  delete [] pnt_min;
  pnt_max  = NULL;
  pnt_min  = NULL;
}

//Exclusion_disk----------------------------------------------------------------
void RectDp::Exclusion_disk(DiskDp disk){
  double r = disk.get_radius();        
  double* c = disk.get_center(); 
  //-points_min_max-------------------------------------------------------------
  double* pnt_max = new double[p];
  double* pnt_min = new double[p];
  point_max_min(pnt_max, pnt_min, disk);
  //----------------------------------------------------------------------------
  for (unsigned int k = 0; k < p; k ++){
    double sum_dif_b = 0;
    double sum_dif_t = 0;
    for (unsigned int j = 0; j < p; j++){
      if (j != k){
        sum_dif_b = sum_dif_b + (pnt_min[j] - c[j]) * (pnt_min[j] - c[j]);
        sum_dif_t = sum_dif_t + (pnt_max[j] - c[j]) * (pnt_max[j] - c[j]);
      }
    }
    double db_4 = r * r - sum_dif_b;
    double dt_4 = r * r - sum_dif_t;
    
    if(db_4 > 0 && dt_4 > 0){ 
      double b1 = INFINITY;       //intersection points
      double t1 = INFINITY;
      double b2 = -INFINITY;
      double t2 = -INFINITY;
      b1 = c[k] - sqrt(db_4);
      b2 = c[k] + sqrt(db_4);
      t1 = c[k] - sqrt(dt_4);
      t2 = c[k] + sqrt(dt_4);
      
      coordinates[k][0]  = max_ab(coordinates[k][0], min_ab(b2, t2));  
      coordinates[k][1]  = min_ab(coordinates[k][1], max_ab(b1, t1));            
    }
  }
  //memory----------------------------------------------------------------------
  delete [] pnt_max;
  delete [] pnt_min;
  pnt_max  = NULL;
  pnt_min  = NULL;
}

