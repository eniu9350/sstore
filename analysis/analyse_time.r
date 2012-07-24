#rm(list=ls(all=TRUE));
t<-read.table("Z:\\niuj\\sstore\\analysis\\time", header=FALSE);

tmin=t[1,1]; #start from 1?
tmax=0;

#get start and end
for(i in 1:nrow(t)) {
  if(t[i,1]<tmin) {
    tmin = t[i,1];
  }
  if(t[i,2]>tmax) {
    tmax = t[i,2];
  }
} 

print(tmin);
print(tmax);

#count users at each second
nusers<-matrix(0,nrow=tmax-tmin+1,ncol=1)
#counting joining and leaving users at each second
njlusers<-matrix(0,nrow=tmax-tmin+1,ncol=3)

for(i in 1:(tmax-tmin+1)) {
  njlusers[i,1] = 0;
  njlusers[i,2] = 0;
}

for(i in 1:nrow(t)) {
  for(j in t[i,1]:t[i,2]) {
    nusers[j-tmin+1,1] = nusers[j-tmin+1,1]+1;
  }
  njlusers[t[i,1]-tmin+1, 1] = njlusers[t[i,1]-tmin+1, 1]+1;
  njlusers[t[i,2]-tmin+1, 2] = njlusers[t[i,2]-tmin+1, 2]+1;
}

for(i in 1:nrow(njlusers)){
  njlusers[i,3] = njlusers[i,1] + njlusers[i,2];
}

par( mfrow = c( 2, 2 ) )
plot(nusers);
plot(njlusers[,1])
plot(njlusers[,2])
plot(njlusers[,3])

#npart<-matrix(0,nrow=100,ncol=1)

#for(k in 1:100){
#  npart[k,1] = nusers[k,1];
#}
#plot(npart);