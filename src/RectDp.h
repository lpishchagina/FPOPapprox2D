#ifndef RECTDP_H
#define RECTDP_H

#include "math.h"
#include "DiskDp.h"

//ATTENTION: Currently, the functions "exclusion" and "intersection" are implemented only for the case dim = 2.
//These functions need to be improved for the case dim != 2 

//################################################################################//
//############################### Class RectDp #####################################//
class RectDp{
public:
  //------------------------------constructor-------------------------------------//
  RectDp();
  RectDp(unsigned dim);
  ~RectDp();
  RectDp(double** coords);
  
  //------------------------------accessory---------------------------------------//
  double** get_coordinates();
  unsigned int get_p();
  //--------------------------------min max---------------------------------------//
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  //-------------------difference and intersection--------------------------------//
  bool IsEmpty_rect();
  void exclusionD2(DiskDp disk);
  void intersectionD2(DiskDp disk);
private:
  double** coordinates;                        //matrix of coordinates x dim x 2,each xi =(xi0,xi1)  i = 0, dim-1
  unsigned int p;
};
//############################# End Class RectDp ###################################//
#endif //RECTDP_H