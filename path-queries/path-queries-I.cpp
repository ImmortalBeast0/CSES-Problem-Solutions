#include<bits/stdc++.h>
using namespace std;
// Fenwinck Tree + Euler Tour
// Tree Flatting and then Update and Query
#define int long long
#define mod (int)1e9+7
#define inf (int)1e9

#define vi vector<int>
#define vii vector<vi>
#define pi pair<int,int>
#define vpi vector<pi>

#define pb push_back
#define bp pop_back
#define mp make_pair

#define F first
#define S second

#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()

using ll = long long;

int n,q;
vi val;
vii g;

int t = 1;
vi in ,out;
vi depth;

vi BIT;

void update(int id ,int val){
    while(id < sz(BIT)){
        BIT[id] += val;
        id += id & (-id);
    }
}

int query(int id){
    int ans = 0;
    while(id > 0){
        ans += BIT[id];
        id -= id & (-id);
    }
    return ans;
}

void dfs(int u ,int p ,int d){

    in[u] = t;
    t += 1;
    depth[u] = d;

    for(int v : g[u])
        if( v != p)
            dfs(v,u,d+1);

    out[u] = t;
    t += 1;
}


void solve(){
    
    cin >> n >> q;
    val.clear(); val.resize(n+1);
    g.clear();g.resize(n+1);

    t = 1;
    in.clear();in.resize(n+1);
    out.clear();out.resize(n+1);
    depth.clear();depth.resize(n+1,0);

    BIT.clear();BIT.resize(2 * n+1);

    for(int i=1;i<=n;i++)    
        cin >> val[i];
    
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1,0,0);

    for(int i=1;i<=n;i++){
        update(in[i],val[i]);
        update(out[i],-val[i]);
    }

    while(q--){
        int ch;
        cin >> ch;
        if(ch == 1){
            int u,x;
            cin >> u >> x;
            update(in[u],-val[u]);
            update(out[u],val[u]);
            val[u] = x;
            update(in[u],x);
            update(out[u],-x);
        }else{
            int u;
            cin >> u;
            cout << query(in[u]) << endl;
        }
    }

}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    solve();
    return 0;
}