#include <algorithm>
#include <queue>
#include "basicsC.h"

class greedy {
    private:
        int getN(Graph &g, set<int> &S, int node);
        int getH(Graph &g,set<int> &S,int node);
        int coverDegree(Graph &g,set<int> &S,int node);
        int needDegree(Graph &g,set<int> &S,int node);
    public:
        greedy();
        void graphPruning(Graph &g, set<int> &partialSolution, set<int> &uncovered);
        void IGA_PIDS(Graph &g, set<int> &solution);
        void Pans(Graph &g, set<int> &solution);

};
