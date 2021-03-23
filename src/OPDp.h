#ifndef OPDP_H
#define OPDP_H

#include "DiskDp.h"
#include "GausseCostDp.h"
#include "Geom3Dp.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <Rcpp.h>
#include <string> 

using namespace Rcpp;
using namespace std;

template <class GeomX>
class OPDp{
private:
  double penalty; //value of penalty 
  int n; //data length
  int p;  //dimension
  double** sx12;  // vector sum x1,x2,..,xp x1^2, x2^2,.., xp^2
  
  std::vector<int> chpts;             //changepoints vector 
  std::vector<std::vector<double>> means;         //means vector 
  double globalCost;                  //value of global cost
  double* m;                          //globalCost = m[n+1] - chpts.size()*penalty
  GeomX geom;
  std::list<GeomX> list_geom;    //list of geometry
  
public:
  OPDp<GeomX>(){};
 
  OPDp<GeomX> (Rcpp::NumericMatrix x, double beta){
    p  = x.nrow();
    n = x.ncol();
    penalty = beta;
    int k = 2*p;
    sx12 = new double*[n + 1]; 
    for(int i = 0; i < n + 1; i++) {sx12[i] = new double[k];}
    m = new double[n + 1];        // "globalCost" = m[n+1] - chpts.size()*penalty
  }
  //----------------------------------------------------------------------------
  ~OPDp<GeomX>(){
    for(int i = 0; i < n+1; i++) {delete(sx12[i]);}
    delete [] sx12;
    sx12 = NULL;
    delete [] m;
    m = NULL;
  }

  std::vector< int > get_chpts() const {return chpts;}
  std::vector<std::vector< double >> get_means() const{return means;}
  double get_globalCost() const {return globalCost;}
  int get_n() const {return n;}
  int get_p() const {return p;}
  double get_penalty() const {return penalty;}

  double** vect_sx12(Rcpp::NumericMatrix x) {
    int p = x.nrow();
    int n = x.ncol();
    for (int k = 0; k < p; k++){ sx12[0][k] = 0;sx12[0][p + k] = 0; }
    for (int j = 1; j < (n + 1); j++){
      for (int k = 0; k < p; k++){
        sx12[j][k] = sx12[j - 1][k] + x(k, j-1);
        sx12[j][p + k] = sx12[j - 1][p + k] + x(k, j-1)*x(k, j-1);
      }
    }
    return(sx12);
  }
  //----------------------------------------------------------------------------
  void algoFPOP(Rcpp::NumericMatrix x, int type, bool test_mode){
    //preprocessing-------------------------------------------------------------
    p = x.nrow();
    n = x.ncol();
    sx12 = vect_sx12(x); 
    penalty = get_penalty();
    m[0] = 0;
    
    double** last_mean_chpt = new double*[p+1];// vectors of mean1, mean2,.., meanp  and the best last changepoints, 
    for(unsigned int i = 0; i < p+1; i++) {last_mean_chpt[i] = new double[n];}
    
    std::ofstream test_file;
    if (test_mode == true){test_file.open("test.txt");}
    
    //Algorithm-----------------------------------------------------------------
    for (int t = 0; t < n ; t++){
      
      Rcpp::Rcout<<"t="<<t<<std::endl;
      
      GausseCostDp cost = GausseCostDp(p, t, t, sx12[t], sx12[t+1], m[t]);
      double min_val = cost.get_min(); //min value of cost
      std::vector<double> means =  cost.get_mu();   //means for (lbl, t)
      int lbl = t;         //best last position
      std::list<DiskDp> list_disk;//list of active disks(t-1)
      list_disk.clear();
     
      typename std::list<GeomX>::reverse_iterator rit_geom;
      //First run: searching min------------------------------------------------
      rit_geom = list_geom.rbegin();
      while(rit_geom!= list_geom.rend()){
        int u = rit_geom -> get_label_t();
        // Searching: min
        cost = GausseCostDp(p, u, t, sx12[u], sx12[t + 1], m[u]);
        if( min_val >= cost.get_min()){
          lbl = u;
          min_val = cost.get_min();
          means = cost.get_mu();
        }
        //list of active disks(t-1)
        GausseCostDp cost_t_1 = GausseCostDp(p, u, t-1, sx12[u], sx12[t], m[u]);
        double r2 = (m[t] - m[u] - cost_t_1.get_coef_Var())/cost_t_1.get_coef();
        DiskDp disk = DiskDp(p, cost_t_1.get_mu(), sqrt(r2));
        list_disk.push_back(disk);
        ++rit_geom;
      }
      //best last changepoints and means
      last_mean_chpt[p][t] = lbl;       //vector of best last chpt
      for (int j = 0; j < p; j++){last_mean_chpt[j][t] = means[j];} //vector of means (lbl,t)
      //new min 
      m[t + 1] = min_val + penalty;
      //Initialisation of geometry----------------------------------------------
      geom = GeomX(p, t); 
      geom.InitialGeometry(list_disk);
      //push to list of geometry new geometry Dtt
      list_geom.push_back(geom);
      
      //Second run: Update list of geometry-------------------------------------
      typename std::list<GeomX>::iterator it_geom;
      it_geom = list_geom.begin();      
      while (it_geom != list_geom.end()){
        lbl = it_geom -> get_label_t();
        cost = GausseCostDp(p, lbl, t, sx12[lbl], sx12[t + 1], m[lbl]);
        double r2 = (m[t + 1] - m[lbl] - cost.get_coef_Var())/cost.get_coef();
        //PELT
        if (r2 <= 0){it_geom = list_geom.erase(it_geom); --it_geom;Rcpp::Rcout<<"Pelt"<<std::endl;}
        //FPOP
        
        if (r2 > 0){
          DiskDp disk_lblt = DiskDp(p, cost.get_mu(), sqrt(r2));
          it_geom -> UpdateGeometry(disk_lblt);
          if (it_geom -> EmptyGeometry()){it_geom = list_geom.erase(it_geom);--it_geom;Rcpp::Rcout<<"fpop"<<std::endl;}
          else {if (test_mode == true && (type == 2 || type == 3)){ test_file << it_geom ->get_label_t() << " "<< it_geom ->get_disks_t_1().size() << " ";}}
        }//else
        ++it_geom;
      }
      if (test_mode == true){test_file << "\n";} 
    }
    if (test_mode == true){test_file.close();}
    //Result vectors------------------------------------------------------------
    unsigned int chp = n;
    while (chp > 0){
      chpts.push_back(chp);
      std::vector<double> mus;
      for (int j = 0; j < p; j++){mus.push_back(last_mean_chpt[j][chp-1]);}
      means.push_back(mus);
      chp = last_mean_chpt[p][chp-1];
    }
    reverse(chpts.begin(), chpts.end());
    reverse(means.begin(), means.end());
    globalCost = m[n + 1] - penalty * chpts.size();
    //memory--------------------------------------------------------------------
    for(unsigned int i = 0; i < p+1; i++) {delete(last_mean_chpt[i]);}
    delete [] last_mean_chpt;
    last_mean_chpt = NULL;
  }
};

#endif //OPDP_H      
    