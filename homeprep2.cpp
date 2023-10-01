#include <bits/stdc++.h>


using namespace std;
#define int long long
const int mnogo = 2*1e9;
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
int mod =  2147483647;
int ch = 239;
int pr(int  a, int b){
    return ((a%mod)*(b%mod))%mod;
}
int plu(int a, int b){
    return ((a%mod)+(b%mod))%mod;
}
int po(int a, int n){
    if(n==0) return 1;
    if(n%2==0){
        int tmp = po(a,n/2);
        return pr(tmp,tmp);
    }
    else {
        return pr(a,po(a,n-1));
    }
}
int del(int a, int b){
    return pr(a,po(b,mod-2));
}
int minu(int a, int b){
    return plu(a, mod-b);
}

void out_pec(vector<pii> a){
    for(pii x: a){
        cout << x.f << ' ' << x.s << '\n';
    }
}
void out_vec(vector<int> a){
    for(int x: a){
        cout << x << ' ';
    }
    cout << '\n';
}
void out_wec(vector<vector<int>> a){
    for(vector<int> x:a){
        out_vec(x);
    }
    cout << '\n';
}
int powers[100000];
void solve1(){
    int n,m;
    cin >> n;
    m=n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
   vector<int> b(n);
   b=a;
   sort(b.begin(),b.end());
   b.erase(unique(b.begin(),b.end()),b.end());
   b.shrink_to_fit();
   m = b.size();
    int dp[n+1][m+1];
    vector<vector<pii>> prev(n+1, vector<pii>(m+1));

    for(int i = 0; i <= m; ++i){
        dp[0][i] = 0;
    }
    for(int i = 0; i <= n; ++i){
        dp[i][0] = 0;
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            if(dp[i][j] == dp[i-1][j]){
                prev[i][j] = mp(i-1,j);
            }
            else {
                prev[i][j] = mp(i,j-1);
            }
            if(a[i-1] == b[j-1]){
                dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
                if(dp[i][j] == dp[i-1][j-1]+1){
                    prev[i][j] = mp(i-1,j-1);
                }

            }
        }
    }
    cout << dp[n][m] << '\n';
    vector<int> ans;
    int nowi = n, nowj = m;
    pii tmp;
    while(nowi > 0 && nowj > 0){
      //  cerr << nowi << ' ' << nowj << '\n';
        tmp = prev[nowi][nowj];
        if(dp[nowi][nowj] != dp[tmp.f][tmp.s]){
            ans.pb(a[nowi-1]);
        }
        nowi = tmp.f;
        nowj = tmp.s;
    }
    reverse(ans.begin(),ans.end());
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << ' ';
    }
}
void solve2(){
    string x,y;
    cin >> x>> y;
    int n = x.size();
    int m = y.size();
    vector<int> a(n);
    vector<int> b(m);
    for(int i = 0; i < n; ++i){
        a[i] = (int)(x[i]-'A');
    }
    for(int i = 0; i < m; ++i){
        b[i] = (int)(y[i] - 'A');
    }
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        dp[i][0] = i;
    }
    for(int i = 1; i <= m; ++i){
        dp[0][i] = i;
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else {
                dp[i][j]= min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]) + 1;
            }
        }
    }
  //  out_wec(dp);
    cout << dp[n][m];

}
void solve3(){
    string s;
    cin >> s;
    int n = s.size();
    vector<int> p(n,0);
    int k;
    for(int i = 1; i < n; ++i){
        k = p[i-1];
        while(s[i] != s[k] && k > 0){
            k = p[k-1];
        }
        if(s[i] == s[k]) k++;
        p[i] = k;
    }
    for(int i = 0; i < n; ++i){
        cout << p[i] << ' ';
    }
    cout << '\n';
}
void solve4(){
    string s;
    cin >> s;
    int  m = s.size();
    int ans = 0;
    int ma = 0;
    int n;
    for(int q = 0; q < m; ++q){
        n = q+1;
        vector<int> p(n,0);
        int k;
        for(int i = 1; i < n; ++i){
        k = p[i-1];
        while(s[n-1-i] != s[n-1-k] && k > 0){
            k = p[k-1];
        }
        if(s[n-1-i] == s[n-1-k]) k++;
        p[i] = k;
        }
        ma = 0;
        for(int i = 1; i < n; ++i){
            ma = max(ma,p[i]);
        }
        ans += n-ma;
    }
    cout << ans-1;
}
void solve5(){
    string a;
    cin >> a;
    int n = a.size();
    int z[n];
    z[0] = 0;
    int x = 0, y = 0, nol = 0;
    for(int k= 1; k < n; ++k){
        //cerr << i << ' ' << x << ' ' << y << "!\n";
        z[k] = max(nol,min(y-k,z[k-x]));
        while(k+z[k] < n && a[z[k]] == a[k+z[k]]){
            z[k]++;
        }
        if(k+z[k] > y){
            x = k;
            y = k+z[k];
        }
    }
    vector<int> ans;
    for(int i = 1; i < n; ++i){
        if(z[i] == n-i){
            ans.push_back(z[i]);
        }
    }
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << '\n';
    }
}
void solve6(){
    int q;
    cin >> q;
    string s;
    cin >> s;
    int n = s.size();
    int a[n];
    for(int i = 0; i < n; ++i){
        a[i] = (int)(s[i]-'a'+1);
    }
    vector<int> _hash(n);
    _hash[0] = a[0];
    for(int i = 1; i < n; ++i){
        _hash[i] = plu(pr(_hash[i-1],ch),a[i]);
    }

    string x;
    int b[n];
    int m;
    int whash;
   // out_vec(_hash);
    for(int qqq = 0; qqq < q; ++qqq){
        cin >> x;
        m = x.size();
        for(int i = 0; i < m; ++i){
            b[i] = (int)(x[i]-'a'+1);
        }
        whash = b[0];
        for(int i = 1; i < m; ++i){
            whash = plu(pr(whash,ch),b[i]);
        }
        bool f = true;
        for(int i = 0; i < n-m; i++){
          // cerr << whash << '\n';

            if((i==0 && whash == _hash[m-1]) || minu(_hash[i+m-1],pr(powers[i],_hash[i-1])) == whash){
                cout << "YES\n";
                f =false;
                break;
            }
           if(i!=0) whash = pr(whash,ch);
        }
        if(f)cout << "NO\n";
    }
}
int hashes[100001];
int sufhashes[100001];
bool iseq(int l1, int r1, int l2, int r2, int n){
    int hash1 = minu(hashes[r1+1],pr(hashes[l1],powers[n-l1]));
    int hash2 = minu(sufhashes[l2],pr(sufhashes[r2+1],powers[n-r2-1]));
    return(pr(hash1,powers[n-r2-1]) == pr(hash2,powers[n-l1]));
}
int bin_search(string s, int shift, int c){
    int l = -1, r = min(c, (int)s.size()-c+shift);
    int m = 0;

    while(r-l > 1 && c+shift+m < s.size()){
        m = (l+r-1)/2;
        if(iseq(c-m,c,c+shift,c+shift+m,(int)s.size())){
            l = m;
        }
        else {
            r = m;
        }
    }
    return r;
}
void solve7(){
    powers[0] = 1;
    for(int i = 1; i < 100000; ++i){
        powers[i] = pr(powers[i-1],ch);
    }
    string s;
    cin >> s;
    int n = s.size();
    int ans = 0;
    hashes[0] = 0;
    for(int i = 1; i <= n; ++i){
        hashes[i] = plu(pr(hashes[i-1],ch),(int)(s[i-1]-'a'+1));
    }
    sufhashes[n] = 0;
    for(int i = n-1; i > -1; i--){
        sufhashes[i] = plu(pr(sufhashes[i+1],ch), (int)(s[i]-'a'+1));
    }
   /* for(int i = 0; i <= n; ++i){
        cerr << hashes[i] << ' ';
    }
    cerr << '\n';
    for(int i = 0; i <= n; ++i){
        cerr << sufhashes[i] << ' ';
    } */
    for(int i = 0; i < n; ++i){
        ans+=bin_search(s,0,i)+bin_search(s,1,i);
        cerr << i << ' ' << bin_search(s,0,i) << ' ' << bin_search(s,1,i) << "!\n";
    }
    cout << ans;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
  //  cin >> t;
    while(t--){
        solve7();
    }

}
