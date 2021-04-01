library(base)
library(FPOPapprox2D)
set.seed(13)

Data =  data_genDp(p = 3, n = 1000, chpts = c(1000), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 

resFPOPDP1 <- FPOPDp(Data, penalty = 2*log(1000),  type = 1)  
resFPOPDP2 <- FPOPDp(Data, penalty = 2*log(1000),  type = 2)  
resFPOPDP3 <- FPOPDp(Data, penalty = 2*log(1000),  type = 3)  

#$chpts
#[1] 1000
#$means
#$means[[1]]
#[1] -0.0031129231  0.0008128666  0.0146805743
#$globalCost
#[1] -13.81551

set.seed(13)
Data1 =  data_genDp(p = 3, n = 4, chpts = c(4), means = matrix(c (0, 0, 0), nrow = 3), noise = 1) 
Data1

res2FPOPDP1 <- FPOPDp(Data1, penalty = 2*log(4),  type = 1) 
res2FPOPDP2 <- FPOPDp(Data1, penalty = 2*log(4),  type = 2) 
res2FPOPDP3 <- FPOPDp(Data1, penalty = 2*log(4),  type = 3) 

#$chpts
#[1] 4
#$means
#$means[[1]]
#[1] 0.55913462 0.75605963 0.02700961
#$globalCost
#[1] -2.772589
