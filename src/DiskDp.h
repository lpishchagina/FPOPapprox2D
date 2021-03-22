#ifndef DISKDP_H
#define DISKDP_H

#include <vector>

class DiskDp{
private:
  std::vector<double> center;                           // coordinates of center
  double radius;
  unsigned int p;
  
public:
  DiskDp();
  DiskDp(unsigned int dim);
  DiskDp(unsigned int dim, std::vector<double> c, double r);
  
  unsigned int get_p();
  double get_radius();
  std::vector<double> get_center();
  bool IsEmpty_disk();

};

#endif //DISKDP_H