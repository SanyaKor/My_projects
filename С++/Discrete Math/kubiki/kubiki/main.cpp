#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;



int** sf(string name2){
    char c;
    int size = 0;
    int ws = 0;
    ifstream F(name2);
    F >> size;
    c = F.get();
    while ((c = F.get()) != '\n')
    {
        ws++;
    }
    F.close();
    F.open(name2);
    
    F >> size;
    int dim = ws + size + 2;
    int **m_k;
    int **m_g;
    m_g = new int*[dim];
    for ( int i = 0; i < dim; i++)
        m_g[i] = new int[dim];
    
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            m_g[i][j] = 0;
    }
    
    m_k = new int *[size];
    for ( int i = 0; i < size; i++)
        m_k[i] = new int[6];
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 6; j++)
            m_k[i][j] = 0;
    }
    
    
    for (int i = 2; i < ws + 2; i++)
    {
        m_g[0][i] = 1;
        m_g[i][0] = 1;
    }
    
    for (int i = ws + 2; i < dim; i++)
    {
        m_g[1][i] = 1;
        m_g[i][1] = 1;
    }
    
    int *w = new int[ws];
    c = F.get();
    while ((c = F.get()) != EOF)
    {
        w[0] = (int)c - 'a';
        
        for (int i = 1; i < ws; i++)
        {
            c = F.get();
            w[i] = (int)c - 'a';
        }
        c = F.get();
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                c = F.get();
                m_k[i][j] = (int)c - 'a';
            }
            c = F.get();
        }
    }
    
    for (int i = 0; i < ws; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int c = 0; c < 6; c++)
            {
                if (w[i] == m_k[j][c])
                {
                    m_g[i + 2][j + ws + 2] = 1;
                    break;
                }
            }
        }
    }
    m_g[0][0] = dim;
    m_g[0][1] = ws;
    return m_g;
}
bool breadth_first_search(int **m,int *path,int V)
{
    queue <int> q;
    bool visited[V];
    for(int i=0; i<V; i++)
    {
        visited[i] = false;
    }
    
    q.push(0);
    visited[0] = true;
    path[0]=-1;
    
    while(!q.empty())
    {
        int curr_node = q.front();
        q.pop();
        for(int i = 0;  i < V; i++)
        {
            if(visited[i] == false && m[curr_node][i] > 0)
            {
                q.push(i);
                path[i] = curr_node;
                visited[i] = true;
            }
        }
    }
    if (visited[1]==true)
        return true;
    else
        return false;
}



int FordFalkerson(int **m)
{
    int V = m[0][0];
    int ws = m[0][1];
    m[0][1] = 0;
    m[0][0] = 0;
    int curr_node, parent_node;
    int res = 0;
    int path[V];
    
    while(breadth_first_search(m,path,V))
    {
        curr_node = 1;
        while(curr_node!=0)
        {
            parent_node = path[curr_node];
            m[parent_node][curr_node]--;
            m[curr_node][parent_node]++;
            curr_node = path[curr_node];
        }
        res++;
    }
    if (res == ws )
    {
        cout << "Полученный ответ ДА" << endl;
        return 1;
    }
    cout << "Полученный ответ НЕТ" << endl;
    return 0;
}

bool compare(string name, string name2)
{
    int r,tr=0;
    r = FordFalkerson(sf(name2));
    ifstream F(name);
    char c;
    c = F.get();
    tr++;
    while ((c = F.get()) != '\n')
    {
        tr++;
    }
    if(tr==3)
    {
        cout << "Правильный ответ ДА" << endl;
    }
    else
    {
        cout << "Правильный ответ НЕТ" << endl;
        
    }
    if((tr == 3 && r == 1 )||(tr == 2 && r == 0 ) )
    {
        return true;
    }
    return false;
}



int main()
{
    clock_t start;
    double duration;
    string name  = "/Users/shurig/Desktop/ff/ff/test8.out";
    string name2 = "/Users/shurig/Desktop/ff/ff/test8.in";
    start = clock();
    if(compare(name,name2)==true)
    {
        cout << "Ответы совпали" << endl;
    }
    else
    {
        cout << "Ответы не совпали" << endl;
    }
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout <<"время работы:" << duration << endl;
    return 0;
}


