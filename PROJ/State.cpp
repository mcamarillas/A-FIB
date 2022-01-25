#include "State.h"

State::State(set<int> &solution, set<int> &notInSolution, Graph &g){
    this->solution = solution;
    this->notInSolution = notInSolution;
    this->g = g;
}

State::State(){

}

void State::swap1(vector<int> &V, vector<int> &nV, int i, int j){
      int aux = V[i];
      V[i] = nV[j];
      nV[j] = aux;
}

vector<State> State::getSuccessors(){
    vector<State> successors;
    set<int>::iterator it1 = solution.begin();
    vector<int> S(solution.size());
    basics b;
    int i = 0;
    while(it1 != solution.end()) {
      S[i] = *it1;
      ++it1;
      ++i;
    }
    it1 = notInSolution.begin();
    i = 0;
    vector<int> notS(notInSolution.size());

    while(it1 != notInSolution.end()) {
      notS[i] = *it1;
      ++it1;
      ++i;
    }
    for(i = 0; i < S.size(); ++i) {
      for(int j = 0; j < notS.size(); ++j) {
        swap1(S,notS,i,j);
        solution.clear();
        for(int x : S) {
          solution.insert(x);
        }
        if(b.isPIDS(g, solution)) successors.push_back(*this);
        swap1(notS,S,j,i);
      }
    }
    for(i = 0; i < S.size(); ++i) {
      int aux = S[i];
      S[i] = -1;
      solution.clear();
      for(int x : S) {
        if(x != -1) solution.insert(x);
      }
      if(b.isPIDS(g, solution)) {
        successors.push_back(*this);
      }
      S[i] = aux;
    }
    solution.clear();
    for(int x : S) {
    solution.insert(x);
    }
    return successors;
}

State State::bestSuccessor(){
    vector<State> successors = getSuccessors();
    int numberOfSuccessors = successors.size();
    if(numberOfSuccessors == 0) return *this;
    int indexOfBestSuccessor = 0;
    float minHeuristica = successors[indexOfBestSuccessor].heuristica();

    for (int i = 1; i < numberOfSuccessors; ++i){
      float newHeuristica = successors[i].heuristica();
      if (newHeuristica < minHeuristica){
        minHeuristica = newHeuristica;
        indexOfBestSuccessor = i;
      }
    }
    return successors[indexOfBestSuccessor];
}

float State::heuristica(){
    //Coger el mínimo sumatorio de los grados por encima del 50% que formen un PIDs
    vector<int> nodesVector;
    g.getNodes(nodesVector);
    float sum = 0;
    for (int i = 0; i < nodesVector.size(); ++i){
        vector<int> adj;
        float adjInSol = 0;
        float degree = g.getDegree(i);
        g.getAdjacent(nodesVector[i],adj);
        for(int j = 0; j < adj.size(); ++j) {
            if(solution.find(adj[i]) != solution.end()) ++adjInSol;
        }
        sum += adjInSol/degree;
    }
    return sum + solSize()*nodesVector.size();
}

int State::solSize() {
  return solution.size();
}

void State::getSolution(set<int> &sol) {
  sol = this->solution;
}

bool State::erasedSolution(){
    srand (time(NULL));
    set<int>::iterator it = solution.begin();
    int size = solSize();
    vector<int> solutionVector(size);
    for (int i = 0; i < size; ++i){
      solutionVector[i] = *it;
      ++it;
    }

    int erasedNodes = solSize()/4;
    
    for (int k = 0; k < erasedNodes; ++k){
      
      int random = rand()%(size-1);
      if (solutionVector[random] == -1) --k;
      else {
        solutionVector[random] = -1;
      }
    }
    solution.clear();
    for(int x : solutionVector) {
      if(x != -1) solution.insert(x);
    }
    basics b;
    return b.isPIDS(g, solution);
    
}

bool State::insertSolution(){
    srand (time(NULL));

    vector<int> nodes;
    g.getNodes(nodes);
    int insertedNodes = ((solSize()*4)/3 + nodes.size())/2 - solSize();
    set<int>::iterator it;
    for (int k = 0; k < insertedNodes; ++k){
      int random = rand()%(nodes.size());
      if (solution.find(nodes[random]) == solution.end()) solution.insert(nodes[random]);
      else --k;
    }

    basics b;
    return b.isPIDS(g, solution);
}

void State::print(){
    set<int>::iterator it;
    it = solution.begin();
    for (int i = 0; i < solution.size(); ++i){
      cout << *it << ' ';
      ++it;
    }
    cout << endl;
}
