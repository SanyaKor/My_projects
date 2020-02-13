#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>


using namespace std;



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

int FordFalkerson(int **m,int V)
{
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
    return max_flow;
}

int main()
{
    int mxfl = 0,res = 0;
    ifstream in("/Users/shurig/Desktop/ff/ff/test6.in");
    
    if (in.is_open())
    {
        int V;
        in >> V;
        int **x;
        
        x = new int*[V];
        for ( int i = 0; i < V; i++)
        {
            x[i] = new int[V];
        }
        //
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                in >> x[i][j];
            }
        }
        mxfl = FordFalkerson(x,V);
    }
    in.close();
    ifstream out("/Users/shurig/Desktop/ff/ff/test6.out");
    
    if (out.is_open())
    {
        out >> res;
    }
    out.close();
    if (mxfl==res)
    {
        cout << res << " = " << mxfl << endl;
        cout << "good job =)" << endl ;
    }
    else
    {
        cout << res << " != " << mxfl << endl;
        cout << " u need to fix your code" << endl ;
    }
    return 0;
}


