#ifndef DISKDP_H
#define DISKDP_H

/*
 Class DiskDp
 -------------------------------------------------------------------------------
 Description: 
  Disk in p-dimension. 
 
 Parameters:
  "center" - vector  of  the disk  center coordinates;
  "radius" - value of the disk radius;
  "p" - dimension.
 -------------------------------------------------------------------------------
 */
class DiskDp{
private:
  unsigned int p;
  double radius;
  double* center;
  
public:
  DiskDp(){};
  DiskDp(unsigned int dim);
  DiskDp(unsigned int dim, double* c, double r);
  DiskDp(const DiskDp &disk);
  ~DiskDp();
  
  void InitialDiskDp(unsigned int dim, double* c, double r);
  
  unsigned int  get_p();
  double get_radius();
  double* get_center();
};
#endif //DISKDP_H
//------------------------------------------------------------------------------