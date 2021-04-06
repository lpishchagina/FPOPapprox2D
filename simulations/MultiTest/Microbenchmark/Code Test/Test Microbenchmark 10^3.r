#############################################################################################
#############################################################################################
##                                         Test                                            ##
##                   Time complexity. One simulation. Microbenchmark                       ##
##                            The data without changepoints                                ##
##                                      n = 1000                                           ##
#############################################################################################
#############################################################################################

###############################
#    package installation     #
###############################
#devtools::install_github("lpishchagina/OptPartitioning2D")
library(OptPartitioning2D)

#devtools::install_github("lpishchagina/FPOPdim2")
library(FPOPdim2)

devtools::install_github("lpishchagina/FPOPapprox2D")

library(FPOPapprox2D)
library(base)
library(rstream)

library(tidyverse)      # data manipulation and viz
library(ggthemes)       # themes for ggplot2
library(viridis)        # the best color palette
library(rgdal)          # deal with shapefiles
library(microbenchmark) # measure the speed of executing
library(extrafont)      # nice font
library(RColorBrewer)

###############################
#    Function one.simu.fpop   #
###############################
#The function returns the runtime of the algorithm for one simulation

#type = 1 - FPOP: only intersection, approximation of intersection = rectangle
#type = 2 - FPOP: intersection and exclusion, approximation of intersection and exclusion = rectangle
#type = 3 - FPOP: only exclusion, approximation -  disk
one.simu.fpop  <- function(data, penalty, type, func = "FPOPDp")
{
  if (type == 1){t <- system.time(FPOPDp(data, penalty, type = 1))[[1]]}
  if (type == 2){t <- system.time(FPOPDp(data, penalty, type = 2))[[1]]}
  if (type == 3){t <- system.time(FPOPDp(data, penalty, type = 3))[[1]]}
  return(t)
}

######################################################################
#                                data generation                     #
#                           The data without changepoints            #
######################################################################

##############################
#parameters mu, sigma  #
#       (by default)         #
##############################
dim <- c(2:10, 12,15)
Data <- list()
mu <-list()
sigma <- 1

size <-1000
##############################
chp <- size
penalty <- 2*sigma*log(size)

set.seed(13)
for (i in 1: length(dim)){
  mu[[i]] <- matrix(0, ncol = 1, nrow = dim[i])
  Data[[i]]<- data_genDp(dim[i], size, chp, mu[[i]], sigma)  
}

###############################
#       microbenchmark        #
###############################
resf1.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 1, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 1, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 1, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 1, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type = 1, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 1, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 1, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 1, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 1, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 1, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 1, func = "FPOPDp"), times = 50) 
resf2.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 2, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 2, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 2, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 2, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type = 2, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 2, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 2, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 2, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 2, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 2, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 2, func = "FPOPDp"), times = 50) 
resf3.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 3, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 3, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 3, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 3, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type =3, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 3, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 3, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 3, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 3, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 3, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 3, func = "FPOPDp"), times = 50) 

png(filename = "10^3 FPOP1 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf1.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP1")
dev.off()
png(filename = "10^3 FPOP2 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf2.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP2")
dev.off()
png(filename = "10^3 FPOP3 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf3.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP3")
dev.off()


###############################
#       microbenchmark        #
###############################
resdim2.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[1]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[1]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[1]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim3.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[2]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[2]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[2]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim4.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[3]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[3]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[3]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim5.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[4]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[4]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[4]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim6.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[5]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[5]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[5]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim7.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[6]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[6]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[6]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim8.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[7]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[7]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[7]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim9.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[8]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[8]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[8]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim10.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[9]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[9]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[9]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim12.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[10]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[10]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[10]], penalty, type = 3, func = "FPOPDp"), times = 10) 

resdim15.microbenchmark <- microbenchmark( "FPOP1  "= one.simu.fpop(Data[[11]], penalty, type = 1, func = "FPOPDp"),"FPOP2 "= one.simu.fpop(Data[[11]], penalty, type = 2, func = "FPOPDp"),"FPOP3 "= one.simu.fpop(Data[[11]], penalty, type = 3, func = "FPOPDp"), times = 10) 


png(filename = "10^3 dim2 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim2.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 2)")
dev.off()
png(filename = "10^3 dim3 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim3.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 3)")
dev.off()
png(filename = "10^3 dim4 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim4.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 4)")
dev.off()
png(filename = "10^3 dim5 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim5.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 5)")
dev.off()
png(filename = "10^3 dim6 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim6.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 6)")
dev.off()
png(filename = "10^3 dim7 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim7.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 7)")
dev.off()
png(filename = "10^3 dim8 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim8.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 8)")
dev.off()
png(filename = "10^3 dim9 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim9.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 9)")
dev.off()
png(filename = "10^3 dim10 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim10.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 10)")
dev.off()
png(filename = "10^3 dim12 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim12.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 12)")
dev.off()
png(filename = "10^3 dim15 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resdim15.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed (Dimension 15)")
dev.off()

#############################################################################################
#############################################################################################
##                                        End Test                                         ##
#############################################################################################
#############################################################################################