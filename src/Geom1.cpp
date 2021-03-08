#include "GausseCostDp.h"
#include "DiskDp.h"
#include "RectDp.h"
#include "Geom1.h"
#include <iostream>
#include <math.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;
//-------------------------------constructor------------------------------------//
Geom1::Geom1(){
  label_t = 0;
  rect_t = RectDp();
}
Geom1::Geom1(unsigned  int t){
  unsigned int dim = 2;
  label_t = t;
  rect_t = RectDp(dim);
}
//--------------------------------accessory-------------------------------------//
unsigned int Geom1::get_label_t(){return label_t;}
RectDp Geom1::get_rect_t(){return rect_t;}

std::list<DiskDp> Geom1::get_disks_t_1(){
  std::list<DiskDp> emptiness;
  emptiness.clear();
  return emptiness;}
//--------------------------------IsEmpty---------------------------------------//
bool Geom1::IsEmpty(){return rect_t.IsEmpty_rect();}

//------------------------------UpdateGeom--------------------------------------//
void Geom1::UpdateGeom(DiskDp disk){rect_t.intersectionD2(disk);}

//---------------------------------End------------------------------------------//