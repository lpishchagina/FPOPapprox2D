#include "RectDp.h"
#include "DiskDp.h"
#include "math.h"
#include<iostream>

using namespace std;

//ATTENTION: Currently, the functions "exclusion" and "intersection" are implemented only for the case dim = 2.
//These functions need to be improved for the case dim != 2 


RectDp::RectDp(){
  p = 0;
  coordinates = NULL;
}

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
  coordinates = coords;
}

RectDp::~RectDp(){
  for(unsigned int i = 0; i < p; i++) {delete(coordinates[i]);}
  delete [] coordinates;
  coordinates = NULL;
}

double** RectDp::get_coordinates(){return coordinates;}
unsigned int RectDp::get_p(){return p;}

double RectDp::min_ab(double a, double b){if (a < b) {return a;} else {return b;}}
double RectDp::max_ab(double a, double b){if (a > b) {return a;} else {return b;}}

bool RectDp::IsEmpty_rect(){
  for (unsigned int k = 0; k < p; k++){
    if (coordinates[k][0] >= coordinates[k][1] || coordinates[k][0] >= coordinates[k][1]){return true;}
  }
  return false;
}

std::vector<double> RectDp::point_max(DiskDp disk){
  std::vector<double> point;
  std::vector<double> c = disk.get_center();
  for (unsigned int k = 0; k < p; k++){
    if (c[k] <= coordinates[k][0]) {point.push_back(coordinates[k][1]);}
    else if (c[k] >= coordinates[k][1]) {point.push_back(coordinates[k][0]);}
    else { 
      if ((c[k] - coordinates[k][1])*(c[k] - coordinates[k][1]) >= (c[k] - coordinates[k][0])*(c[k] - coordinates[k][0])) {point.push_back(coordinates[k][1]);}
      else{point.push_back(coordinates[k][0]);} 
    }
  }
  return point;
}

std::vector<double> RectDp::point_min(DiskDp disk){
  std::vector<double> point;
  std::vector<double> c = disk.get_center();
  for (unsigned int k = 0; k < p; k++){
    if (c[k] <= coordinates[k][0]) {point.push_back(coordinates[k][0]);}
    else if (c[k] >= coordinates[k][1]) {point.push_back(coordinates[k][1]);}
    else { 
      if ((c[k] - coordinates[k][1])*(c[k] - coordinates[k][1]) >= (c[k] - coordinates[k][0])*(c[k] - coordinates[k][0])) {point.push_back(coordinates[k][0]);}
      else{point.push_back(coordinates[k][1]);} 
    }
  }
  return point;
}

void RectDp::Intersection_disk(DiskDp disk){
  double r = disk.get_radius();        
  std::vector<double> c = disk.get_center();            //parameters of the disk
  bool fl = true;                                       // empty set
  //-points_min_max-------------------------------------------------------------
  std::vector<double> pnt_t = point_max(disk);
  std::vector<double> pnt_b = point_min(disk);
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
          sum_dif_b = sum_dif_b + (pnt_b[j] - c[j]) * (pnt_b[j] - c[j]);
          sum_dif_t = sum_dif_t + (pnt_t[j] - c[j]) * (pnt_t[j] - c[j]);
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
      if (fl) {coordinates[k][0] = coordinates[k][1];}  //empty set
    }//else
  }
}

void RectDp::Exclusion_disk(DiskDp disk){
  double r = disk.get_radius();        
  std::vector<double> c = disk.get_center(); 
  
  std::vector<double> pnt_t = point_max(disk);
  std::vector<double> pnt_b = point_min(disk);
  
  for (unsigned int k = 0; k < p; k ++){
    double sum_dif_b = 0;
    double sum_dif_t = 0;
    for (unsigned int j = 0; j < p; j++){
      if (j != k){
        sum_dif_b = sum_dif_b + (pnt_b[j] - c[j]) * (pnt_b[j] - c[j]);
        sum_dif_t = sum_dif_t + (pnt_t[j] - c[j]) * (pnt_t[j] - c[j]);
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
      coordinates[k][1]  = min_ab(coordinates[k][1], max_ab(t1, t1));            
    }
  }
}

