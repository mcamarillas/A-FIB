#include "local_searchC.h"
#include <cmath>
#include <time.h>
#include <chrono>
#include <string.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace std::chrono;

const int T = 1; //contra + T más probabilidad de aceptación nunca prob +1

void readDefaultGraph(Graph &g) {
    for(int i = 0; i < 10; ++i) {
        g.addNode(i);
    }
    g.addEdge(6,4);
    g.addEdge(6,3);
    g.addEdge(6,2);
    g.addEdge(2,1);
    g.addEdge(2,8);
    g.addEdge(2,9);
    g.addEdge(9,5);
    g.addEdge(5,0);
    g.addEdge(5,7);
    g.addEdge(0,7);
}

/*
    Reads the nodes which will form the new graph.
*/
void readDataMH(Graph &g, string s) {
    ifstream indata;
    indata.open(s.c_str());
    int u, v;
    indata >> u >> v;
    while(indata >> u >> v) {
      g.addNode(u);
      g.addNode(v);
      g.addEdge(u,v);
    }
    indata.close();

}

void generateInitialSolutionMH(Graph& g, set<int> &solution){
  for (int i = 0; i < g.size(); ++i){
    solution.insert(i);
  }
}

float probabilityOfAcceptation(State &solution, State &newSolution){
    if (solution.heuristica() > newSolution.heuristica()) return 1;
    else {
      return exp(-((newSolution.heuristica()-solution.heuristica())/(T*solution.solSize())));
    }
}

State disturbance(State &solution){
    State modifySolution = solution;
    if (modifySolution.erasedSolution()) return modifySolution;
    else if (modifySolution.insertSolution()) return modifySolution;
    return solution;
}

State acceptanceRequirements(State &state, State &newState){
    srand (time(NULL));
    float probability = probabilityOfAcceptation(state, newState);
    int random = rand()%1000;
    if (random <= probability*1000) return newState;
    else return state;
}

/*
  Display all possible graphs the user can test.
*/
void intputInfoGMH(Graph &g) {
    cout << endl << "Select the function: " << endl << endl <<
                    "   1.Choose Default Graph" << endl <<
                    "   2.ego-facebook" << endl <<
                    "   3.graph_actors_dat" << endl <<
                    "   4.graph_CA-AstroPh" << endl <<
                    "   5.graph_CA-CondMat" << endl <<
                    "   6.graph_CA-HepPh" << endl <<
                    "   7.graph_football" << endl <<
                    "   8.graph_jazz" << endl <<
                    "   9.socfb-Brandeis99" << endl <<
                    "   10.socfb-Mich67" << endl <<
                    "   11.soc-gplus" << endl <<
                    "   12.Select file graph (with an structure such as the one in ./Pruebas/AsiaFm.txt)" << endl << endl;
    int a;
    string s;
    while(cin >> a) {
      if (a == 1) {
        readDefaultGraph(g);
        break;
      }
      else if (a == 2) {
        s = "./instances/ego-facebook.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 3) {
        s = "./instances/graph_actors_dat.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 4) {
        s = "./instances/graph_CA-AstroPh.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 5) {
        s = "./instances/graph_CA-CondMat.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 6) {
        s = "./instances/graph_CA-HepPh.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 7) {
        s = "./instances/graph_football.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 8) {
        s = "./instances/graph_jazz.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 9) {
        s = "./instances/socfb-Brandeis99.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 10) {
        s = "./instances/socfb-Mich67.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 11) {
        s = "./instances/soc-gplus.txt";
        readDataMH(g,s);
        break;
      }
      else if (a == 12) {
        cout << endl << "Introduce a valid path, otherwise the program will not run propertly" <<
        endl << "File path (./path): ";
        cin >> s;
        readDataMH(g,s);
        break;
      }
      else cout << "Introduce a valid option." << endl;
    }
}

int main(){
    Graph g;
    intputInfoGMH(g);
    greedy greedy;
    set<int> initialSolution;
    greedy.Pans(g, initialSolution);
    //generateInitialSolutionMH(g,initialSolution);
    set<int> notInSolution;
    g.getSetNodes(notInSolution);
    set<int>::iterator it = initialSolution.begin();
    while(it != initialSolution.end()) {
        if(notInSolution.find(*it) != notInSolution.end()) {
            notInSolution.erase(*it);
        }
        ++it;
    }
    State initialState(initialSolution, notInSolution, g);
    localSearch ls;
    int iteration = 1;


    State metaheuristicInitialSolution = ls.hillClimbing(initialState, iteration);
    metaheuristicInitialSolution.print();
    State history = metaheuristicInitialSolution;
    auto start = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(start - start);
    while(duration.count() < 6000000) {
        if(history.heuristica() > metaheuristicInitialSolution.heuristica()) history = metaheuristicInitialSolution;
        State newState = disturbance(metaheuristicInitialSolution);     //cambiar solution para obtener otro posible estado
        iteration = 1;
        newState = ls.hillClimbing(newState, iteration);
        metaheuristicInitialSolution = acceptanceRequirements(metaheuristicInitialSolution, newState); //aceptamos la nueva solución si solo si
        auto stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        cout << duration.count() << endl;
    }
    history.print();
    cout << history.solSize() << endl;
}
