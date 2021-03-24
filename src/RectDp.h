#ifndef RECTDP_H
#define RECTDP_H

#include "math.h"
#include "DiskDp.h"

//ATTENTION: Currently, the functions "exclusion" and "intersection" are implemented only for the case dim = 2.
//These functions need to be improved for the case dim != 2 

class RectDp{
private:
  double** coordinates;//matrix of coordinates x dim x 2,each xi =(xi0,xi1)  i = 0, p-1
  unsigned int p;
  
public:
  RectDp();
  RectDp(unsigned int dim);
  RectDp(unsigned int dim, double** coords);
  ~RectDp();
  
  double** get_coordinates();
  unsigned int get_p();
  
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  
  std::vector<double> point_min(DiskDp disk);
  std::vector<double> point_max(DiskDp disk);
  
  bool IsEmpty_rect();
  void Exclusion_disk(DiskDp disk);
  void Intersection_disk(DiskDp disk);
  
};

#endif //RECTDP_H