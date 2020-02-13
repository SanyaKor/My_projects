#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
void multiply(unsigned long long int **F,unsigned long long int **M,unsigned long long int mod) {
    unsigned long long int f1 = ((F[0][0]%mod * M[0][0]%mod)%mod
                                 + (F[0][1]%mod * M[1][0]%mod)%mod)%mod;
    
    unsigned long long int f2 = ((F[0][0]%mod * M[0][1]%mod)%mod
                                 + (F[0][1]%mod * M[1][1]%mod)%mod)%mod;
    
    unsigned long long  int f3 = ((F[1][0]%mod * M[0][0]%mod)%mod
                                 + (F[1][1]%mod * M[1][0]%mod)%mod)%mod;
    
    unsigned long long  int f4 = ((F[1][0]%mod * M[0][1]%mod)%mod
                                 + (F[1][1]%mod * M[1][1]%mod)%mod)%mod;
    F[0][0] = f1;
    F[0][1] = f2;
    F[1][0] = f3;
    F[1][1] = f4;
}
void power(unsigned long long  int **F,unsigned long long int n,unsigned long long int mod,unsigned long long int **cache) {
    if (n == 0 || n == 1)
        return;
    
    power(F, n / 2,mod,cache);
    multiply(F, F,mod);
    if (n % 2 != 0)
        multiply(F, cache,mod);
}
int fibonacci_matrix(unsigned long long int n,unsigned long long int mod,unsigned long long int **F,unsigned long long int **cache) {
    if (n == 0)
        return 0;
    power(F, n - 1,mod,cache);
    return F[0][0];
}
int main() {
    unsigned long long int mod;
    unsigned long long int n;
    unsigned long long int res;
    unsigned long long int res1;
    
    unsigned long long int **matrix;
    unsigned long long int **cache;
    matrix = new unsigned long long int*[2];
    for ( int i = 0; i < 2; i++)
    {
        matrix[i] = new unsigned long long int[2];
    }
    
    
    cache = new unsigned long long int*[2];
    for ( int i = 0; i < 2; i++)
    {
        cache[i] = new unsigned long long int[2];
    }
    
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 0;
    
    cache[0][0] = 1;
    cache[0][1] = 1;
    cache[1][0] = 1;
    cache[1][1] = 0;
    string path;
    ostringstream ss;
    int total_res=0;
    int x=0;
    clock_t start;
    double duration;
    while(x!=410){
        ss<<"/Users/shurig/Desktop/ff/ff/"<<x<<".in";
        path = ss.str();
        ifstream f(path.c_str());
        if (f)
        {
            f >> n >> mod;
            res1 = fibonacci_matrix(n,mod,matrix,cache);
            ss.str("");
            ss << "tests/test" << x << ".out";
            path = ss.str();
            f.close();
            f.open(path.c_str());
            f >> res;
            f.close();
        }
        if(res==res1){
            total_res++;
        }
        x++;
    }
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    
    if(total_res==410){
        cout << "Ответы совпали =)" << endl;
    }
    else
        cout << "Ты накосячил =(" << endl;
    
    cout <<"время работы:" << duration << endl;
    
    return 0;
}
