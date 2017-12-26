#include <bits/stdc++.h>

using namespace std;

#define MAX int(1e7)

bool Mark[MAX+5]={1,1};
vector<int> Primes;

void sieve()
{
	int i;
	for(i=2;i*i<=MAX;i++)
	{
		if(Mark[i]==0)
		{
			Primes.push_back(i);
			for(int j=i*i ; j<=MAX ; j+=i)
			{
				Mark[j]=1;
			}
		}
	}
	for(; i<=MAX ; i++)
	{
		if(Mark[i]==0)
		{
			Primes.push_back(i);
		}
	}
	return;
}

int main()
{
	sieve();
	for(int i=0;i<Primes.size();i++)
	{
		cout<<Primes[i]<<" ";
	}
	cout<<endl;
	return 0;
}
