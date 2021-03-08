#ifndef GEOM2_H
#define GEOM2_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

//Description of geometry "Geom2": 
//Geometry for FPOP-Algorithm in 2-dimension. 
//Parameters of geometry: rectangle "rect t" - approximated set, "label_t" - moment of time, "disks_t_1" - list of disks(t-1)
//The updated geometry is a rectangle that approximates (the intersection of the rectangle and disk at the moment t) minus (list of disks(t-1)) .
//Check for emptiness - correct rectangle coordinates. 

//##############################################################################//
//############################### Class Geom2 ##################################//
class Geom2{
public:
  //------------------------------constructor-----------------------------------//
  Geom2();
  Geom2(unsigned int t);
  Geom2(unsigned int t, std::list<DiskDp> disks);
  //------------------------------accessory-------------------------------------//
  unsigned int get_label_t();
  RectDp get_rect_t();
  std::list<DiskDp> get_disks_t_1();
  void remove_disk(DiskDp disk);
  void add_disk(DiskDp disk);
  
  void fillDisks(std::list<DiskDp>list_disks);
  bool IsEmpty();                                        //check for emptiness of an approximated set 
  void intersection_rect_disk(DiskDp disk);              //intersection approximation
  void exclusion_rect_disk(DiskDp disk);                 //exclusion approximation
  void UpdateGeom(DiskDp disk);
private:
  unsigned int label_t;                                 //time moment 
  RectDp rect_t;                                          //approx rectangle
  std::list<DiskDp> disks_t_1;                            //list of disks(t-1)
};
//############################# End Class Geom2 ################################//
#endif //GEOM2_H
