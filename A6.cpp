#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
using namespace std;
//DEFINITION OF SPLIT FUNCTION
vector<string> split(string str,char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string tok;
	while(getline(ss,tok,delimiter))
	{
		internal.push_back(tok);
	}
	return internal;
}
int main()
{
	int n;
	int number=0;
	string line;
	ifstream myfile("ip.csv");
	while (getline(myfile, line))
	{
        	++number;
	}
	n=number;
	cout<<"No. of data items: "<<n<<"\n";
	ifstream in("ip.csv");//for reading
	ofstream out;//for writing
	string s;
	vector<string> p;
	double x[n],y[n];//storing co-ordinates
	int lol=0;
	//SPLIT THE LINE AT "," AND STORE CO-ORDINATES
	while(in>>s)
	{
		p=split(s,',');
		x[lol]=atof(p[0].c_str());
		y[lol]=atof(p[1].c_str());
		++lol;
	}
	int k;
	cout<<"Enter number of clusters:";
	cin>>k;
	vector<double> *mean;
	mean=new vector<double>[2];
	//Enter first k entries from input dataset
	cout<<"Random Centroids are:-\n";
	int randIndex;
	int rn=n+1;
	for(int i=0;i<k;i++)
	{
		int mx,my;
		randIndex=rand()%rn;
		mx=x[randIndex];
		my=y[randIndex];
		cout<<i<<") "<<mx<<","<<my<<"\n";
		mean[0].push_back(mx);
		mean[1].push_back(my);
	}
	vector<double> *omean;
	omean=new vector<double>[2];
	//stores position of data
	vector<int> *c;		//k clusters
	c=new vector<int>[n];	//each cluster of size n
	while(1)
	{
		for(int i=0;i<2;i++)
			omean[i]=mean[i];

		//clear previous cluster
		for(int i=0;i<k;i++)
			c[i].erase(c[i].begin(),c[i].end());

		//Cluster the data
		for(int i=0;i<n;i++)
		{
			double min=99999;
			int pos;
			
			//Find cluster center with minimum difference 
			for(int j=0;j<k;j++)
			{

				double temp=sqrt(pow((x[i]-mean[0][j]),2)+pow((y[i]-mean[1][j]),2));
				if(temp<min)
				{
					min=temp;
					pos=j;
				}
			}

			c[pos].push_back(i);

		}


		//Calculate new mean and copy cluster data
		for(int i=0;i<k;i++)
		{
			double xsum=0,ysum=0;
			for(int j=0;j<c[i].size();j++)
			{
				xsum+=x[c[i][j]];
				ysum+=y[c[i][j]];

			}
			mean[0][i]=xsum/c[i].size();
			mean[1][i]=ysum/c[i].size();
		}
		//CHECK IF MEAN HAS CHANGED OR REMAINED SAME
		if(omean[0]==mean[0] && omean[1]==mean[1])
			break;
		
		//DISPLAY OUTPUT ON CONSOLE FOR EACH PASS except last one
		for(int i=0;i<k;i++)
		{
			cout<<"\nCluster "<<i+1<<endl;
			cout<<"Mean of cluster\n";
			cout<<mean[0][i]<<","<<mean[1][i]<<endl;
			cout<<"Cluster data\n";

			for(int j=0;j<c[i].size();j++)
			{
				int pos=c[i][j];		
				cout<<x[pos]<<","<<y[pos]<<endl;
			}
		}
			cout<<endl;
	}


	out.open("op.csv");
	//STORE RESULT IN A FILE
	for(int i=0;i<k;i++)
	{
		out<<"Cluster "<<i+1<<endl;
		out<<"Mean of cluster\n";
		out<<mean[0][i]<<","<<mean[1][i]<<endl;
		out<<"Cluster data\n";

		for(int j=0;j<c[i].size();j++)
		{
			int pos=c[i][j];		
			out<<x[pos]<<","<<y[pos]<<endl;
		}
		out<<endl;
	}

	in.close();
	out.close();
	return 0;
}
