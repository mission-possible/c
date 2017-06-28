//Find the largest continuous sequence in a array which sums to zero.

vector<int> lszero(vector<int> &sequence) {
        
        int N = sequence.size();
        vector<int> sum;
        if(N == 0)
                return sum; // empty vector

        sum.push_back(sequence[0]);

        for(int i = 1; i < N; ++i) {
            sum.push_back(sequence[i] + sum[i - 1]);
        }
        
        int start = 0;
        int end = 0;
        map<int, int> hash;
        for(int i = 0; i < N; ++i) {
            if(sum[i] == 0) {
                int temp_start = 0;
                int temp_end = i + 1;
                if(temp_end - temp_start >= end - start) {
                    start = temp_start;
                    end = temp_end;
                } 
            } else {
                if(hash.find(sum[i]) != hash.end()) {
                    int temp_start = hash[sum[i]] + 1;
                    int temp_end = i + 1;
                    if(temp_end - temp_start > end - start) {
                        start = temp_start;
                        end = temp_end;                  
                    } else if(temp_end - temp_start == end - start && temp_start < start) {
                        start = temp_start;
                        end = temp_end;
                    }
                } else {
                    hash[sum[i]] = i;
                }
            }
        }

        vector<int> ans;

        for(int i = start; i < end; ++i) {
            ans.push_back(sequence[i]);
        }

        return ans;
    }
    
    
