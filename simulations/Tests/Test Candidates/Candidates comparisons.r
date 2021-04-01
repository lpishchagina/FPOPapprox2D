CandidatesFPOP1 <- readLines(con = 'FPOP1 Candidates  data10^5 iter100.txt', n = -1)
CandidatesFPOP2 <- readLines(con = 'FPOP2 Candidates  data10^5 iter100.txt', n = -1)
CandidatesFPOP3 <- readLines(con = 'FPOP3 Candidates  data10^5 iter100.txt', n = -1)

CandidatesFPOP1 <- strsplit(CandidatesFPOP1,split = ' ')
CandidatesFPOP2 <- strsplit(CandidatesFPOP2,split = ' ')
CandidatesFPOP3 <- strsplit(CandidatesFPOP3,split = ' ')

CandidatesFPOP1<- sapply(CandidatesFPOP1, FUN = function(x) {as.double(unlist(x))})
CandidatesFPOP2<- sapply(CandidatesFPOP2, FUN = function(x) {as.double(unlist(x))})
CandidatesFPOP3 <- sapply(CandidatesFPOP3, FUN = function(x) {as.double(unlist(x))})

png(filename = "Plot Candidates comparison data10^5.png",  width = 1500, height = 1000)

plot(CandidatesFPOP1, main = "Candidates", xlab = "Time", ylab = "Number of candidates(mean) being considered", col = "skyblue3")
lines(CandidatesFPOP1, col= "skyblue3", lwd = 3)
points(CandidatesFPOP3, col = "purple3")
lines(CandidatesFPOP3, col= "purple3", lwd = 3)
points(CandidatesFPOP2, col= "royalblue3")
lines(CandidatesFPOP2, col= "royalblue3", lwd = 3)
##############
#   legend   #
##############
location = "topleft"
labels = c("FPOP1","FPOP2","FPOP3")
colors = c("skyblue3","royalblue3", "purple3")
legend(location, labels, fill = colors)
dev.off()
