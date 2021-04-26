#include <bits/stdc++.h>
using namespace std;

vector<int> func(vector<int> &v){
  int n= v.size();
  int r = 0;
  while(pow(2,r)<r+n+1) r++;
  vector<int> cnt(r,0);int z=1;int q=0;
  for(int i=1;i<=r+n;i++){
    int t= i,k=0;
    if(i==z){z*=2;continue;}
    while(t && v[q]){
      if(t&1 && v[q]) cnt[k]++;
      t >>= 1;k++;
    }
    q++;
  }
  vector<int> ans(n+r);
  cout << "Correct Hamming Code" << endl;
  int j=0,k=0,p=1;
  for(int i=1;i<=r+n;i++){
    if(i==p){p*=2;ans[i-1] = cnt[j]%2 ;j++;}
    else ans[i-1] = v[k++];


  }

  return ans;
}

int func2(vector<int> &v){
  int n= v.size();
  map<int,int> cnt;
  for(int i=0;i<n;i++){
    int t= i+1,k=0;
    while(t && v[i]){
      if(t&1 && v[i]) cnt[k]++;
      t >>= 1;k++;
    }
  }
  int ans = 0;
  for(auto it : cnt){
    if(it.second%2){ans += pow(2,it.first);}
  }
  return ans;
}

int main(){
  int n;cin >> n;
  vector<int> v(n);
  for(int i=n-1;i>=0;i--) cin >> v[i];
  vector<int> ans = func(v);

  for(int i=ans.size()-1;i>=0;i--){
    cout << ans[i] << " ";
  }
  cout << endl;

  cout << "Enter the bit number to change" << endl;
  int x;cin >> x;
  ans[x-1] = 1-ans[x-1];

  for(int i=ans.size()-1;i>=0;i--){
    cout << ans[i] << " ";
  }
  cout << endl;

  cout << "Wrong number : " << func2(ans)  << endl;
}
