#include <iostream>
#include <vector>
#include "math.h"
#include "GausseCostDp.h"
using namespace std;
#include <Rcpp.h>
using namespace Rcpp;

//##############################constructor#####################################//
GausseCostDp::GausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen){
  double sum_mu2 = 0;
  double sum_dif_x2 = 0;
  coef = t - i + 1;
  mi_1_p = mi_1pen;
  for (unsigned int k = 0; k < dim; k++){
    mu[k] = (st[k] - si_1[k])/coef;
    sum_mu2 = sum_mu2 + mu[k]*mu[k];
    sum_dif_x2 = sum_dif_x2 + (st[dim+k] - si_1[dim+k]);
  }
  coef_Var = sum_dif_x2 - coef * sum_mu2;
}

//##############################accessory#######################################//
unsigned int GausseCostDp::get_coef() const{return coef;}
double GausseCostDp::get_coef_Var() const{return coef_Var;}
double GausseCostDp::get_mi_1_p() const{return mi_1_p;}
std::vector<double> GausseCostDp::get_mu(){return mu;}

//#################################get_min######################################//
double GausseCostDp::get_min(){ return(coef_Var + mi_1_p);}// q_it is a paraboloid => min{q_it} = coef_Var + mi_1_p

//##################################End#########################################//
