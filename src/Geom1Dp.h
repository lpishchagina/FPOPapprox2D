#ifndef GEOM1DP_H
#define GEOM1DP_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

//Class Geom1Dp
//-----------------------------------------------------------------------------------------------
//Description of geometry "Geom1Dp": 
//Geometry for FPOP-Algorithm in p-dimension. 
//Parameters of geometry: rectangle "rect t" - approximated set, "label_t" - moment of time
//The updated geometry is a rectangle that approximates the intersection of the rectangle and disK.
//Check for emptiness - correct rectangle coordinates. 
//-----------------------------------------------------------------------------------------------
class Geom1Dp{
private:
  unsigned int p;
  int label_t; //time moment 
  RectDp rect_t;          //approx rectangle
  
public:
  Geom1Dp();
  Geom1Dp(unsigned int dim, unsigned int t);
  
  unsigned int get_p();
  int get_label_t();
  RectDp get_rect_t();
  std::list<DiskDp> get_disks_t_1();
  
  void InitialGeometry(std::list<DiskDp> disks);
  void UpdateGeometry(DiskDp disk_t);
  bool EmptyGeometry();
};
#endif //GEOM1DP_H
