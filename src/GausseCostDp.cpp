#include "GausseCostDp.h"

#include <iostream>
#include "math.h"
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;
//constructor, copy and destructor**********************************************
GausseCostDp::GausseCostDp(unsigned int dim){
  coef = 0;
  mi_1_p = 0;
  coef_Var = 0;
  mu = new double[dim];
}

GausseCostDp::GausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen){
  coef = t - i + 1;
  mi_1_p = mi_1pen;
  mu = new double[dim];
  
  double sum_mu2 = 0;
  double sum_dif_x2 = 0;
  
  for (unsigned int k = 0; k < dim; k++){
    mu[k] = (st[k] - si_1[k])/coef;
    
    sum_mu2 = sum_mu2 + mu[k] * mu[k];
    sum_dif_x2 = sum_dif_x2 + (st[dim + k] - si_1[dim + k]);
  }
  coef_Var = sum_dif_x2 - coef * sum_mu2;
}

GausseCostDp::GausseCostDp(const GausseCostDp &cost){
  p = cost.p;
  coef = cost.coef;
  mi_1_p = cost.mi_1_p;
  coef_Var =cost.coef_Var;
  mu = new double[p];
  for (unsigned int k = 0; k < p; k++){mu[k] = cost.mu[k];}
}

GausseCostDp::~GausseCostDp(){delete [] mu; mu = NULL;Rcpp::Rcout<<"--destr cost"<< std::endl;}

//accessory*********************************************************************
void GausseCostDp::InitialGausseCostDp(unsigned int dim, unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen){
  coef = t - i + 1;
  mi_1_p = mi_1pen;
  
  double sum_mu2 = 0;
  double sum_dif_x2 = 0;
  
  for (unsigned int k = 0; k < dim; k++){
    mu[k] = (st[k] - si_1[k])/coef;
    
    sum_mu2 = sum_mu2 + mu[k] * mu[k];
    sum_dif_x2 = sum_dif_x2 + (st[dim + k] - si_1[dim + k]);
  }
  coef_Var = sum_dif_x2 - coef * sum_mu2;
}

unsigned int GausseCostDp::get_p() const{return p;}

unsigned int GausseCostDp::get_coef() const{return coef;}

double GausseCostDp::get_coef_Var() const{return coef_Var;}

double GausseCostDp::get_mi_1_p() const{return mi_1_p;}

double* GausseCostDp::get_mu(){return mu;}

double GausseCostDp::get_min(){ return(coef_Var + mi_1_p);}
//******************************************************************************

