#include<strings.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

int dr[] = {-1,1,0,0};
int dc[] = {0,0,1,-1};
int R,C;
int move_count=0;
vector<vector<char>> city;
vector<pair<int, int>> riders;
queue<int> rq, cq;
int sr;
int sc;
int nodes_left_in_layer = 1;
int nodes_in_next_layer = 0;
bool reached_end = false;
vector<vector<bool>> visited;
void explore_neighbours(int r,int c)
{
    for(int i=0; i<4; i++)
    {
        int rr= r+dr[i];
        int cc = c+dc[i];
        if(rr<0 || cc<0)
        {
            continue;
        }
        if(rr>=R || cc>=C)
        {
            continue;
        }
        if(visited[rr][cc]==true)
        {
            continue;
        }
        if(city[rr][cc]=='#')
        {
            continue;
        }
        // cout<<rr<<" "<<cc<<endl;
        rq.push(rr);
        cq.push(cc);
        visited[r][c] = true;
        nodes_in_next_layer++;
    }
    return;
}
int solve(int sr, int sc, int ex, int ey)
{
    rq.push(sr);
    cq.push(sc);
    // cout<<visited[sr][sc]<<endl;
    visited[sr][sc] = true;
    while(rq.size() > 0)
    {
        int r = rq.front();
        rq.pop();
        int c = cq.front();
        cq.pop();
        // cout<<r<<" "<<c<<endl;
        if(r==ex && c==ey)
        {
            reached_end=true;
            break;
        }
        explore_neighbours(r,c);
        nodes_left_in_layer--;
        if(nodes_left_in_layer==0)
        {
            // cout<<"here";
            nodes_left_in_layer = nodes_in_next_layer;
            nodes_in_next_layer=0;
            move_count++;
        }
    }

    if(reached_end==true)
    {
        // cout<<move_count<<endl;
        return move_count;
    }
    return -1;
}
int main()
{
    int flag=0;
    vector<pair<int, int>> riders;
    cin>>R>>C;
    int ex,ey;
    int sr, sc;
    for(int i=0; i<R; i++)
    {
        vector<char> arr;
        for(int j=0; j<C; j++)
        {
            char k;
            cin>>k;
            arr.push_back(k);
            if(k=='R')
                riders.push_back(make_pair(i,j));
            if(k=='.' && flag==0)
            {
                flag=1;
                ex=i;
                ey=j;
            }
            if(k=='A')
            {
                sr=i;
                sc=j;
            }
        }
        city.push_back(arr);
    }
    for(int i=0; i<R; i++)
    {
        vector<bool> arr;
        for(int j=0; j<C; j++)
        {
            arr.push_back(false);
        }
        visited.push_back(arr);
    }
    int my_time = solve(sr, sc, ex, ey);
    // cout<<my_time<<endl;
    for(auto it: riders)
    {
        move_count=0;
        queue<int> empty;
        swap(cq, empty);
        swap(rq, empty);
        visited.clear();
        for(int i=0; i<R; i++)
        {
            vector<bool> arr;
            for(int j=0; j<C; j++)
            {
                arr.push_back(false);
            }
            visited.push_back(arr);
        }
        nodes_left_in_layer = 1;
        nodes_in_next_layer = 0;
        reached_end = false;
        // cout<<it.first<<" "<<it.second<<endl;
        while(rq.empty()==false)
            rq.pop();
        int t = solve(it.first, it.second, ex, ey);
        // cout<<t<<" ";
        if(my_time > t)
        {
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES"<<endl<<my_time;
    return 0;
}
