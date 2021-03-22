#ifndef GEOM3DP_H
#define GEOM3DP_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>

#include "DiskDp.h"
#include "GausseCostDp.h"

//Class Geom3Dp
//------------------------------------------------------------------------------
//Description of geometry "Geom3": 
//Geometry for FPOP-Algorithm in 2-dimension. 
//Parameters of geometry:"label_t" - moment of time, "disks_t_1" - list of disks(t-1)
//The updated geometry is a disk that approximates (disk at the moment t) minus (list of disks(t-1)) .
//Check for emptiness - the distance between the centers of the disks. 
//------------------------------------------------------------------------------
class Geom3Dp{
private:
  int label_t;       //time moment 
  std::list<DiskDp> disks_t_1;  //list of disks(t-1)
  unsigned int p;
  
public:
  Geom3Dp();
  Geom3Dp(unsigned int dim, unsigned int t);
  unsigned int get_p();
  int get_label_t();
  std::list<DiskDp> get_disks_t_1();
  
  double Dist(std::vector<double> a, std::vector<double> b);
  
  void InitialGeometry(std::list<DiskDp> disks);
  void UpdateGeometry(DiskDp disk_t);
  bool EmptyGeometry();
};
#endif //GEOM3DP_H