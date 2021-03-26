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
  Geom3Dp(unsigned  int dim);
  Geom3Dp(unsigned int dim, unsigned int t);
  
  unsigned int get_p();
  unsigned int get_label_t();
  bool get_fl_empty();
  std::list<DiskDp> get_disks_t_1();
  
  
  double Dist(double* a, double* b);
  
  void InitialGeometry(unsigned int dim, unsigned int t,std::list<DiskDp> disks);
  void UpdateGeometry(DiskDp disk_t);
  bool EmptyGeometry();
};
#endif //GEOM3DP_H