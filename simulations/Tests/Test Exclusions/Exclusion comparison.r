meanFPOP2_100 <- readLines(con = 'FPOP2 Mean number of exclusions data10^5.txt', n = -1)

meanFPOP3_100 <- readLines(con = 'FPOP3 Mean number of exclusions data10^5.txt', n = -1)


meanFPOP2_100 <- strsplit(meanFPOP2_100,split = ' ')

meanFPOP3_100 <- strsplit(meanFPOP3_100,split = ' ')


meanFPOP2_100 <- sapply(meanFPOP2_100, FUN = function(x) {as.double(unlist(x))})

meanFPOP3_100 <- sapply(meanFPOP3_100, FUN = function(x) {as.double(unlist(x))})



meanFPOP2_100 <- c(meanFPOP2_100, seq(from = 0, by = 0, length.out = length(meanFPOP3_100) - length(meanFPOP2_100) ) )



png(filename = "Plot FPOP2 and FPOP3 Exclusions data10^5.png",  width = 1500, height = 1000)

plot(meanFPOP3_100, main = "FPOP2 and FPOP3:Mean number of exclusions", xlab = "Time", ylab = "Number of candidates(mean) being considered", col = "purple3")
lines(meanFPOP3_100, col= "purple3", lwd = 3)
points(meanFPOP2_100, col= "royalblue3")
lines(meanFPOP2_100, col= "royalblue3", lwd = 3)

##############
#   legend   #
##############
location = "topright"
labels = c("FPOP2","FPOP3")
colors = c("royalblue3", "purple3")
legend(location, labels, fill = colors)
dev.off()
