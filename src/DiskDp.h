#ifndef DISK2D_H
#define DISK2D_H

#include <vector>


//################################################################################//
//############################### Class DiskDp ###################################//
class DiskDp{
public:
  //-----------------------------constructor--------------------------------------//
  DiskDp(unsigned int dim);

  DiskDp(std::vector<double> c, double r);
  //-----------------------------accessory----------------------------------------//
  double get_radius();
  std::vector<double> get_center();
  bool IsEmpty_disk();
  double dist(DiskDp disk2);
private:
  std::vector<double> center;                           // coordinates of center
  double radius;
};
//############################ End Class DiskDp ##################################//

#endif //DISKDP_H