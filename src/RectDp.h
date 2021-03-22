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
  RectDp(unsigned dim);
  RectDp(unsigned dim, double** coords);
  ~RectDp();
  
  double** get_coordinates();
  unsigned int get_p();
  
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  
  bool IsEmpty_rect();
  void ExclusionD2(DiskDp disk);
  void IntersectionD2(DiskDp disk);

};

#endif //RECTDP_H