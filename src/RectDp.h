#ifndef RECTDP_H
#define RECTDP_H

#include "math.h"
#include "DiskDp.h"

/*
 Class RectDp
 -------------------------------------------------------------------------------
 Description: 
 Rectangle in p-dimension. 
 
 Parameters:
 "coordinates" - the values of two constraints for each axis;
 "p" - dimension.
 -------------------------------------------------------------------------------
 */

class RectDp{
private:
  unsigned int p;
  double** coordinates;//matrix(px2) of constraints for x ,each xi =(xi0,xi1)  i = 0, p-1
  
public:
  RectDp(): p(0), coordinates(NULL){}
  RectDp(unsigned int dim);
  RectDp(unsigned int dim, double** coords);
  RectDp(const RectDp &rect);
  ~RectDp();
  
  double** get_coordinates();
  unsigned int get_p();
  
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  
  bool EmptyIntersection(DiskDp disk);

  bool IsEmpty_rect();
  void Exclusion_disk(DiskDp disk);
  void Intersection_disk(DiskDp disk);
};

#endif //RECTDP_H