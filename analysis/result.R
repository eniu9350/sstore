d<-matrix(0,nrow=10,ncol=2)
d[1,] = c(10.0/3, 10.0/3)#user 200k
d[2,] = c(20.0/3, 20.0/3)#user 400k
d[3,] = c(30.0/3, 30.0/3)#user 600k
d[4,] = c(40.0/3, 13.33) #user 800k
d[5,] = c(50.0/3, 14.29) #user 1000k
d[6,] = c(60.0/3, 14.75) #user 1200k
d[7,] = c(70.0/3, 14.00)  #user 1400k
d[8,] = c(80.0/3, 13.41)  #user 1600k
d[9,] = c(90.0/3, 13.04)  #user 1800k
d[10,] = c(100.0/3, 12.71) #user 2000k


rex<-matrix(0,nrow=9,ncol=2)
rex[1,] = c(10.0/3, 10.0/3)#!user 200k
rex[2,] = c(20.0/3, 20.0/3)#!user 400k
rex[3,] = c(30.0/3, 30.0/3)#!user 600k
rex[4,] = c(40.0/3, 40.0/3) #!user 800k
rex[5,] = c(50.0/3, 13.89) #!user 1000k
rex[6,] = c(60.0/3, 14.75) #!user 1200k
rex[7,] = c(70.0/3, 13.55)  #!user 1400k
rex[8,] = c(80.0/3, 13.26)  #!user 1600k
rex[9,] = c(90.0/3, 11.89)  #!user 1800k
#rex[10,] = c(100.0/3, 11.90) #!user 2000k





#d[6,] = c(10.0/3, 10.0/3)
#d[7,] = c(10.0/3, 10.0/3)
#d[8,] = c(10.0/3, 10.0/3)

plot(rex[,1], rex[,2], type="l", xlim=c(0,40), ylim=c(0,20), col="red", xlab="offered load (kreq/s)", ylab="throughput (kreq/s)")
#lines(d[,1], d[,2], type="l", xlim=c(0,40), ylim=c(0,20), col="blue", xlab="offered load (kreq/s)", ylab="throughput (kreq/s)")

dold<-matrix(0,nrow=6,ncol=2)
dold[1,] = c(0, 0)  #user 100k  //not test
dold[2,] = c(10.0/3, 3.30)  #user 200k
dold[3,] = c(20.0/3, 4.76)  #user 400k
dold[4,] = c(30.0/3, 4.48)  #user 600k
dold[5,] = c(40.0/3, 4.30)  #user 800k
dold[6,] = c(50.0/3, 4.24)  #user 1000k
lines(dold, col="green")




e<-matrix(0,nrow=4,ncol=2)
e[1,] = c(5.0/3, 5.0/3)#user 100k
e[2,] = c(10.0/3, 10.0/3)#user 200k
e[3,] = c(20.0/3, 3.02)#user 400k
e[4,] = c(30.0/3, 3.02)#user 600k
#e[2,] = c(40.0/3, 6.02)#user 400k
#e[2,] = c(30.0/3, 20.0/3)#user 400k
