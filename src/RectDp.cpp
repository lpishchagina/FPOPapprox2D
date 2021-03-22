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



//############################## intersection ####################################// 
//ATTENTION: Currently, the functions "exclusion" and "intersection" are implemented only for the case dim = 2.
//This function are implemented only for the case dim = 2.

void RectDp::IntersectionD2(DiskDp disk){
  double r = disk.get_radius();        
  std::vector<double> c = disk.get_center();            //parameters of the disk
  bool fl = true;                                       // empty set
  //----------------------approximation-----------------------------------------
  for (unsigned int k = 0; k < 2; k ++){
    if (c[k] >= coordinates[k][0] && c[k] <= coordinates[k][1]){
      fl = false; //boundary point is inside xk = [xk0,xk1]
      for (unsigned int j = 0; j < 2; j ++){
        if (j != k){
          coordinates[j][0] = max_ab(coordinates[j][0], c[j] - r);
          coordinates[j][1] = min_ab(coordinates[j][1], c[j] + r);
        }
      }
    }//if (c[k] >= coordinates[k][0] && c[k] <= coordinates[k][0])
    else{
      std::vector<double> diskr_4;// if  diskr_4 =< 0 - no intersection points, if  diskr_4 > 0 - two intersection points
      for (unsigned int j = 0; j < 2; j++){diskr_4[j] = r * r - (coordinates[k][j] - c[k]) * (coordinates[k][j] - c[k]);}
      std::vector<double> roots0 = {INFINITY,-INFINITY};  // intersection points
      std::vector<double> roots1 = {INFINITY,-INFINITY}; 
      if (diskr_4[0] > 0){
        fl = false;
        for (unsigned int j = 0; j < 2; j++){
          if (j != k) {
            roots0[0] = c[j] - sqrt(diskr_4[0]);
            roots0[1] = c[j] + sqrt(diskr_4[0]);
          } 
        }
      }//if (diskr_4[0] > 0)
      if (diskr_4[1] > 0){
        fl = false;
        for (int j = 0; j < 2; j++){
          if (j != k) {
            roots1[0] = c[j] - sqrt(diskr_4[1]);
            roots1[1] = c[j] + sqrt(diskr_4[1]);
          } 
        }
      }//if (diskr_4[1] > 0)
      if(!fl){
        for (unsigned int j = 0; j < 2; j ++){
          if (j != k){
            coordinates[j][0] = max_ab(coordinates[j][0], min_ab(roots0[0],roots1[0])); //xi0 = max{xi0, min{roots}}
            coordinates[j][1] = min_ab(coordinates[j][1], max_ab(roots0[1],roots1[1])); //xi1 = min{xi1, max{roots}
          }
        }
      }//if(!fl) intersection
      else{coordinates[k][0] = coordinates[k][1];} //empty set
    }//else
  }//for (unsigned int k = 0; k < 2; k ++)
}


//############################## exclusion ######################################//
void RectDp::ExclusionD2(DiskDp disk){
  double r = disk.get_radius();                         //parameters of the disk
  std::vector<double> c = disk.get_center();
  //----------------------approximation-----------------------------------------
  for (unsigned int k = 0; k < 2; k ++){
    std::vector<double> diskr_4;  //if diskr_4 =< 0 - no intersection points, if  diskr_4 > 0 - two intersection points
    for (unsigned int j = 0; j < 2; j++){diskr_4[j] = r * r - (coordinates[k][j] - c[k]) * (coordinates[k][j] - c[k]);}
    if(diskr_4[0] > 0 && diskr_4[1] > 0){
      std::vector<double> roots0 = {INFINITY,-INFINITY};  // intersection points
      std::vector<double> roots1 = {INFINITY,-INFINITY};
      for (unsigned int j = 0; j < 2; j++){
        if (j != k) {
          roots0[0] = c[j] - sqrt(diskr_4[0]);
          roots0[1] = c[j] + sqrt(diskr_4[0]);
          roots1[0] = c[j] - sqrt(diskr_4[1]);
          roots1[1] = c[j] + sqrt(diskr_4[1]);
        }
      }
      for (unsigned int j = 0; j < 2; j ++){
        if (j != k){
          coordinates[j][0] = max_ab(coordinates[j][0], min_ab(roots0[1],roots1[1])); //xi0 = max{xi0, min{roots}}
          coordinates[j][1] = min_ab(coordinates[j][1], max_ab(roots0[0],roots1[0])); //xi1 = min{xi1, max{roots}}
        }
      }
    }//if(diskr_4[0] > 0 && diskr_4[1] > 0)
  }//for (unsigned int k = 0; k < 2; k ++)
}  
//############################## End ###########################################//



