#include<bits/stdc++.h>
using namespace std;

int64_t bit[10000001];

void update(int64_t bit[], int64_t x, int val)
{
	for( ; x<=10000000; x+=x&(-x))
	bit[x]+=val;
}

int64_t query(int64_t bit[], int64_t x)
{
	int64_t sum=0;
	for( ; x>=1; x-=x&(-x))
	sum+=bit[x];
	return sum;
}

int main()
{
	int t;
	cin>>t;
	for(int it=0; it<t; it++)
	{
		for(int i=0; i<10000000; i++) bit[i]=0;
		int64_t ans=0;
		int n; cin>>n;
		int a[n];
		
		for(int i=0; i<n; i++) cin>>a[i];
		
		for(int i=n-1; i>=0; i--) 	
		{
			update(bit, a[i], 1);
			ans+=query(bit, a[i]-1);
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
		
