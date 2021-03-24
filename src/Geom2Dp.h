#ifndef GEOM2DP_H
#define GEOM2DP_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

//Class Geom2Dp
//------------------------------------------------------------------------------------------------------------------------
//Description of geometry "Geom2Dp": 
//Geometry for FPOP-Algorithm in 2-dimension. 
//Parameters of geometry: rectangle "rect t" - approximated set, "label_t" - moment of time, "disks_t_1" - list of disks(t-1)
//The updated geometry is a rectangle that approximates (the intersection of the rectangle and disk at the moment t) minus (list of disks(t-1)) .
//Check for emptiness - correct rectangle coordinates. 
//------------------------------------------------------------------------------------------------------------------------

class Geom2Dp{
private:
  unsigned int p;
  int label_t;                                 //time moment 
  RectDp rect_t;                                          //approx rectangle
  std::list<DiskDp> disks_t_1;                            //list of disks(t-1)
  
public:
  Geom2Dp();
  Geom2Dp(unsigned int dim, unsigned int t);
  unsigned int get_p();
  int get_label_t();
  Rect get_rect_t();
  std::list<DiskDp> get_disks_t_1();

  void InitialGeometry(std::list<DiskDp> disks);
  void UpdateGeometry(DiskDp disk_t);
  bool EmptyGeometry();
};
#endif //GEOM2DP_H
