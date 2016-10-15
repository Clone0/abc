#include <iostream>
#include<omp.h>
using namespace std;
class dynamic
{
private:
	int c[5][5],n,d[24],p[24][6],list[5],r;
public:
	dynamic();
	void getdata();
	void display();
	int fact(int num);
	int min(int list[]);
	void perm(int list[], int k, int m);
	void sol();
};
dynamic::dynamic()
{
	r=0;
}

void dynamic::getdata()
{ int i,j;
cout<<"Enter no. of cities:";
cin>>n;
cout<<endl;
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
		c[i][j]=0;
for (i=0;i<n;i++)
{
	for (j=0;j<n;j++)
	{
		if (i!=j)
		{
			if (c[i][j]==0)
			{
				cout<<"Enter cost from "<<i<<" to "<<j<<" :";
				cin>>c[i][j];
				c[j][i]=c[i][j];
			}
		}
	}
}
for (i=0;i<n-1;i++)
	list[i]=i+1;
}

int dynamic::fact(int num)
{
int f=1;
if (num!=0)
for (int i=1;i<=num;i++)
	f=f*i;
return f;
}

void dynamic::perm(int list[], int k, int m)
{
int i,temp;
if (k==m)
{
	for (i=0;i<=m;i++)
		{
			p[r][i+1]=list[i];
		}
	r++;
}
else
	for (i=k;i<=m;i++)
	{
		temp=list[k]; list[k]=list[i]; list[i]=temp;
		perm(list,k+1,m);
		temp=list[k]; list[k]=list[i]; list[i]=temp;
	}
}

void dynamic::sol()
{
     int i;
     #pragma openmp parallel
	perm(list,0,n-2);
	for (i=0;i<fact(n-1);i++)
	{
		p[i][0]=0;
		p[i][n]=0;
	}
	for (i=0;i<fact(n-1);i++)
	{
		d[i]=0;
		for (int j=0;j<n;j++)
		{
			d[i]=d[i]+c[p[i][j]][p[i][j+1]];
		}
	}
}
int dynamic::min(int list[])
{
	int minimum=list[0];
	for (int i=0;i<fact(n-1);i++)
	{
		if (list[i]<minimum)
			minimum=list[i];
	}
	return minimum;
}
void dynamic::display()
{
int i,j;
cout<<endl<<"The cost Matrix:"<<endl;
for (i=0;i<n;i++)
	{
	for (j=0;j<n;j++)
		cout<<c[i][j]<<"\t";
	cout<<endl;
	}
cout<<endl<<"The Possible paths and their corresponding cost:"<<endl;
for (i=0;i<fact(n-1);i++)
	{
	for (j=0;j<n+1;j++)
		cout<<p[i][j]<<"\t";
	cout<<"--> "<<d[i]<<endl;
	}
cout<<endl<<"The shortest path :"<<endl;
for (i=0;i<fact(n-1);i++)
{
	if (d[i]==min(d))
		break;
}
for (j=0;j<=n;j++)
{
	cout<<p[i][j]<<" ";
}
cout<<endl<<"\nThe cost of this path is "<<d[i]<<endl;
}

int main()
{

dynamic ts;
ts.getdata();
ts.sol();
ts.display();
return 0;
}

