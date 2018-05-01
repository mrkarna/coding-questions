#include<bits/stdc++.h>
using namespace std;

void dfs(int s, int visited[], vector<int> adj[])
{	
	if(visited[s]) return;
	visited[s]=1;
	for(auto u: adj[s]) dfs(u, visited, adj);
}

int main()
{
	int n, m;
	cin>>n>>m;
	int visited[n+1]={0};
	vector<int> adj[n+1];
	
	for(int i=0; i<m; i++)
	{
		int x, y;
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	dfs(1, visited, adj);
	
	int ans=0;
	for(int i=1; i<=n; i++)
	if(visited[i]!=1) ans++;
	
	if(ans==0 && m==n-1) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
