#include "greedyC.h"
#include <set>
#include <vector>
#include <time.h>

class State
{
    private:
        set<int> solution;
        set<int> notInSolution;
        Graph g;
    public:
        State(set<int> &solution, set<int> &notInSolution, Graph &g);
        State();
        void getSolution(set<int> &sol);
        void swap1(vector<int> &V, vector<int> &nV, int i, int j);
        vector<State> getSuccessors();
        State bestSuccessor();
        float heuristica();
        bool erasedSolution();
        bool insertSolution();
        int solSize();
        void print();

};
