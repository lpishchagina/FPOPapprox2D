#ifndef DISKDP_H
#define DISKDP_H

/*
 Class DiskDp
 -------------------------------------------------------------------------------
 Description: 
  Disk in p-dimension. 
 
 Parameters:
  "center" - vector  of  the disk  center coordinates;
  "radius" - value of the disk radius.
 -------------------------------------------------------------------------------
 */
class DiskDp{
private:
  double* center;                           
  double radius;
  
public:
  DiskDp(){};
  DiskDp(unsigned int dim);
  DiskDp(unsigned int dim, double* c, double r);
  
  ~DiskDp();
  
  void InitialDiskDp(double* c, double r);
  
  double get_radius();
  double* get_center();
};

#endif //DISKDP_H