#include <bits/stdc++.h>
using namespace std;

class node{
  public:
  int maxweight;
  unordered_map<char,node*> M;
  node(){
    maxweight=0;
  }
};

class trie{
  public:
  node *root;
  trie(){
  root=new node;
  }

  void insert(string str,int weight){
    node *temp=root;
    for(int i=0;i<str.size();i++){
     auto it=temp->M.find(str[i]);
    if(it!=temp->M.end())
      temp=it->second;
    else{
      node *newnode=new node;
      temp->M.insert(make_pair(str[i],newnode));
      temp=newnode;
    }
    temp->maxweight=max(temp->maxweight,weight);
    }
  }

  void search(string str){
    node *temp=root;
    for(int i=0;i<str.size();i++){
      auto it=temp->M.find(str[i]);
      if(it!=temp->M.end())
        temp=it->second;
      else{
        cout<<"-1"<<endl;
        return;
      }
    }
    cout<<temp->maxweight<<endl;
  }
};

int main(){
  int N,Q;
  cin>>N>>Q;
  string str;
  int weight;
  trie T;
  for(int i=0;i<N;i++){
    cin>>str>>weight;
    T.insert(str,weight);
  }
  while(Q--){
    cin>>str;
    T.search(str);
  }
  return 0;
}
