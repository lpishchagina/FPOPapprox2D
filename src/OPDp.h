#ifndef OPDP_H
#define OPDP_H

#include "RectDp.h"
#include "DiskDp.h"
#include "GausseCostDp.h"
#include "Geom3Dp.h"
#include "Geom2Dp.h"
#include "Geom1Dp.h"

#include <vector>
#include <list>
#include <iterator>

#include <string> 
#include <fstream>
#include <iostream>
#include <Rcpp.h>


using namespace Rcpp;
using namespace std;

/*
 Class OPDp
 -------------------------------------------------------------------------------
 Description: 
 Template for the realization of FPOP-Algorithm in p-dimension. 
 
 Parameters:
 "p" - dimension;
 "n" - data length;
 "penalty" - value of penalty;

 "sx12" - matrix(n+1x2*p) of sum:x1:xp, x1^2:xp^2;
 "geom" - geometry of <class GeomX>;
 "list_geom" - list of geometries;
 
 "chpts" - vector of changepoints;
 "means" - means matrix for  vector of changepoints; 
 "globalCost" - value of global cost.
 --------------------------------------------------------------------------------
 */
template <class GeomX>
class OPDp{
private:
  unsigned int n;         
  unsigned int p;         
  double penalty; 
  double** sx12;                   
  
  std::vector <unsigned int> chpts;                
  std::vector <std::vector <double>> means;        
  double globalCost;                                
  
public:
  //constructor, copy and destructor********************************************
  OPDp<GeomX>(){}

  OPDp<GeomX> (Rcpp::NumericMatrix x, double beta){
    p  = (unsigned int)x.nrow();
    n = (unsigned int)x.ncol();
    penalty = beta;
    sx12 = new double*[n + 1]; 
    for(unsigned int i = 0; i < n + 1; i++) {sx12[i] = new double[(2*p)];}
  }
  
  OPDp<GeomX> (const OPDp<GeomX> &geomX){
    p  = geomX.p;
    n = geomX.n;
    penalty = geomX.penalty;

    chpts = geomX.chpts;
    means = geomX.means;
    globalCost = geomX.globalCost;
    
    sx12 = new double*[n + 1]; 
    for(unsigned int i = 0; i < n + 1; i++) {
      sx12[i] = new double[(2*p)];
      for (unsigned int k = 0; k < p; k++){
        sx12[i][k] = geomX.sx12[i][k];
        sx12[i][p + k] = geomX.sx12[i][p + k];
      }
    }
  }
    
  ~OPDp<GeomX>(){
    Rcpp::Rcout<<"destr OP=>"<<std::endl;
    for(unsigned int i = 0; i < n + 1; i++) {delete(sx12[i]);}
    delete [] sx12;
    sx12 = NULL;
    Rcpp::Rcout<<"<=destr OP"<<std::endl;
  }
  //accessory*******************************************************************
  std::vector <unsigned int> get_chpts() const {return chpts;}
  
  std::vector <std::vector <double>> get_means() const{return means;}
  
  double get_globalCost() const {return globalCost;}
  
  unsigned int get_n() const {return n;}
  
  unsigned int get_p() const {return p;}
  
