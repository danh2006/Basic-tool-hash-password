#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const int base =  97 ;
const int MOD_BASE = pow(10, 9) + 7;
const int64_t MOD = (1LL << 61) - 1;

auto convert(char& c){
   if(c >= 'A' && c <= 'Z') return (c - 'A');
   if(c >= 'a' && c <= 'z') return (c - 'a');
   if(c >= '0' && c <= '9') return (c - '0');
   return (int)(c);
}

bool needIgnore(char c){
   if(c < 0 && c > 122) return true;
   return !((isdigit(c)) || 
            (isalpha(c)) ||
            (c == 64));
}


void solve(string& s){ 
   int n = s.size();
   s = " " + s;

  vector<int64_t> Hash(n+2);
  vector<int64_t> Pow(n+1);
  Pow[0] = 1, Hash[0] = 1; Hash[n+1] = 1;
  for(int i = 1; i <= n; ++i){
     Pow[i] = (Pow[i - 1] * base) % MOD_BASE;
  }
  vector<string> saveHashValue;
  for(int times = 1; times <= 30; ++times){
  for(int i = 1; i <= n; ++i){
     Hash[i] = (((__int128)(Hash[i - 1]) * Pow[i] + convert(s[i]))*times + (Hash[i] % MOD_BASE)) % MOD;
  }
  for(int i = n; i >= 1; --i){
     Hash[i] = ((__int128)(Hash[i + 1]) * Pow[n - i] * times + Hash[i]) % MOD;
     saveHashValue.push_back(to_string(Hash[i] + times + i));
  }
 }
  string ans;
  for(auto& val : saveHashValue){
     for(int i = 0; i < val.size() - 1; ++i){
        int tmp = abs(stoi(val.substr(i, 2)));
        ans += static_cast<char>(tmp);
     }
  }
  reverse(ans.begin(), ans.begin() + ans.size() / 3);
  reverse(ans.begin() + 2*ans.size() / 5,  ans.end());
  int midPos = 2*ans.size() / 7;
  int curPos = max(0, midPos - 9);
  int count = 0;
  string done;
  while(curPos++ < ans.size() && count < 18) {
     if(needIgnore(ans[curPos])) continue;
     done += ans[curPos];
     count++;
  }
  cout << done << endl;
}
signed main(){
   string s;
   while(getline(cin, s)){
       solve(s);  
   }
}
