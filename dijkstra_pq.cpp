#include<bits/stdc++.h>
using namespace std;
 
#define ll long long 
#define rep(i,n) for (int i=0; i<n; i++)
typedef vector<vector<ll> >matrix;
const ll mod=1e9+7;
#define f first
#define s second
 
int main()
{
	int t; t=1;
	while(t--)
	{
		ll n,m,r,x,y; cin>>n>>m>>r>>x>>y;
		vector<pair<ll,ll>>adj[n+1];
		rep(i,r) 
		{
			ll u,v,w; cin>>u>>v>>w;
			adj[u].push_back({v,w});
			adj[v].push_back({u,w});
		}
		priority_queue<pair<ll,ll>>pq;
		ll d[n+1]; ll v[n+1];
		rep(i,n+1) { d[i]=INT_MAX; v[i]=0; }
		d[x]=0;
		pq.push({-0,x});
		while(!pq.empty())
		{
			pair<ll,ll>fr=pq.top(); pq.pop();
			if(v[fr.s]) continue;
			v[fr.s]=1;
			for(auto u:adj[fr.s])
			{
				if(d[u.f]>d[fr.s]+u.s)
				{
					d[u.f]=d[fr.s]+u.s;
					pq.push({-d[u.f],u.f});
				}
			}
		}
		//for(auto u:d) cout<<u<<" ";
		if(d[y]<=m) cout<<"alive "<<d[y];
		else cout<<"died";
	}
	return 0;
}
