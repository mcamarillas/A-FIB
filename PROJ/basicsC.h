#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include "Graph.h"

class basics {
  private:
    bool isInDominatingSet(int node, set<int> &dominatingSet);
	public:
		// Constructora
    	basics();
		// Consultora
		bool isPIDS(Graph &g, set<int> &dominatingSet);
		bool isMinimalPIDS(Graph &g, set<int> &dominatingSet);
};
