#ifndef GEOM3DP_H
#define GEOM3DP_H

#include <iostream>
#include <list>
#include <iterator>

#include "DiskDp.h"
#include "GausseCostDp.h"
/*
Class Geom3Dp
--------------------------------------------------------------------------------
Description of geometry "Geom3Dp": 
Geometry for FPOP-Algorithm in p-dimension. 
 
Geometry parameters:
  "p" - dimension;
  "label_t" - moment in time;
  "disks_t_1" - list of active disks at moment (t-1);
  "fl_empty"  - "false" if geometry exists, otherwise "true".
 
The updated geometry is the result of exclusion from the disk at time t of disks at time t-1.
 
Check for emptiness - the distance between the centers of the disks. 
--------------------------------------------------------------------------------
 */
class Geom3Dp{
private:
  unsigned int p;
  unsigned int label_t;           
  std::list<DiskDp> disks_t_1;    
  bool fl_empty;
  
public:
  Geom3Dp(){};
  Geom3Dp(unsigned  int dim): p(dim), label_t(0), fl_empty(false){}
  Geom3Dp(unsigned int dim, unsigned int t): p(dim), label_t(t), fl_empty(false){}
  Geom3Dp(const Geom3Dp & geom3);
  
  unsigned int get_p() const;
  unsigned int get_label_t()const;
  bool get_fl_empty()const;
  std::list<DiskDp> get_disks_t_1()const;

  double Dist(double* a, double* b);
  
  void CleanGeometry();
  bool EmptyGeometry();
  void InitialGeometry(unsigned int dim, unsigned int t, const std::list<DiskDp> &disks);
  void UpdateGeometry(const DiskDp &disk_t);
};
#endif //GEOM3DP_H
//------------------------------------------------------------------------------