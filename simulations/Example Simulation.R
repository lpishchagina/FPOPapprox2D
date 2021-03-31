Data =  data_genDp(p = 3, n = 4, chpts = c(2, 4), means = matrix(c (0, 0, 0, 10, 10, 10), nrow = 3), noise = 1) 
Data

FPOPDp(Data, penalty = 2*log(4),  type = 3)  
FPOPDp(data = matrix(c(0,0,0,0,1,1,2,2,2,2,0,0), nrow = 2), penalty = 2*log(6),  type = 1)
 
 
  Data =  data_genDp(p = 4, n = 1000, chpts = c(1000), means = matrix(c (0, 0, 0, 0), nrow = 4), noise = 1) 
  Data
  FPOPDp(Data, penalty = 2*log(1000),  type = 3)  
   
  Data =  data_genDp(p = 2, n = 1000, chpts = c(1000), means = matrix(c (0, 0), nrow = 2), noise = 1) 
  Data
  FPOPDp(Data, penalty = 2*log(1000),  type = 3) 
  FPOPDp(Data, penalty = 2*log(1000),  type = 1) 
   
  Data =  data_genDp(p = 3, n = 1000, chpts = c(1000), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
  Data
  FPOPDp(Data, penalty = 2*log(1000),  type = 3) 
  library(base)
  set.seed(13)
  Data =  data_genDp(p = 3, n = 10, chpts = c(10), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
  Data
  FPOPDp(Data, penalty = 2*log(10),  type = 1) 
  FPOPDp(Data, penalty = 2*log(3),  type = 2)   
  
  FPOPDp(Data, penalty = 2*log(10),  type = 3) 

  Data =  data_genDp(p = 3, n = 3, chpts = c(3), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
  Data
  FPOPDp(Data, penalty = 2*log(3),  type = 3)   
    library(base)
    set.seed(13)
    Data =  data_genDp(p = 3, n = 4, chpts = c(4), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
    Data
  
  FPOPDp(Data, penalty = 2*log(4),  type = 1) 
  
  FPOPDp(Data, penalty = 2*log(4),  type = 2) 
  FPOPDp(Data, penalty = 2*log(4),  type = 3) 
  