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
 "rect_t" -  pointer to rectangle (approximated set);

 The updated geometry  is a rectangle that approximates the intersection of the rectangle and disk.
 
 Check for emptiness - the correctness of the  rectangle coordinates. 
 --------------------------------------------------------------------------------
 */
class Geom1Dp{
private:
  unsigned int p;
  unsigned int label_t; 
  RectDp* rect_t;   
  
  
public:
  Geom1Dp(): p(0), label_t(0), rect_t(0){}
  Geom1Dp(unsigned  int dim): p(dim), label_t(0), rect_t(new RectDp(dim)){}
  Geom1Dp(unsigned int dim, unsigned int t): p(dim), label_t(t), rect_t(new RectDp(dim)){}
  Geom1Dp(const Geom1Dp & geom1);
  ~Geom1Dp();
  
  unsigned int get_p() const;
  unsigned int get_label_t() const;
  std::list<DiskDp> get_disks_t_1() const;
  
  void CleanGeometry(){};
  bool EmptyGeometry();
  void InitialGeometry(unsigned int dim, unsigned int t, const std::list<DiskDp> &disks);
  void UpdateGeometry(const DiskDp &disk_t);
};
#endif //GEOM1DP_H
//------------------------------------------------------------------------------