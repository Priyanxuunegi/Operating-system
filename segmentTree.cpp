#include<bits/stdc++.h>
using namespace std ; 

int build(vector<int> &segtree , int sl , int sr , vector<int> &a , int index){
    if(sl == sr){
        segtree[index] = a[sl] ; 
        return segtree[index] ; 
    }
    int mid = (sl + sr) /2 ; 
    segtree[index] = build(segtree, sl , mid , a , 2 * index+1) + build(segtree , mid + 1 , sr , a , 2 * index + 2);
    return segtree[index] ;
}
void buildtree(vector<int> &segtree , int s , vector<int> &a , int n){
    build(segtree , 0 , n-1 , a , 0) ; 
}
void updateutil(vector<int> &segtree , int sl , int sr , int newval , int index , int i)
{
    if(index >= sl && index <= sr){
        segtree[i] += newval ;; 
        if(sl == sr) return ; 

        int mid = ( sl + sr) / 2 ; 
        updateutil(segtree, sl , mid ,newval ,index , 2 * i + 1) ; 
        updateutil(segtree , mid + 1 , sr , newval , index , 2 *i + 2) ;
    }
    return ; 
}
void update(vector<int> &segtree ,int n , int newval , int index){
    updateutil(segtree , 0 , n - 1  ,newval , index , 0) ; 
}

int rangeS(vector<int> &segtree , int sl , int sr ,int ql  , int qr, int i){
    if(qr < sl || sr <= ql) return 0 ; 

    else if(ql <= sl && sr <= qr)
     return segtree[i] ; 

    else {
        int mid = (sl + sr) / 2 ; 
        return rangeS(segtree , sl , mid , ql , qr , 2 * i + 1) + rangeS(segtree , mid + 1 , sr , ql , qr , 2 * i + 2) ;
    }
}


int main(){
  int n ; 
  cin >> n ; 
  vector<int> a(n) ; 
  for(int i = 0 ; i < n ; i++)cin >> a[i] ;

  size_t s = pow(2,ceil(log2(n) +1)) - 1 ;  
  vector<int> segtree(s,0) ; 
  buildtree(segtree,s,a,n) ; 
  for(int i = 0 ; i < s ; i++)
   cout << segtree[i] << "  " ; 
   
   cout << endl ; 
   int Q ; 
   int l , r , index , val , ch ;
   cin >> Q ; 
   while(Q--){
       cin >> ch ;
       if(ch == 1){
        cin >> index >> val ;
        int newval = abs(val - a[index]) ; 
        update(segtree,n,newval,index) ; 
       }
       else if(ch ==2){
        cin >> l >> r ;
        cout << rangeS(segtree,0,n-1,l,r,0) << endl ; 

       }
   }

return 0 ; 
}