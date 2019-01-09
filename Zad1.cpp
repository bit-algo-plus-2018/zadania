#include<bits/stdc++.h>
using namespace std;
/*
Dany jest graf G=(V,E) nieskierowany, ważony (wagi nieujemne) 
i wyróżniony wierzchołek źródłowy s. Dla każdego wierzchołka 
obliczyć najkrótszą ścieżkę do niego ze źródła, przy czym
liczymy tylko ścieżki o parzystej liczbie krawędzi.
*/
struct vertex{
    int id;
    int distance;
    bool parity;
    vertex(int i,int d)
        :id(i),distance(d),parity(false)
        {}
    vertex(int i,int d,bool p)
        :id(i),distance(d),parity(p)
        {}
};
struct vertexCmp{
    bool operator()(vertex left, vertex right){
        return left.distance<right.distance;
    }
};
using adjacency=vector<vector<vertex> >;
const int INF = numeric_limits<int>::max();
void readInput(int &n, int &m, adjacency &graph);

void solve(int n,adjacency &graph, vector<int> &result){
    priority_queue<vertex,vector<vertex>,vertexCmp> que;
    que.push(vertex(0,0,true));
    for(int i = 1; i<n; i++)
        que.push(vertex(i,INF));
    result.clear();
    result.shrink_to_fit();
    result.resize(n,INF);
    vector<int>distance(n,INF);
    distance[0] = 0;

    while(!que.empty()){
        vertex top = que.top();
        que.pop();

        for(auto i : graph[top.id]){
            if(!top.parity)
                result[i.id] = min(result[i.id],(distance[top.id]==INF ? INF:distance[top.id]+i.distance));
            if(distance[top.id]!=INF && distance[top.id]+i.distance < distance[i.id]){
                distance[i.id] = distance[top.id]+i.distance;
                que.push(vertex(i.id,distance[i.id],!top.parity));            
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    adjacency graph;
    int n,m;
    readInput(n,m,graph);
    vector<int> distance;
    solve(n,graph, distance);
    for(int i=1; i<n; i++)
        cout<<i<<" = "<<distance[i]<<endl;
}

void readInput(int &n, int &m, adjacency &graph){
    cin>>n>>m;
    graph.resize(n);
    for(int i=0; i<m; i++){
        int a,b,c;
        cin>>a>>b>>c;
        graph[a].push_back(vertex(b,c));
        graph[b].push_back(vertex(a,c));
    }
}
