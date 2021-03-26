#ifndef GEOM1DP_H
#define GEOM1DP_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

/*
 Class Geom1Dp
 --------------------------------------------------------------------------------
 Description of geometry "Geom1Dp": 
 Geometry for FPOP-Algorithm in p-dimension. 
 
 Geometry parameters:
 "p" - dimension;
 "label_t" - moment in time;
 "rect_t" - rectangle, approximated set;

 The updated geometry  is a rectangle that approximates the intersection of the rectangle and disk.
 
 Check for emptiness - the correctness of the  rectangle coordinates. 
 --------------------------------------------------------------------------------
 */
class Geom1Dp{
private:
  unsigned int p;
  unsigned int label_t; 
  RectDp rect_t;         
  
public:
  Geom1Dp(){};
  Geom1Dp(unsigned  int dim);
  Geom1Dp(unsigned int dim, unsigned int t);
  
  unsigned int get_p();
  unsigned int get_label_t();
  RectDp get_rect_t();
  std::list<DiskDp> get_disks_t_1();
  
  void InitialGeometry(unsigned int dim, unsigned int t,std::list<DiskDp> disks);
  void UpdateGeometry(DiskDp disk_t);
  bool EmptyGeometry();
};
#endif //GEOM1DP_H
