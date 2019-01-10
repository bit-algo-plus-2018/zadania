#include<bits/stdc++.h>
using namespace std;
//Srednica drzewa
using adjacency=vector<vector<int> >;
int readInput(adjacency &tree);

int bfs(int s, adjacency &tree, int n){
    vector<int> distance(n,-1);
    distance[s]=0;
    queue<int> que;
    que.push(s);

    while(!que.empty()){
        int top = que.front();
        que.pop();
        for(auto i : tree[top]){
            if(distance[i]!=-1)
                continue;
            distance[i]=distance[top]+1;
            que.push(i);
        }
    }
    int resId = s;
    int resVal = 0;
    for(int i=0; i<n; i++){
        if(distance[i]>resVal){
            resVal = distance[i];
            resId = i;
        }
    }
    return resId;
}

bool print(int n, int endPath, adjacency &tree,vector<bool> &seen){
    bool doPrint = (n==endPath);
    for(auto i : tree[n]){
        if(seen[i])
            continue;
        seen[i] = true;
        doPrint = doPrint || print(i,endPath,tree, seen);
    }
    if(doPrint)
        cout<<n+1<<endl;
    return doPrint;
}

void solve(adjacency &tree, int n){
    int beginPath = bfs(0,tree,n);
    int endPath = bfs(beginPath,tree,n);
    vector<bool> seen(n,false);
    print(beginPath,endPath,tree,seen);
}

int main(){
    adjacency tree;
    int n = readInput(tree);
    solve(tree,n);
}

int readInput(adjacency &tree){
    //wierzcholki numerowane od 1 do n
    tree.clear();
    tree.shrink_to_fit();
    int n,m;
    cin>>n>>m;
    tree.resize(n);    

    while(m--){
        int a,b;
        cin>>a>>b;
        a--;b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    return n;
}
