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

#devtools::install_github("lpishchagina/FPOPapprox2D")

library(FPOPapprox2D)
library(base)
library(rstream)

library(microbenchmark)
library("ggplot2")

###############################
#     Function one.simu.op    #
###############################
#The function returns the runtime of the algorithm for one simulation

#type = "null" - Optimal Partitioning
#type = "pruning" - PELT

one.simu.op <- function(data1, data2, penalty, type, func = "OptPart2D")
{
  if(type == "null"){t <- system.time(OptPart2D(data1, data2, penalty, type = "null"))[[1]]}
  if(type == "pruning"){t <- system.time(OptPart2D(data1, data2, penalty, type = "pruning"))[[1]]}
  return(t)
}

###############################
#    Function one.simu.fpopd2   #
###############################
#type = 1 - FPOP2D: only intersection, approximation of intersection = rectangle
#type = 2 - FPOP: intersection and exclusion, approximation of intersection and exclusion = rectangle
#type = 3 - FPOP: only exclusion, approximation -  disk
one.simu.fpopd2  <- function(data1, data2, penalty, type, func = "FPOP2D")
{
  if (type == 1){t <- system.time(FPOP2D(data1, data2, penalty, type = 1))[[1]]}
  if (type == 2){t <- system.time(FPOP2D(data1, data2, penalty, type = 2))[[1]]}
  if (type == 3){t <- system.time(FPOP2D(data1, data2, penalty, type = 3))[[1]]}
  return(t)
}


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
dim <- 2
mu <- matrix(c (0, 0), nrow = 2)
sigma <- 1

##############################
n <-100000
dim <- 2

##############################
chp <- n
penalty <- 2*sigma*log(n)

set.seed(21)
Data <- data_genDp(dim, n, chp, mu, sigma)
#Data[1,1] [1] 0.7930132 

###############################
#           Algorithm         #
###############################

resOP <- OptPart2D(Data[1,], Data[2,], penalty, type = "null")
resPELT <- OptPart2D(Data[1,], Data[2,], penalty, type = "pruning")

#$changepoints		$means1				$means2				$globalCost
#[1] 1000			[1] 0.07820922 		[1] 0.01483164		[1] 1996.968

resFPOP1d2 <- FPOP2D(Data[1,], Data[2,], penalty, type = 1)
resFPOP2d2 <- FPOP2D(Data[1,], Data[2,], penalty, type = 2)
resFPOP3d2 <- FPOP2D(Data[1,], Data[2,], penalty, type = 3)

resFPOP1 <- FPOPDp(Data, penalty, type = 1)
resFPOP2 <- FPOPDp(Data, penalty, type = 2)
resFPOP3 <- FPOPDp(Data, penalty, type = 3)
#$1000		0.07820922 		 0.01483164		 -13.81551

###############################
#The data without changepoints#
#The runtime One simulation   #
###############################

one.runtimeOP <- one.simu.op(Data[1,], Data[2,], penalty, type = "null", func = "OptPart2D")
one.runtimePELT <- one.simu.op(Data[1,], Data[2,], penalty, type = "pruning", func = "OptPart2D")
one.runtimeFPOP1 <- one.simu.fpop(Data, penalty, type = 1, func = "FPOPDp")
one.runtimeFPOP2 <- one.simu.fpop(Data, penalty, type = 2, func = "FPOPDp")
one.runtimeFPOP3 <- one.simu.fpop(Data, penalty, type = 3, func = "FPOPDp")
one.runtimeFPOP1d2 <- one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 1, func = "FPOP2D")
one.runtimeFPOP2d2 <- one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 2, func = "FPOP2D")
one.runtimeFPOP3d2 <- one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 3, func = "FPOP2D")

###############################
#       microbenchmark        #
###############################
res.microbenchmark <- microbenchmark("OP" =one.simu.op(Data[1,], Data[2,], penalty, type = "null", func = "OptPart2D"), "PELT"= one.simu.op(Data[1,], Data[2,], penalty, type = "pruning", func = "OptPart2D" ), "FPOP1"= one.simu.fpop(Data, penalty, type = 1, func = "FPOPDp"), "FPOP2" = one.simu.fpop(Data, penalty, type = 2, func = "FPOPDp"), "FPOP3" = one.simu.fpop(Data, penalty, type = 3, func = "FPOPDp"),"FPOP1_2d"= one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 1, func = "FPOP2D"), "FPOP2_2d" = one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 2, func = "FPOP2D"), "FPOP3_2d" = one.simu.fpopd2(Data[1,], Data[2,], penalty, type = 3, func = "FPOP2D"), times = 5)
#
png(filename = "Microbenchmark data10^5.png",  width = 1500, height = 1000)
autoplot(res.microbenchmark)

dev.off()




#############################################################################################
#############################################################################################
##                                        End Test                                         ##
#############################################################################################
#############################################################################################