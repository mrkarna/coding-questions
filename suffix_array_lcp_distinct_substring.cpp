// Accepted on Interesting Strings : Hackerearth
// Not accepted on Disubstr : Spoj

// So, there must be some fault with the code....

// The problem is to distinct substrings of given string

#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second

bool mycmp(pair<int,pair<int,int>>p1, pair<int,pair<int,int>>p2)
{
    if((p1.fi<p2.fi) || (p1.fi==p2.fi && p1.se.fi<p2.se.fi)) return true;
    return false;
}

vector<long long int> kasai(string s, vector<long long int> sa)
{
    int n=s.size(),k=0;
    vector<long long int> lcp(n,0);
    vector<long long int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(rank[i]==n-1) {k=0; continue;}
        int j=sa[rank[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[rank[i]]=k;
    }
    return lcp;
}

int main()
{
    int T; cin>>T;
    while(T--)
    {
        string s; cin>>s;
        long long int n=s.size();
        if(n==1) {cout<<"1\n"; continue; }

        long long int a[n][int(ceil(log2(n)))+1];
        
        vector<pair<int,int>>temp(n);
        for(int i=0; i<n; i++) temp[i]=make_pair(int(s[i]),i);
        sort(temp.begin(),temp.end());
        int give=0,last=temp[0].fi; a[temp[0].se][0]=0;
        for(int i=1; i<n; i++)
        {
            if(temp[i].fi==last) a[temp[i].se][0]=give;
            else { a[temp[i].se][0]=++give; last=temp[i].fi; }
        }

        //for(auto u:temp) cout<<u.fi<<","<<u.se<<" % "; cout<<endl;
        //for(int i=0; i<n; i++) cout<<a[i][0]<<" & "; cout<<endl;
        
        for(int j=1; j<int(ceil(log2(n)))+1; j++)
        {
            vector<pair<int,pair<int,int> >>v;
            for(int k=0; k<n; k++)
            {
                int x,y;
                x=a[k][j-1];
                if(k+j<n) y=a[k+j][j-1]; else y=-1;
                v.push_back({x,{y,k}});
            }
            sort(v.begin(),v.end());//,mycmp);                          // Compare function is not necessary to write
            long long int assign=0;
            int lx, ly; a[v[0].se.se][j]=0; lx=v[0].fi; ly=v[0].se.fi;
            for(int i=1; i<n; i++)
            {
                if(v[i].fi==lx && v[i].se.fi==ly)
                {
                    a[v[i].se.se][j]=assign;
                }
                else
                {
                    a[v[i].se.se][j]=++assign;
                    lx=v[i].fi;
                    ly=v[i].se.fi;
                }
            } 
        }

        vector<long long int>sfa(n);                        
        for(int i=0; i<n; i++) sfa[a[i][int(ceil(log2(n)))]]=i;  //for(auto u:sfa) cout<<u<<" "; cout<<endl;
        vector<long long int>lcp=kasai(s,sfa);
        long long sum=0; for(int i=0; i<n; i++) sum+=lcp[i];     // for(auto u:lcp) cout<<u<<" "; cout<<endl;
        long long ans=(n*(n+1)/2)-sum;
        cout<<ans<<endl;
    }
    return 0;
}
