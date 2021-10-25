#include<strings.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>
int v;
using namespace std;
vector<pair<int, int>> adj[4];
vector<vector<int>> paths;
void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt)
{
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
}
void printGraph(vector<pair<int, int>> adj[])
{
    for(int i=0; i<v; i++)
    {
        cout<<"Edges of Node "<<i<<endl;
        for(auto it = adj[i].begin(); it!=adj[i].end(); it++)
        {
            cout<<it->first<<" "<<it->second<<endl;
        }
    }
}
void util(int u, int d, bool visited[], int path[], int& path_index, int wt, vector<int> &wt_array)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    if(u==d){
        vector<int> p;
        for(int i=0; i<path_index; i++)
            // cout<<path[i]<<" ";
            p.push_back(path[i]);
        // cout<<wt;
        wt_array.push_back(wt);
        paths.push_back(p);
        // cout<<endl;
    }
    else
    {
        vector<pair<int, int>>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int curr_wt = i->second;
            int ind = i->first;
            if (!visited[ind])
            {
                wt = wt + curr_wt;
                util(ind, d, visited, path, path_index, wt, wt_array);
                wt=0;
            }
        }

    }
    path_index--;
    visited[u] = false;
    // wt=0;
}
void getPaths(int s, int d, vector<int> &wt_array)
{
    bool *visited = new bool[v];
    int *path = new int[v];
    int path_index=0;
    for(int i=0; i<v; i++)
        visited[i] = false;

    util(s,d,visited, path, path_index, 0, wt_array);
}
int main()
{
    int nodes, edges;
    cin>>nodes>>edges;
    v = nodes;
    for(int i=0; i<edges; i++)
    {
        int s,d,wt;
        cin>>s>>d>>wt;
        addEdge(adj,s,d,wt);
    }
    // cout<<v;
    // printGraph(adj);
    int d;
    cin>>d;
    for(int u=0; u<nodes-1; u++)
    {
        vector<int> wt_array;
        if(d==u)
            continue;
        
        getPaths(u,d, wt_array);
        auto min_it = min_element(wt_array.begin(), wt_array.end()); //getting the min weight 
        int c = count(wt_array.begin(), wt_array.end(), *min_it); //getting the count of min weight, if more than 1 print lexicographically shortest
        if(c==1)
        {
            int ind = min_it - wt_array.begin();
            for(auto i: paths[ind])
                cout<<i<<" ";
            cout<<endl;
        }
        else
        {
            vector<string> short_path;
            for(int i=0; i<wt_array.size(); i++)
            {
                string s="";
                if(wt_array[i] == *min_it)
                    {
                        for(auto it:paths[i])
                            s = s+to_string(it)+" ";
                    }
                short_path.push_back(s);    
            }
            auto ans = min_element(short_path.begin(), short_path.end());
            cout<<*ans<<endl;
        }
        paths.clear();
    }
    // for(auto it: paths)
    // {
    //     for(auto it1:it)
    //         cout<<it1<<" ";
    //     cout<<endl;
    return 0;
}
