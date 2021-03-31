#include "OPDp.h"
#include "DiskDp.h"

#include "GausseCostDp.h"
#include "Geom3Dp.h"
#include "Geom2Dp.h"
#include "Geom1Dp.h"

#include "math.h"
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//' @title FPOPDp 
//'                                                                                                        
//' @description Detection changepoints using the Functional Pruning Optimal Partitioning method (FPOP) in p-variate time series in a p-variable time series of length n.                         
//'                                                                                                       
//' @param data is a matrix of data(p-rows x n-columns).                               
//' @param penalty is a value of penalty (a non-negative real number).                                        
//' @param type is a value defining the  type of geometry for FPOP-pruning: type=1: ("intersection" of sets), approximation - rectangle; type=2:("intersection" of sets)"minus"("union" of sets), approximation - rectangle; type=3: (last disk)"minus"("union" of sets), approximation - disk.       
//'                                                                                                          
//' @return a list of  elements  = (changepoints, means, globalCost).                    
//'  
//' \describe{
//' \item{\code{chpts}}{is the changepoint vector that gives the last index of each segment for the p-variate time series.}
//' \item{\code{means}}{is the list of successive means for the p-variate time series.}
//' \item{\code{globalCost}}{is a number equal to the global cost.}
//' }                                                                                                                                                                                 
//' 
//' @examples FPOPDp(data = data_genDp(p = 3, n = 100, chpts = 100, means = matrix(c (0, 0, 0), nrow = 3), noise = 1), penalty = 2*log(100), type = 2) 
// [[Rcpp::export]]
List FPOPDp(Rcpp::NumericMatrix data, double penalty, int type) {
  //----------stop--------------------------------------------------------------
  if(penalty < 0) {throw std::range_error("penalty should be a non-negative number");}
  if(type < 1 || type > 3)
  {throw std::range_error("type must be one of: 1, 2 or 3");}
  //----------------------------------------------------------------------------
  List res;
  bool test;
  test = false;
  
  if (type == 1){
    //test = true;//
    OPDp<Geom1Dp> X = OPDp<Geom1Dp>(data, penalty);
    X.algoFPOP(data, type, test);
    res["chpts"] = X.get_chpts();
    res["means"] = X.get_means();
    res["globalCost"] = X.get_globalCost();
  }
  
  if (type == 2){
    //test = true;//
    OPDp<Geom2Dp> Y = OPDp<Geom2Dp>(data, penalty);
    Y.algoFPOP(data, type, test);   
    res["chpts"] = Y.get_chpts();
    res["means"] = Y.get_means();
    res["globalCost"] = Y.get_globalCost();
  }
  
  if (type == 3){
    //test = true;//
    OPDp<Geom3Dp> Z = OPDp<Geom3Dp>(data, penalty);
    Z.algoFPOP(data, type, test);  
    res["chpts"] = Z.get_chpts();
    res["means"] = Z.get_means();
    res["globalCost"] = Z.get_globalCost();
  }
  return res;
}
