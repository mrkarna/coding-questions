//https://practice.geeksforgeeks.org/problems/subset-sum-problem/0

// 1<=n<=100; 0<=a[i]<=1000;
//find if a can b divided into 2 subsets of equal sum

//////***************************************************/////
//The point is in initialising the dp array ..
// If it is kept in integer type solution is not accepted because of segment.. fault,
// bcoz that much space is not available on stack //////////


/// To overcome this problem----
//1. Either keep dp array in integer type, then initialise it outside main
//2. Or keep dp array bool type, this reduces a lot of memory space, now it can be 
///  inside or outside main.



#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i,n) for(ll i=0; i<n; i++)

int main()
{
	ll T; cin>>T;
	while(T--)
	{
		ll n; cin>>n;
		ll s=0;
		ll a[n]; rep(i,n) { cin>>a[i]; s+=a[i]; } sort(a,a+n);
		bool dp[n][s+1];										//
		rep(i,n) dp[i][0]=1;
		rep(i,s+1) { if(i==0) continue; dp[0][i]=a[0]==i?1:0; }
		
		for(ll i=1; i<n; i++)
		for(ll j=1; j<=s; j++)
		{
			if(a[i]>j) dp[i][j]=dp[i-1][j];
			else dp[i][j]=(dp[i-1][j] || dp[i-1][j-a[i]]);
		}
		
		bool ans=false;
		if(s%2) cout<<"NO"<<endl;
		else
		{
			rep(i,n) if(dp[i][s/2]) ans=true;
			if(ans) cout<<"YES"<<endl; else cout<<"NO"<<endl;
		}
		//rep(i,s+1) cout<<i<<' '; cout<<endl;
		//rep(i,n)  { rep(j,s+1) cout<<dp[i][j]<<' '; cout<<endl; }
	}
	return 0;
}
