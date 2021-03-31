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


//constructor copy**************************************************************
Geom1Dp::Geom1Dp(const Geom1Dp & geom1){
   p = geom1.p;
   label_t = geom1.label_t;
   rect_t = new RectDp(p);
 }
 
//destructor******************************************************************** 
Geom1Dp::~Geom1Dp(){delete rect_t;}
 
//accessory*********************************************************************
unsigned int Geom1Dp::get_p(){return p;}
 
unsigned int Geom1Dp::get_label_t(){return label_t;}
 
std::list<DiskDp> Geom1Dp::get_disks_t_1(){
   std::list<DiskDp> list_NULL;
   list_NULL.clear();
   return list_NULL;
}
 
//EmptyGeometry*****************************************************************
bool Geom1Dp::EmptyGeometry(){return rect_t->IsEmpty_rect();}
 
//InitialGeometry***************************************************************
void Geom1Dp::InitialGeometry(unsigned int dim, unsigned int t, std::list<DiskDp> disks){label_t = t;}
 
//UpdateGeometry****************************************************************
void Geom1Dp::UpdateGeometry(DiskDp disk_t){rect_t->Intersection_disk(disk_t);}
 
//******************************************************************************

