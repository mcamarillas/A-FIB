#include "basicsC.h"
using namespace std;

//--------------------------------CONSTRUCTOR--------------------------------//
basics::basics() {

}

//--------------------------------CONSULTANTS--------------------------------//

/*
  Returns true if the node is in the dominatingSet, false otherwise.
*/
bool basics::isInDominatingSet(int node, set<int> &dominatingSet) {
    set<int>::iterator it;
    it = dominatingSet.find(node);
    return it != dominatingSet.end();
}

/*
  Return true if the dominatingSet is  PIDS on the graph g, false otherwise.
*/
bool basics::isPIDS(Graph &g, set<int> &dominatingSet) {
    vector<int> v;
    g.getNodes(v);
    int size = v.size();
    int i = 0;
    bool isDominating = true;
    while(i < size and isDominating) {
        int count = 0;
        vector<int> adj;
        g.getAdjacent(v[i], adj);
        int size2 = adj.size();
        for(int j = 0; j < size2; ++j) if(isInDominatingSet(adj[j], dominatingSet)) ++count;
        isDominating = count >= ceil(size2/2.);
        ++i;
    }
    return isDominating;
}

/*
  Returns true if the dominatingSet is minimal.
*/
bool basics::isMinimalPIDS(Graph &g, set<int> &dominatingSet) {
    set<int>::iterator it = dominatingSet.begin();
    vector<int> ds(dominatingSet.size());
    int i = 0;
    while(it != dominatingSet.end()) {
      ds[i] = *it;
      ++it;
      ++i;
    }
    bool found = false;
    for(i = 0; i < ds.size(); ++i) {
      int aux = ds[i];
      ds[i] = -1;
      dominatingSet.clear();
      for(int x : ds) {
        if(x != -1) dominatingSet.insert(x);
      }
      found = isPIDS(g, dominatingSet);
      ds[i] = aux;
    }
    return !found;
}
