#include <iostream>
#include <vector>
#include<cmath>
#include<string>
using namespace std;
//重载输出
ostream& operator<< (ostream& out, vector<int>& vec) {
        vector<int>::reverse_iterator it = vec.rbegin();
        for(;it!=vec.rend();++it)if(*it !=0)break;
        for(; it != vec.rend(); ++it)
                out << *it;
        out<<endl;
        return out;
}
//保证长度为2^n
vector<int> correct(vector<int>&vec){
        int len = vec.size(),t=0;
        for(int i=0;i<len;i++)if(vec[i]==0)t++;
        if(t==len){
            vector<int> res;
            res.push_back(0);
            return res;
        }
        int lg = log2(len+0.5), pw = pow(2.0, lg);
        if(len > pw){
              int needzero = pow(2.0,lg+1)-len;
              while(needzero--)vec.push_back(0);
        }
        return vec;
}
//重载输入
istream& operator >> (istream & in, vector<int>& vec){
       string s;
       in>>s;
       string::reverse_iterator it = s.rbegin();
       while(it!=s.rend())vec.push_back((*it++)-'0');
       correct(vec);
       return in;
}
//  将vec左移m位（比如十进制数23左移2位得到2300）
vector<int> shift (vector<int> &vec, int m){
         vector<int>res;
         while(m--)res.push_back(0);
          vector<int>::iterator it = vec.begin();
          for(;it!=vec.end();it++)res.push_back(*it);
         return res;
}
//重载加法
vector<int> operator + (vector<int>& a, vector<int>& b){
        vector<int> c;
        int lena = a.size(), lenb = b.size(), k=0,m,n;
        while(k<lena || k<lenb){
              m = k<lena ? a[k] : 0;
              n  = k< lenb ? b[k] : 0;
              k++;
              c.push_back(m+n);
        }
        for(int i=0;i<k;i++){
                if(c[i]>9){
                       if(i+1<k){
                            c[i+1] += c[i]/10;
                       }else{
                            c.push_back(c[i]/10);
                       }
                       c[i] = c[i]%10;
                }
        }
        return correct(c);
}
//重载比较运算符
bool operator < (vector<int> &a, vector<int> &b){
        int lena = a.size(), lenb = b.size();
        if(lena==lenb){
             for(int i=lena-1; i>=0;i--){
                     if(a[i]==b[i])continue;
                     else return a[i]<b[i];
             }
        }else {
             return lena<lenb;
        }
}
//重载减法
vector<int> operator - (vector<int>& a, vector<int>& b){
//a>b
       vector<int> c;
       int lena = a.size(), lenb = b.size(),k=0,m,n;
       while(k<lena || k<lenb){
            m = k<lena ? a[k] : 0;
            n  = k<lenb ? b[k] : 0;
            k++;
            c.push_back(m-n);
       }
       for(int i=0;i<k;i++){
             if(c[i]<0){
                  c[i+1]--;
                  c[i]+=10;
                  if(i+1==k-1&&c[i+1]==0)c.erase(c.begin()+k-1);
             }
       }
       return correct(c);
}
//拷贝子数组
vector<int> copy(vector<int>&vec, int start, int length){
        vector<int> res;
        vector<int>::iterator it = vec.begin() + start;
        for(int i=0; i<length; i++){
                res.push_back(*it++);
        }
        return res;
}
//分治求大整数
vector<int> DivideAndConque(vector<int> &a, vector<int>&b){
       int lena = a.size(), lenb = b.size();
       if(lena!=lenb){
               if(lena>lenb){
                       int t = lena - lenb;
                       while(t--)b.push_back(0);
               }else{
                       int t = lenb-lena;
                       while(t--)a.push_back(0);
               }
       }
       int len = a.size();
       if(len==1){
               vector<int> res;
               res.push_back(a[0]*b[0]);
               if(res[0]>9){
                    res.push_back(res[0]/10);
                    res[0] = res[0]%10;
               }
               return res;
       }
       vector<int> B = copy(a, 0, len/2);
       vector<int> A = copy(a, len/2, len/2);
       vector<int> D = copy(b, 0, len/2);
       vector<int> C = copy(b,len/2,len/2);
       vector<int>AC = DivideAndConque(A,C);
       vector<int>BD = DivideAndConque(B,D);
       vector<int>mid;
       vector<int>tmp1 = AC+BD;
       if(A<B){
            vector<int>B_A = B - A;
             if(D<C){
                    vector<int>C_D = C - D;
                    vector<int>tmp2 = DivideAndConque(B_A,C_D);
                    vector<int>tmp3 = tmp1+tmp2;
                    mid = shift(tmp3,len/2);
             }else{
                    vector<int>D_C = D-C;
                    vector<int>tmp2 = DivideAndConque(B_A,D_C);
                    vector<int>tmp3 = tmp1-tmp2;
                    mid = shift(tmp3,len/2);
             }
       }else{
           vector<int>A_B = A-B;
            if(D<C){
                 vector<int>C_D = C - D;
                 vector<int>tmp2 = DivideAndConque(A_B,C_D);
                 vector<int>tmp3 = tmp1-tmp2;
                 mid = shift(tmp3,len/2);
            }else{
                 vector<int>D_C = D-C;
                 vector<int>tmp2 = DivideAndConque(A_B,D_C);
                 vector<int>tmp3 = tmp1+tmp2;
                 mid = shift(tmp3,len/2);
            }
       }
       vector<int>left = shift(AC,len);
       vector<int>right = mid + BD;
       return left+right;
}
int main()
{
    vector<int> a,b;
   while(cin>>a>>b){
          //cout<<a<<endl<<b<<endl;
          vector<int>res = DivideAndConque(a,b);
          cout<<res;
          a.clear(),b.clear();
   }
    return 0;
}
