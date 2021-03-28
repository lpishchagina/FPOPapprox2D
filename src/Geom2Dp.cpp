#include "DiskDp.h"
#include "RectDp.h"
#include "Geom2Dp.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <math.h>
//#include <list>
#include <Rcpp.h>


using namespace Rcpp;
using namespace std;
//constructor-------------------------------------------------------------------
Geom2Dp::Geom2Dp(unsigned int dim){
  p = dim;
  label_t = 0;
  rect_t = RectDp(p);
  disks_t_1.clear();
}

Geom2Dp::Geom2Dp(unsigned int dim, unsigned int t){
  p = dim;
  label_t = t;
  rect_t = RectDp(p);
  disks_t_1.clear();
}
//accessory---------------------------------------------------------------------
unsigned int Geom2Dp::get_p(){return p;}

unsigned int Geom2Dp::get_label_t(){return label_t;}

RectDp Geom2Dp::get_rect_t(){return rect_t;}

std::list<DiskDp> Geom2Dp::get_disks_t_1(){return disks_t_1;}
//------------------------------------------------------------------------------
bool Geom2Dp::EmptyGeometry(){return rect_t.IsEmpty_rect();}
//------------------------------------------------------------------------------
void Geom2Dp::CleanGeometry(){
  //clean rect_t memory
  rect_t.CleanRectDp();
  //clean disk memory
  disks_t_1.clear();// 
}
//------------------------------------------------------------------------------
void Geom2Dp::InitialGeometry(unsigned int dim, unsigned int t,std::list<DiskDp> disks){
  p = dim;
  label_t = t;
  disks_t_1 = disks; 
  }
//------------------------------------------------------------------------------
void Geom2Dp::UpdateGeometry(DiskDp disk_t){
  //Intersection
  rect_t.Intersection_disk(disk_t);
  //Remove disks
  if(rect_t.IsEmpty_rect() == false){
    std::list<DiskDp>::iterator iter;
    iter = disks_t_1.begin();
    while( iter != disks_t_1.end()){
      DiskDp disk = *iter;
      RectDp rect = rect_t;
      rect.Intersection_disk(disk);
      if(rect.IsEmpty_rect()){iter = disks_t_1.erase(iter); --iter;}
      ++iter;
    }
    //Exclusion
    iter = disks_t_1.begin();
    while( iter != disks_t_1.end()){
      DiskDp disk = *iter;
      rect_t.Exclusion_disk(disk);
      if(rect_t.IsEmpty_rect()){iter = disks_t_1.end();}
      else{ ++iter;}
    }
  }
}
//------------------------------------------------------------------------------
