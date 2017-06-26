//Without back tracking
bool compar(const vector<int> &a,const vector<int> &b){
    if(a.size()==0)return true;
    if(b.size()==0)return false;
    if(a.at(0)<b.at(0))return true;//without line 3 and 4, this will cause segmentation fault if anyone of the vector is empty
    if( a.at(0)==b.at(0)){
        int i=0;
        while(i<a.size() && i<b.size() && a.at(i)==b.at(i)){
            i++;
        }
        if(i>=a.size())return true;
        if(i>=b.size())return false;
        if(a.at(i)<b.at(i))return true;
    }
    return false;
}
vector<vector<int> > Solution::subsets(vector<int> &A) {
    int n=pow(2,A.size());
    sort(A.begin(),A.end());
    vector<vector<int> > res(n);
    int j,k;
    for(int i=0;i<n;++i){
        curr.clear();
        j=i;k=0,c=0;
        if(k<A.size() && j%2==1){
            res[i].push_back(A[k]);
            j=j>>1;
            k++;
        }
        while(k<A.size() && j>0){
            if(j%2==1){
                res[i].push_back(A[k]);
            }
            k++;
            j=j>>1;
        }
    }
    sort(res.begin(),res.end(),compar);
    return res;
}
