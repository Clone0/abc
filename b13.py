import csv
import random
from operator import itemgetter
import math

def load(ipfile,split,train=[],test=[]):
	with open(ipfile,'rb') as c:
		lines=csv.reader(c)
		dataset=list(lines)
		for x in range(len(dataset)):
			for y in range(4):
				dataset[x][y]=float(dataset[x][y])
			if random.random() < split:
				train.append(dataset[x])
			else:
				test.append(dataset[x])


def ed(i1,i2,l):
	d=0
	for x in range(l):
		d+=pow((i1[x]-i2[x]),2)
	return math.sqrt(d)

def getN(train,test_i,k):
	dist=[]
	l=len(test_i)-1 #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for x in range(len(train)):
		d=ed(train[x],test_i,l)
		dist.append((train[x],d)) #((,))
	dist.sort(key=itemgetter(1))
	n=[]
	for x in range(k):
		n.append(dist[x][0])
	return n

def getR(n):
	votes={}
	for x in range(len(n)):
		response=n[x][-1]
		if response in votes:
			votes[response]+=1
		else:
			votes[response]=1
	sortedVotes=sorted(votes.iteritems(),key=itemgetter(1),reverse=True)
	return sortedVotes[0][0]

def Acc(pred,test):
	correct=0
	for x in range(len(test)):
		if(test[x][-1]==pred[x]):
			correct+=1
	return (correct/float(len(test)))*100.0

def main():
	train=[]
	test=[]
	split=0.67
	load("iris.data",split,train,test)
	pred=[]
	n=[]
	print "Training data size ",repr(len(train))
	print "Test data size ",repr(len(test))
	k=3
	for x in range(len(test)):
		n=getN(train,test[x],k)
		r=getR(n)
		pred.append(r)
		print ("PREDICTED :- "+repr(r)+" ACTUAL :- "+test[x][-1])
	res=Acc(pred,test)
	print ("Accuracy:- "+repr(res)+"%")
main()
		
	

		
