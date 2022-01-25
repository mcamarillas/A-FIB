#include "greedyC.h"
using namespace std;

greedy::greedy() {

}

/*
    Returns the number of neighbours of a node that pertain to a certain set.
*/
int greedy::getN(Graph &g, set<int> &S, int node) {
    vector<int> adj;
    g.getAdjacent(node,adj);
    int count = 0;
    for(int i = 0; i < adj.size(); ++i) {
        if(S.find(adj[i]) != S.end()) ++count;
    }
    return count;
}


/*
    Returns the H forumla used on Pans algorithm.
*/
int greedy::getH(Graph &g,set<int> &S,int node) {
    return ceil(g.getDegree(node)/2.) - getN(g,S,node);
}

/*
    Returns the number of neighbours of a certain node than have H > 0.
    Needed on Pan's algorithm.
*/
int greedy::coverDegree(Graph &g,set<int> &S,int node) {
    vector<int> adj;
    g.getAdjacent(node,adj);
    int count = 0;
    for(int i = 0; i < adj.size(); ++i) {
        if(getH(g,S,adj[i]) > 0) ++count;
    }
    return count;
}

/*
    Function used on the IGA_PIDS algorithm.
*/
int greedy::needDegree(Graph &g,set<int> &S,int node) {
    vector<int> adj;
    g.getAdjacent(node,adj);
    int sum = 0;
    for(int i = 0; i < adj.size(); ++i) {
        sum += max(getH(g,S,node),0);
    }
    return sum;
}


/*
    Function used on the IGA_PIDS algorithm.
*/
void greedy::graphPruning(Graph &g, set<int> &partialSolution, set<int> &uncovered) {
    vector<int> vertex;
    g.getNodes(vertex);
    // Set the uncovered vertex
    for(int i = 0; i < vertex.size(); ++i) {
        uncovered.insert(vertex[i]);
    }
    for(int i = 0; i < vertex.size(); ++i) {

        int v = vertex[i];
        if(g.getDegree(v) == 1) {
            vector<int> adjV;
            g.getAdjacent(v, adjV);
            int u = adjV[0];
            set<int>::iterator it = partialSolution.find(u);

            if(it == partialSolution.end()) partialSolution.insert(u);
            uncovered.erase(v);

            it = partialSolution.find(v);
            if(g.getDegree(u) == 2 and it == partialSolution.end()) {
                vector<int> adjU;
                g.getAdjacent(v, adjU);
                int w = adjU[0];
                if(adjU[0] == v) w = adjU[1];
                it = partialSolution.find(w);
                if(it == partialSolution.end()) partialSolution.insert(w);
                uncovered.erase(u);
            }
        }
    }
}

/*
    Implementation of the IGA_PIDS algorithm. We tried to solve the problem with
    this algorithm but we couldnt find an omptimal implementation so we ended
    using only Pan's algorithm to solve the problem.
*/
void greedy::IGA_PIDS(Graph &g, set<int> &S) {
    set<int> uncovered;
    graphPruning(g, S, uncovered);
    int n = uncovered.size();

    // C <- sorted uncovered by degree
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> C;
    set<int>::iterator it = uncovered.begin();
    while(it != uncovered.end()) {
        C.push(make_pair( g.getDegree(*it),*it));
        ++it;
    }
    // S1 <- V\S
    set<int> S1;
    g.getSetNodes(S1);

    it = S.begin();
    while(it != S.end()) {
        if(S1.find(*it) != S1.end()) {
            S1.erase(*it);
        }
        ++it;
    }
    // while S is not a valid PIDS solution do
    basics b;
    while(!C.empty()) {
        int vi = C.top().second;
        int p = getH(g,S,vi);
        vector<int> adj;
        g.getAdjacent(vi,adj);
        for(int j = 0; j < p; ++j) {
            int cdMax = -1;
            set<int> cds;
            for(int i = 0; i< adj.size();++i) {
                if(S.find(adj[i]) == S.end()) {
                  int cd = coverDegree(g,S,adj[i]);
                  if(cd > cdMax) {
                      cdMax = cd;
                      cds.clear();
                  }
                  if(cd == cdMax) cds.insert(adj[i]);
                }
            }
            int ndMax = -1;
            set<int>::iterator argMax = cds.begin();
            set<int>::iterator it1 = cds.begin();
            while(it1 != cds.end()) {
                int nd = needDegree(g,S1,*it);
                if(nd > ndMax) {
                    argMax = it1;
                    ndMax = nd;
                }
                ++it1;
            }
            S.insert(*argMax);
            S1.erase(*argMax);
        }
        C.pop();
    }
    vector<int> vertex;
    g.getNodes(vertex);
    set<int> notCovered;
    if(!b.isPIDS(g,S)) {
        for(int v : vertex) {
          vector<int> adj;
          g.getAdjacent(v, adj);
          int count = 0;
          for(int u : adj) if(S.find(u) != S.end()) ++count;
          if(count < ceil(g.getDegree(v)/2.)) notCovered.insert(v);
        }
        set<int>::iterator it1 = notCovered.begin();
        while(it1 != notCovered.end()) {
            vector<int> adj;
            g.getAdjacent(*it1, adj);
            for(int u : adj) {
              if(S.find(u) == S.end()) S.insert(u);
              if(b.isPIDS(g,S)) break;
            }
            ++it1;
        }
    }
 }

/*
    Implementation of Pan's algorithm. We use this algorithm to find a greedy
    solution to the problem.
*/
void greedy::Pans(Graph &g, set<int> &S) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> C;
    vector<int> V;
    g.getNodes(V);
    set<int> S1;
    for(int x : V) {
        C.push(make_pair(g.getDegree(x),x));
        S1.insert(x);
    }
    int n = V.size();

    map<int,int> hs;
    map<int,int> CoverDegree;
    map<int,set<int>> adjS;

    for(int i = 0; i < n; ++i) {
        set<int> s;
        vector<int> v;
        g.getAdjacent(V[i],v);
        for(int j = 0; j < g.getDegree(V[i]); ++j) {
            s.insert(v[j]);
        }
        adjS[V[i]] = s;
        CoverDegree[V[i]] = g.getDegree(V[i]);

        hs[V[i]] = ceil(g.getDegree(V[i])/2.);

        V[i] = C.top().second;
        C.pop();
    }

    for(int i = 0; i < n; ++i) {
        int vi = V[i];

        if(hs[vi] > 0) {
            int p = hs[vi];
            for(int j = 1; j <= p; ++j) {
                int cdMax = -1;
                set<int>::iterator it = adjS[vi].begin();
                set<int>::iterator argMax = it;
                while(it != adjS[vi].end()) {
                    int cd = CoverDegree[*it];
                    if(cd > cdMax) {
                        cdMax = cd;
                        argMax = it;
                    }
                    ++it;
                }

                S.insert(*argMax);
                set<int> adj;
                g.getSetAdjacent(*argMax,adj);
                it = adj.begin();
                while(it != adj.end()) {
                    hs[*it]--;
                    if(hs[*it] <= 0) CoverDegree[*argMax]--;

                    adjS[*it].erase(*argMax);

                    ++it;
                }
            }
        }
    }
}
