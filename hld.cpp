#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

#define pb push_back
#define mp make_pair

#define N 500000

int Vis[N + 5]={};
int SubTreeSize[N + 5]={};
int ChainNum[N + 5]={};
int chainCount;
vector<int> Chain[N + 5];
vector<int> G[N + 5];

void clearVis()
{
	for (int i=0 ; i<=N ; i++)
		Vis[i] = 0;
}

void clearChain()
{
	for (int i=0 ; i<=N ; i++)
		ChainNum[i] = 0;
	for (int i=0 ; i<=N ; i++)
		Chain[i].clear();
}

/*
*  clearVis();
*  Vis[1] = 1;
*  dfs(1);
*/
void dfs(int node)
{
	SubTreeSize[node] = 1;
	for (int i=0 ; i<G[node].size() ; i++)
		if (Vis[G[node][i]] == 0)
		{
			Vis[G[node][i]] = 1;
			dfs(G[node][i]);
			SubTreeSize[node] += SubTreeSize[G[node][i]];
		}
	return;
}

/*
*  clearVis();
*  clearChain();
*  Vis[1] = ChainNum[1] = chainCount = 1;
*  Chain[1].pb(1);
*  hld(1);
*/
void hld(int node)
{
	if (G[node].size() <= 1)
	{
		//leaf
		return;
	}
	pair<int, int> maxChild = mp(0, 0);
	for (int i=0 ; i<G[node].size() ; i++)
	{
		if (Vis[G[node][i]] == 0 && SubTreeSize[G[node][i]] > maxChild.second)
		{
			maxChild = mp(G[node][i], SubTreeSize[G[node][i]]);
		}
	}
	Vis[maxChild.first] = 1;
	ChainNum[maxChild.first] = ChainNum[node];
	Chain[ChainNum[maxChild.first]].pb(maxChild.first);
	hld(maxChild.first);
	for(int i=0 ; i<G[node].size() ; i++)
	{
		if (Vis[G[node][i]] == 0)
		{
			Vis[G[node][i]] = 1;
			chainCount += 1;
			ChainNum[G[node][i]] = chainCount;
			Chain[ChainNum[G[node][i]]].pb(G[node][i]);
			hld(G[node][i]);
		}
	}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	int n, i, x, y, j;
	cin>>n;
	for (i=1 ; i<n ; i++)
	{
		cin>>x>>y;
		G[x].pb(y);
		G[y].pb(x);
	}
	clearVis();
	Vis[1] = 1;
	dfs(1);
	clearVis();
	clearChain();
	Vis[1] = ChainNum[1] = chainCount = 1;
	Chain[1].pb(1);
	hld(1);

	for (i=1 ; i<=n ; i++)
	{
		cout<<i<<" "<<SubTreeSize[i]<<endl;
	}
	cout<<endl;

	for (i=1 ; i<=chainCount ; i++)
	{
		cout<<"Chain "<<i<<": ";
		for(j=0 ; j<Chain[i].size() ; j++)
		{
			cout<<Chain[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

/*
Test Case
23
1 2
1 3 1 4 1 5
2 6 2 7 2 8 2 9
3 10 4 11
6 12 8 13 8 14 9 15 9 16
13 17 14 18 14 19 15 20 16 21 16 22
21 23
https://blog.anudeep2011.com/heavy-light-decomposition/
*/

