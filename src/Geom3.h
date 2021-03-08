#ifndef GEOM3_H
#define GEOM3_H

#include <iostream>
#include <vector>
#include <list>

#include "DiskDp.h"
#include "RectDp.h"
#include "GausseCostDp.h"

//Description of geometry "Geom3": 
//Geometry for FPOP-Algorithm in 2-dimension. 
//Parameters of geometry:"label_t" - moment of time, "disks_t_1" - list of disks(t-1)
//The updated geometry is a disk that approximates (disk at the moment t) minus (list of disks(t-1)) .
//Check for emptiness - the distance between the centers of the disks. 

//##############################################################################//
//############################### Class Geom3 ##################################//
class Geom3{
public:
  //------------------------------constructor-----------------------------------//
  Geom3();
  Geom3(unsigned int t);
  Geom3(unsigned int t, std::list<DiskDp> disks);
  //------------------------------accessory-------------------------------------//
  unsigned int get_label_t();
  std::list<DiskDp> get_disks_t_1();
  void remove_disk(DiskDp disk_t);
  void add_disk(DiskDp disk);
  void fillDisks(std::list<DiskDp> disks);
  bool IsEmpty();                                        //check for emptiness of an approximated set 
  
  void UpdateGeom(DiskDp disk);
private:
  unsigned int label_t;                                 //time moment 
  std::list<DiskDp> disks_t_1;                            //list of disks(t-1)
};
//############################# End Class Geom3 ################################//
#endif //GEOM3_H