  double get_penalty() const {return penalty;}
  //preprocessing***************************************************************
  double** vect_sx12(Rcpp::NumericMatrix x) {
    for (unsigned int k = 0; k < p; k++){ sx12[0][k] = 0; sx12[0][p + k] = 0;}
    for (unsigned int j = 1; j < (n + 1); j++){
      for (unsigned int k = 0; k < p; k++){
        sx12[j][k] = sx12[j - 1][k] + x(k, j-1);
        sx12[j][p + k] = sx12[j - 1][p + k] + x(k, j-1)*x(k, j-1);
      }
    }
    return(sx12);
  }
  //algorithm FPOP**************************************************************
  void algoFPOP(Rcpp::NumericMatrix x, int type, bool test_mode){
    //preprocessing-------------------------------------------------------------
    double* m = new double[n + 1];                       //globalCost = m[n+1] - chpts.size()*penalty
    double* mus = new double[p];                         //values of temporary means 
    unsigned int* last_chpt = new unsigned int[n];       //vector of the best last changepoints 
    double** last_mean = new double*[n];                 //matrix (nxp) of means for the best last changepoints
    for(unsigned int i = 0; i < n; i++) {last_mean[i] = new double[p];}
    
    m[0] = 0;
    sx12 = vect_sx12(x); 
    
    std::ofstream test_file;                                  // candidates test
    if (test_mode == true){test_file.open("test.txt");}
    Rcpp::Rcout<<"GeomX=>"<<std::endl;
    GeomX geom = GeomX(p);

    Rcpp::Rcout<<"DiskDP=>"<<std::endl;
    DiskDp disk = DiskDp(p);
    Rcpp::Rcout<<"Cost=>"<<std::endl;
    GausseCostDp cost = GausseCostDp(p);
    std::list<GeomX> list_geom;//
    std::list<DiskDp> list_disk;      //list of active disks(t-1)
    //Algorithm-----------------------------------------------------------------
    
    for (unsigned int t = 0; t < n ; t++){
  
      Rcpp::Rcout << "MOMENT T = " << t <<"-------------" <<std::endl;
      
      cost.InitialGausseCostDp(p, t, t, sx12[t], sx12[t+1], m[t]);
      double min_val = cost.get_min();                       //min value of cost
      unsigned int lbl = t;                                 //best last position
      for (unsigned j = 0; j < p; j++){mus[j] = cost.get_mu()[j]; }
      
      //First run: searching min------------------------------------------------
      typename std::list<GeomX>::reverse_iterator rit_geom;
      rit_geom = list_geom.rbegin();
      while(rit_geom!= list_geom.rend()){
        unsigned int u = rit_geom -> get_label_t();
        // Searching: min
        cost.InitialGausseCostDp(p, u, t, sx12[u], sx12[t + 1], m[u]);
        if( min_val >= cost.get_min()){
          lbl = u;
          min_val = cost.get_min();
          for (unsigned j = 0; j < p; j++){mus[j] = cost.get_mu()[j]; }
        }
        //list of active disks(t-1)
        cost.InitialGausseCostDp(p, u, t-1, sx12[u], sx12[t], m[u]);
        double r2 = (m[t] - m[u] - cost.get_coef_Var())/cost.get_coef();
        
        disk.InitialDiskDp(p, cost.get_mu(), sqrt(r2));
        Rcpp::Rcout<<"push_back(disk)=>>"<<std::endl;
        list_disk.push_back(disk);
        ++rit_geom;
      }
          
      //new min 
      m[t + 1] = min_val + penalty;
      //best last changepoint and means
      for (unsigned int j = 0; j < p; j++){last_mean[t][j] = mus[j];}
      last_chpt[t] = lbl;  
      Rcpp::Rcout<<"1 STEP:lbl ="<<lbl<<" m[t + 1] ="<<m[t + 1]<<" size of disks = "<<  list_disk.size()<< std::endl;
      
      //Initialisation of geometry----------------------------------------------
      Rcpp::Rcout<<"2.INITIALISATION OF GEOMETRY"<<std::endl;
      geom.InitialGeometry(p,t,list_disk);
      Rcpp::Rcout<<"list_disk.clear()=>>"<<std::endl;
      list_disk.clear();
      Rcpp::Rcout<<"push_back(geom)=>>"<<std::endl;
      list_geom.push_back(geom);
      Rcpp::Rcout<<" geom.CleanGeometry=>>"<<std::endl;
      geom.CleanGeometry();
     
      //Second run: Update list of geometry-------------------------------------
       Rcpp::Rcout<<"3 STEP"<<std::endl;
      typename std::list<GeomX>::iterator it_geom;
      
      it_geom = list_geom.begin(); 
      while (it_geom != list_geom.end()){
        lbl = it_geom -> get_label_t();
        cost.InitialGausseCostDp(p, lbl, t, sx12[lbl], sx12[t + 1], m[lbl]);
        double r2 = (m[t + 1] - m[lbl] - cost.get_coef_Var())/cost.get_coef();
        Rcpp::Rcout << "r2 = " << r2 <<std::endl;
        //PELT
        if (r2 <= 0){
          Rcpp::Rcout<<"PELT: CleanGeometry()=>"<<std::endl;
          it_geom -> CleanGeometry();
          Rcpp::Rcout<<"PELT: list_geom.erase(it_geom)"<<std::endl;
          it_geom = list_geom.erase(it_geom); 
          --it_geom;
          Rcpp::Rcout << "<=END PELT "  <<std::endl;
        }
        //FPOP
        if (r2 > 0){
          disk.InitialDiskDp(p, cost.get_mu(), sqrt(r2));
          Rcpp::Rcout<<"UPDATE GEOM=>"<<std::endl;
          it_geom -> UpdateGeometry(disk);
          Rcpp::Rcout<<"<=UPDATE GEOM"<<std::endl;
          if (it_geom -> EmptyGeometry()){
            Rcpp::Rcout<<"FPOP: CleanGeometry()=>"<<std::endl;
            it_geom -> CleanGeometry();
            Rcpp::Rcout<<"FPOP: list_geom.erase(it_geom)=>"<<std::endl;
            it_geom = list_geom.erase(it_geom);
            --it_geom;
            Rcpp::Rcout << "<=END FPOP"  <<std::endl;
          }
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
      Rcpp::Rcout<<" chp ="<<chp;
      std::vector<double> mm;
      for (unsigned int i = 0; i < p; i++){mm.push_back(last_mean[chp-1][i]);
      }
      means.push_back(mm);
      chp = last_chpt[chp-1];
    }
    reverse(chpts.begin(), chpts.end());
    reverse(means.begin(), means.end());
    globalCost = m[n + 1] - penalty * chpts.size();
    
    //memory--------------------------------------------------------------------
    Rcpp::Rcout<<std::endl<<"MEMORY"<<std::endl;

    Rcpp::Rcout<<"CLEAN LIST_GEOM=>"<<std::endl;
    list_geom.clear(); //important
  
    Rcpp::Rcout<<"CLEAN vectors"<<std::endl;
    for(unsigned int i = 0; i < n; i++) {delete(last_mean[i]);}
    delete [] last_mean;
    delete [] last_chpt;
    delete [] mus;
    delete [] m;
    m = NULL;
    last_mean = NULL;
    last_chpt = NULL;
    mus = NULL;
    Rcpp::Rcout<<"END Algo"<<std::endl;
  }
};

#endif //OPDP_H      
    