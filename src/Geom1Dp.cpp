#include "GausseCostDp.h"
#include "DiskDp.h"
#include "RectDp.h"
#include "Geom1Dp.h"

#include <math.h>
#include <iostream>
#include <list>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;
//constructor-------------------------------------------------------------------
Geom1Dp::Geom1Dp(unsigned  int dim, unsigned  int t){
  p = dim;
  label_t = t;
  rect_t = RectDp(p);
}
//accessory---------------------------------------------------------------------
unsigned int Geom1Dp::get_p(){return p;}

unsigned int Geom1Dp::get_label_t(){return label_t;}

RectDp Geom1Dp::get_rect_t(){return rect_t;}

std::list<DiskDp> Geom1Dp::get_disks_t_1(){
  std::list<DiskDp> list_NULL;
  list_NULL.clear();
  return list_NULL;
}
//------------------------------------------------------------------------------
void Geom1Dp::InitialGeometry(std::list<DiskDp> disks){}

void Geom1Dp::UpdateGeometry(DiskDp disk_t){rect_t.Intersection_disk(disk_t);}

bool Geom1Dp::EmptyGeometry(){return rect_t.IsEmpty_rect();}
//------------------------------------------------------------------------------
