#ifndef GEOM1_H
#define GEOM1_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

//Description of geometry "Geom1": 
//Geometry for FPOP-Algorithm in 2-dimension. 
//Parameters of geometry: rectangle "rect t" - approximated set, "label_t" - moment of time
//The updated geometry is a rectangle that approximates the intersection of the rectangle and disK.
//Check for emptiness - correct rectangle coordinates. 

//############################### Class Geom1 #####################################//
class Geom1{
public:
  //------------------------------constructor-----------------------------------//
  Geom1();
  Geom1(unsigned int t);
  //------------------------------accessory-------------------------------------//
  unsigned int get_label_t();
  RectDp get_rect_t();
  std::list<DiskDp> get_disks_t_1();
  //---------------------------IsEmpty, UpdateGeom------------------------------// 
  void fillDisks(std::list<DiskDp>list_disks){};
  bool IsEmpty();         
  void UpdateGeom(DiskDp disk);                
private:
  unsigned int label_t;                                   //time moment 
  RectDp rect_t;                                          //approx rectangle
};
//############################# End Class Geom1 ##################################//
#endif //GEOM1_H
