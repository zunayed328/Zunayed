#include<bits/stdc++.h>
#define rp(i,a,b) for(int i=a;i<=b;++i)
#define pr(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back
using namespace std;

const int mod=998244353;
typedef long long ll;
void upd(int &x,ll y){
    x=(x+y)%mod;
}

struct mat{
    int z[2][2];
    mat(){
        memset(z,0,sizeof(z));
    }
    void set(int i,int j,int v){
        z[i][j]=v;
    }
    mat operator*(const mat &o)const{
        mat x;
        rp(i,0,1)rp(j,0,1)rp(k,0,1)upd(x.z[i][k],1ll*z[i][j]*o.z[j][k]);
        return x;
    }
};

mat A;

void init_mat_A(){
    A.set(0,0,1);
    A.set(0,1,2);
    A.set(1,0,1);
    A.set(1,1,0);
}

mat ksm(mat a,ll k){
    mat b;
    b.set(0,0,1);
    b.set(1,1,1);
    for(;k;k>>=1,a=a*a){
        if(k&1)b=a*b;
    }
    return b;
}

int ksm(int a,ll k){
    int b=1;
    for(;k;k>>=1,a=1ll*a*a%mod){
        if(k&1)b=1ll*a*b%mod;
    }
    return b;
}

int calc(ll n){
    if(n<3)return 0;
    mat a=ksm(A,n-3);
    int x=(a.z[0][0]+a.z[0][1])*2ll%mod;
    return x;
}

#define fi first
#define se second

/*
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>

*/

const int N=5e5+5;
int n,m,C,D,f[N],mrk[N];
ll d[N];
vector<pair<int,int>> g[N];
void dfs(int u,int fa){
    f[u]=fa;
    for(auto p:g[u]){
        int v=p.fi;
        if(!d[v]){
            d[v]=d[u]+1+p.se;
            dfs(v,u);
        }else if(v!=fa&&d[v]<d[u]){
            for(int i=u;i!=v;i=f[i]){
                mrk[i]=1;
            }
            C=1ll*C*calc(d[u]-d[v]+1+p.se)%mod;
            D=2*D%mod;
        }
    }
}
int main(){

    init_mat_A();

    scanf("%d%d",&n,&m);
    if((n+m)&1){
        puts("0"),exit(0);
    }
    rp(i,1,m){
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        g[x].pb({y,w});
        g[y].pb({x,w});
    }
    d[1]=1;
    C=1;
    D=1;
    dfs(1,0);
    rp(i,2,n)if(!mrk[i]){
        C=1ll*C*ksm(2,d[i]-d[f[i]])%mod;
    }
    C=3ll*C%mod;
    int ans=1ll*C*D%mod;
    printf("%d\n",ans);
    return 0;
}

/*
ALL TEST CASES SHOUD PASS HERE
*/
