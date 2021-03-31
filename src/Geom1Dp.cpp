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

//constructor, copy and destructor**********************************************
/*
Geom1Dp::Geom1Dp(unsigned  int dim){
  Rcpp::Rcout<<"constr geom1=> ";
  p = dim;
  label_t = 0;
  rect_t = RectDp(p);
  Rcpp::Rcout<<" <= constr geom1 "<<std::endl;
}
*/
Geom1Dp::Geom1Dp(unsigned  int dim, unsigned  int t){
  p = dim;
  label_t = t;
  rect_t = RectDp(p);
}

Geom1Dp::Geom1Dp(const Geom1Dp & geom1){
  Rcpp::Rcout<<"copy geom1=>"<<std::endl;
  p = geom1.p;
  label_t = geom1.label_t;
  rect_t = geom1.rect_t;
//  Rcpp::Rcout<<"rect_t.get_coordinates()[0][0]="<<rect_t.get_coordinates()[0][0]<<std::endl;
  Rcpp::Rcout<<"<=copy geom1"<<std::endl;
}

/*
Geom1Dp Geom1Dp::operator=(const Geom1Dp& geom1){
  Rcpp::Rcout<<"oper = geom => "<<std::endl;
  p = geom1.p;
  label_t = geom1.label_t;
  rect_t = geom1.rect_t;
  Rcpp::Rcout<<"<= oper = geom "<<std::endl;
  return *this;
}

*/

//Geom1Dp::~Geom1Dp(){Rcpp::Rcout<<"destr geom1=>"<<std::endl; CleanGeometry(); Rcpp::Rcout<<"<=destr geom1"<<std::endl;}


//accessory*********************************************************************
unsigned int Geom1Dp::get_p(){return p;}

unsigned int Geom1Dp::get_label_t(){return label_t;}

RectDp Geom1Dp::get_rect_t(){return rect_t;}

std::list<DiskDp> Geom1Dp::get_disks_t_1(){
  std::list<DiskDp> list_NULL;
  list_NULL.clear();
  return list_NULL;
}

//CleanGeometry*****************************************************************
//void Geom1Dp::CleanGeometry() {}

//EmptyGeometry*****************************************************************
bool Geom1Dp::EmptyGeometry(){return rect_t.IsEmpty_rect();}

//InitialGeometry***************************************************************
void Geom1Dp::InitialGeometry(unsigned int dim, unsigned int t, std::list<DiskDp> disks){
  p = dim; 
  label_t = t;
  rect_t.InitialRectDp(p);
}

//UpdateGeometry****************************************************************
void Geom1Dp::UpdateGeometry(DiskDp disk_t){rect_t.Intersection_disk(disk_t);}

//******************************************************************************
