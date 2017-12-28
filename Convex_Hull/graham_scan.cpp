#include <bits/stdc++.h>

using namespace std;

#define pi 3.141592653589793238
#define x first
#define y second
#define f first
#define s second
#define mp make_pair

typedef pair<int,int> point;
typedef pair<point,point> line;

int cross_product(line a, line b)
{
	return (a.f.x-a.s.x)*(b.f.y-b.s.y) - (b.f.x-b.s.x)*(a.f.y-a.s.y);
}

bool counter_clockwise_turn(point p1, point p2, point p3)
{
	return (cross_product(mp(p2,p1),mp(p3,p1)) > 0);
}

double dist(point p1, point p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

bool cmp1(point a, point b)
{
	if(a.y<b.y)
		return 1;
	if(a.y==b.y && a.x<b.x)
		return 1;
	return 0;
}

point pivot;

bool cmp2(point a, point b)
{
	int c = cross_product(mp(a,pivot),mp(b,pivot));
	if(c==0)
	{
		return (dist(pivot,a) < dist(pivot,b));
	}
	return (c>0);
}

vector<point> V, V1;
vector<point> Output;
stack<point> S;

int main()
{
	int n;
	point p;
	cin>>n;
	for(int i=0 ; i<n ; i++)
	{
		cin>>p.x>>p.y;
		V.push_back(p);
	}
	sort(V.begin(),V.end(),cmp1);
	pivot = V[0];
	V1.push_back(pivot);
	for(int i=1 ; i<V.size() ; i++)
	{
		if(V[i]!=V[i-1])
			V1.push_back(V[i]);
	}
	V=V1;
	sort(V.begin()+1,V.end(),cmp2);
	V.push_back(pivot);
	S.push(V[0]);
	S.push(V[1]);
	point prev = V[0];
	point curr = V[1];
	point next;
	int k=2;
	while(k<V.size())
	{
		next = V[k];
		if(counter_clockwise_turn(prev,curr,next))
		{
			S.push(next);
			prev=curr;
			curr=next;
		}
		else
		{
			S.pop();
			S.push(next);
			curr=next;
		}
		k++;
	}
	S.pop();
	while(!S.empty())
	{
		Output.push_back(S.top());
		S.pop();
	}
	reverse(Output.begin(),Output.end());
	cout<<Output.size()<<endl;
	for(int i=0 ; i<Output.size() ; i++)
	{
		cout<<Output[i].x<<" "<<Output[i].y<<endl;
	}
	return 0;
}
