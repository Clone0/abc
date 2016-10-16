from math import log
from math import sqrt
from collections import Counter
from operator import itemgetter

def tf(kt,doc):
	return(doc.count(kt))

def idf(kt,all_docs):
	num=0
	for x in all_docs:
		if kt in x:
			num=num+1
	if num>0:
		return round(float(log(float(len(all_docs))))/float(num),3) #!!!!!!!!!!!!!!
	else:
		return 0

def tfidf(kt,doc):
	return tf(kt,doc)*idf(kt,all_docs)

def cos(inputfile,doc,kt):
	a=0
	for x in kt:
		a=a+(tfidf(x,inputfile)*tfidf(x,doc))
	b=doclen(x,inputfile)*doclen(x,doc)
	if not b:
		return 0
	else:
		return round(float(a/b),3)

def doclen(kt,doc):
	val=0
	for x in kt:
		val=val+pow(tfidf(x,doc),2)
	return sqrt(val)

files=[]
all_docs=[]
key=[]

documents=['doc1.txt','doc2.txt','doc3.txt','doc4.txt','doc5.txt','doc6.txt','doc7.txt','doc8.txt']
results=[['doc1.txt','animals'],['doc2.txt','animals'],['doc3.txt','animals'],['doc4.txt','sport'],['doc5.txt','sport'],['doc6.txt','sport'],['doc7.txt','movie'],['doc8.txt','movie']]

for x in documents:
	files.append(open(x,"r").read())
for x in files:
	all_docs.append(x.lower().rstrip('\n'))
for x in all_docs:
	key=key+x.split()

key=set(key)
key=list(key)

filename=raw_input("Enter File Name:-\n")
inputfile=open(filename,"r").readline().lower() #!!!!!!!!!!!!!!!!!!!!
cnt=0
for x in all_docs:
	results[cnt]=results[cnt]+[cos(inputfile,x,key)]
	cnt=cnt+1
print results
k=3
sortedres=sorted(results,key=itemgetter(2),reverse=True)
top_k=sortedres[:k] #!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
top_k[:]=(x for x in top_k if x[2]!=0)
if len(top_k)==0:
	print "Didn't match\n"
else:
	class_count=Counter(category for (document,category,value) in top_k) #!!!!!!!!!!!!!
	print class_count
	classification=max(class_count,key=lambda cls:class_count[cls])
	print "Class of text file is ",classification






















