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

d#evtools::install_github("lpishchagina/FPOPapprox2D")

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

size <-10000
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
resf1.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 1, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 1, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 1, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 1, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type = 1, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 1, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 1, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 1, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 1, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 1, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 1, func = "FPOPDp"), times = 5) 
resf2.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 2, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 2, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 2, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 2, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type = 2, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 2, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 2, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 2, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 2, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 2, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 2, func = "FPOPDp"), times = 5) 
resf3.microbenchmark <- microbenchmark( "dim 2  "= one.simu.fpop(Data[[1]], penalty, type = 3, func = "FPOPDp"), "dim 3  "= one.simu.fpop(Data[[2]], penalty, type = 3, func = "FPOPDp"),  "dim 4  "= one.simu.fpop(Data[[3]], penalty, type = 3, func = "FPOPDp"), "dim 5  "= one.simu.fpop(Data[[4]], penalty, type = 3, func = "FPOPDp"), "dim 6  "= one.simu.fpop(Data[[5]], penalty, type =3, func = "FPOPDp"), "dim 7  "= one.simu.fpop(Data[[6]], penalty, type = 3, func = "FPOPDp"), "dim 8  "= one.simu.fpop(Data[[7]], penalty, type = 3, func = "FPOPDp"), "dim 9  "= one.simu.fpop(Data[[8]], penalty, type = 3, func = "FPOPDp"),  "dim 10  "= one.simu.fpop(Data[[9]], penalty, type = 3, func = "FPOPDp"),"dim 12  "= one.simu.fpop(Data[[10]], penalty, type = 3, func = "FPOPDp"),"dim 15  "= one.simu.fpop(Data[[11]], penalty, type = 3, func = "FPOPDp"), times = 5) 

png(filename = "10^4 FPOP1 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf1.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP1")
dev.off()
png(filename = "10^4 FPOP2 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf2.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP2")
dev.off()
png(filename = "10^4 FPOP3 Microbenchmark.png",  width = 1500, height = 1000)
autoplot(resf3.microbenchmark)+aes(fill = expr)+scale_fill_viridis(discrete = T)+theme(legend.position = "none",axis.text = element_text(size = 15))+labs(title = "The speed of FPOP3")
dev.off()
#############################################################################################
#############################################################################################
##                                        End Test                                         ##
#############################################################################################
#############################################################################################