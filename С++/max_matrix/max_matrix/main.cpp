#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <ctime>

using namespace std;


int** sf(string name2){
    int M, N;
    ifstream in(name2);
    in >> M >> N;
    int dim = M + N + 2;

    int **a;
    a = new int*[dim];
    for ( int i = 0; i < dim; i++)
        a[i] = new int[dim];
    
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            a[i][j] = 0;
    }
    for (int i = 2; i < M + 2; i++)
    {
        in >> a[0][i];
        a[i][0] = a[0][i];
    }
    int k=0;
    for (int j = M + 2; j < dim; j++)
    {
        in >> a[1][j];
        a[j][1] = a[1][j];
        k++;
    }
    for (int j = M + 2; j < dim; j++)
    {
        for (int i = 2; i < dim-k; i++)
        {
            a[i][j] = -1;
            a[j][i]  = a[i][j];
        }
    }
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    a[0][0] = dim;
    return a;
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

int FordFulkerson(int **m)
{
    int V = m[0][0];
    m[0][0] = 0;
    int curr_node, parent_node;
    int max_flow = 0;
    int path[V];
    
    while(breadth_first_search(m,path,V))
    {
        int path_flow=INT_MAX;
        curr_node = 1;
        while(curr_node!=0)
        {
            parent_node=path[curr_node];
            path_flow=min(path_flow, m[parent_node][curr_node]);
            curr_node=path[curr_node];
        }
        curr_node = 1;
        while(curr_node!=0)
        {
            parent_node = path[curr_node];
            m[parent_node][curr_node] -= path_flow;
            m[curr_node][parent_node] += path_flow;
            curr_node = path[curr_node];
        }
        max_flow += path_flow;
    }
    
    for (int i = 0; i < V; i++)
    {
            free(m[i]);
    }
    free(m);
    return max_flow;
}

bool compare(string name,string name2)
{
    int res=0;
    int sum = FordFulkerson(sf(name2));
    ifstream out(name);
    
    if (out.is_open())
    {
        out >> res;
    }
    out.close();
    if (sum==res)
    {
        cout << res << " = " << sum << endl;

        return true;
    }
    else
    {
        cout << res << " != " << sum << endl;
        return false;
    }
}

int main()
{
    
    clock_t start;
    double duration;
    string name  = "/Users/shurig/Desktop/ff/ff/test1.out";
    string name2 = "/Users/shurig/Desktop/ff/ff/test1.in";
    start = clock();
        if (!compare(name,name2))
        {
            cout << " u need to fix your code" << endl ;
        }
        else
        {
            cout << "good job =)" << endl ;
        }
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout <<"время работы:" << duration << endl;
    return 0;
}
