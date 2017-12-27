#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

#define f first
#define s second

const int N = 1e5;

pair<int,int> Input[N+5];
bool Mark[N+5]={};

long long dist(int a, int b)
{
	long long x1 = Input[a].x;
	long long x2 = Input[b].x;
	long long y1 = Input[a].y;
	long long y2 = Input[b].y;
	return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

pair<pair<int,int>,long long> closest_pair(set<int> P, vector<pair<int,int> > X, vector<pair<int,int> > Y)
{
	long long min_dist = 1e18;
	int p1=0, p2=0;
	if(P.size()<=3)
	{
		for(int i=0 ; i<X.size() ; i++)
		{
			for(int j=i+1 ; j<X.size() ; j++)
			{
				if(dist(X[i].s,X[j].s)<min_dist)
				{
					min_dist=dist(X[i].s,X[j].s);
					p1=X[i].s;
					p2=X[j].s;
				}
			}
		}
		return make_pair(make_pair(p1,p2),min_dist);
	}
	int m=X.size()/2;
	set<int> P1, P2;
	vector<pair<int,int> > X1, X2;
	vector<pair<int,int> > Y1, Y2;
	for(int i=0 ; i<X.size() ; i++)
	{
		if(i<m)
		{
			P1.insert(X[i].s);
			X1.push_back(X[i]);
			Mark[X[i].s]=0;
		}
		else
		{
			P2.insert(X[i].s);
			X2.push_back(X[i]);
			Mark[X[i].s]=1;
		}
	}
	for(int i=0 ; i<Y.size() ; i++)
	{
		if(Mark[Y[i].s]==0)
		{
			Y1.push_back(Y[i]);
		}
		else
		{
			Y2.push_back(Y[i]);
		}
	}
	pair<pair<int,int>,long long> result_1 = closest_pair(P1,X1,Y1);
	pair<pair<int,int>,long long> result_2 = closest_pair(P2,X2,Y2);
	pair<pair<int,int>,long long> result = (result_1.s<result_2.s)?result_1:result_2;
	for(int i=0 ; i<Y.size() ; i++)
	{
		for(int j=i+1 ; j<Y.size() && j<=i+7 ; j++)
		{
			if(dist(Y[i].s,Y[j].s)<result.s)
			{
				result.s=dist(Y[i].s,Y[j].s);
				result.f.f=Y[i].s;
				result.f.s=Y[j].s;
			}
		}
	}
	return result;
}

int main()
{
	int n;
	int p,q;
	set<int> P;
	vector<pair<int,int> > X, Y;
	cin>>n;
	for(int i=1 ; i<=n ; i++)
	{
		cin>>p>>q;
		P.insert(i);
		X.push_back(make_pair(p,i));
		Y.push_back(make_pair(q,i));
		Input[i]=make_pair(p,q);
	}
	pair<pair<int,int>,long long> result = closest_pair(P,X,Y);
	cout<<"Shortest Distance = "<<result.s<<endl;
	cout<<"Point 1 : "<<Input[result.f.f].f<<" "<<Input[result.f.f].s<<endl;
	cout<<"Point 2 : "<<Input[result.f.s].f<<" "<<Input[result.f.s].s<<endl;
	return 0;
}
