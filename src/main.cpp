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
//' @description Detecting changepoints using the functional pruning optimal partitioning method (fpop) in bivariate time series.                         
//'                                                                                                       
//' @param data is a matrix of data.                               
//' @param penalty is a value of penalty (a non-negative real number).                                        
//' @param type is a value defining the  type of pruning (1 = FPOP(intersection of sets, approximation - rectangle); 2 = FPOP(intersection of set \ union of set, approximation - rectangle); 3 = FPOP(intersection of set \ union of set, approximation -last disk)).       
//'                                                                                                          
//' @return a list of  elements  = (changepoints, means, globalCost).                    
//'  
//' \describe{
//' \item{\code{changepoints}}{is the vector of changepoints.}
//' \item{\code{means}}{is the matrix of successive means for data.}
//' \item{\code{globalCost}}{is a number equal to the global cost.}
//' }                                                                                                                                                                             #     
//' 
//' @examples FPOPDp(data = matrix(c(0,0,0,0,1,1,2,2,2,2,0,0), nrow = 2), penalty = 2*log(6),  type = 1) 
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
    OPDp<Geom1Dp> X = OPDp<Geom1Dp>(data, penalty);
    
    X.algoFPOP(data, type, test);     
    res["changepoints"] = X.get_chpts();
    res["means"] = X.get_means();
    res["globalCost"] = X.get_globalCost();
  }
  
  if (type == 2){
    //test = true;//
    OPDp<Geom2Dp> Y = OPDp<Geom2Dp>(data, penalty);
    Y.algoFPOP(data, type, test);   
    res["changepoints"] = Y.get_chpts();
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
