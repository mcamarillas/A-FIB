#include "local_searchC.h"
#include <chrono>
#include <string.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
using namespace std;
using namespace std::chrono;

//----------------------------------------FUNCTIONS-------------------------------------------\\

/*
  Selects the same graph as the one in the instructions document.
*/
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
    Reads the nodes which will form the new graph
*/
void readDataLS(Graph &g, string s) {
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

/*
  Generates an initial solution based on making all nodes form part of
  the S set, which is a correct soluction.
*/
void generateInitialSolution(Graph& g, set<int> &solution){
  for (int i = 0; i < g.size(); ++i){
    solution.insert(i);
  }
}

/*
  Executes Local search search with a given initial solution.
*/
void solutionLS(Graph &g, set<int> &initialSolution) {
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
    int iteration = 1;
    // Get starting timepoint

    localSearch ls;
    auto start = high_resolution_clock::now();
    State solution = ls.hillClimbing(initialState, iteration);
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
    basics b;
    set<int> sol;
    solution.getSolution(sol);
    cout << "Hill climbing algorithm info:" << endl;
    cout << endl << "       Execution time: " << duration.count() << " microseconds." << endl;
    cout << "       Number of nodes expanded: " << iteration << '.' << endl;
    cout << endl << "Solution info:" << endl;
    if (b.isPIDS(g, sol) == 1) {
    cout << endl << "   Graph G has a dominating set. Set found: [";
    bool first = true;
    set<int>::iterator it = sol.begin();
    while(it != sol.end()) {
      if(first) first = false;
      else cout << ", ";
      cout << *it;
      ++it;
    }
    cout << "]." << endl;
    vector<int> v;
    g.getNodes(v);
    cout << endl << "   Size of the set: " << sol.size() << ". Which represents " << (sol.size()/float(v.size()))*100 << "% of the nodes." << endl;
    if(b.isMinimalPIDS(g,sol)) cout << "   Found set is minimal";
    else cout << "   Found set is not minimal.";
    cout << endl;
  }
  else cout << "    This graph has no dominating set" << endl;

}

/*
  Displays all the information the user needs to execute the program correctly.
*/
void intputInfoLS(Graph &g, set<int> &initialSolution) {

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
      readDataLS(g,s);
      break;
    }
    else if (a == 3) {
      s = "./instances/graph_actors_dat.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 4) {
      s = "./instances/graph_CA-AstroPh.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 5) {
      s = "./instances/graph_CA-CondMat.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 6) {
      s = "./instances/graph_CA-HepPh.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 7) {
      s = "./instances/graph_football.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 8) {
      s = "./instances/graph_jazz.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 9) {
      s = "./instances/socfb-Brandeis99.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 10) {
      s = "./instances/socfb-Mich67.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 11) {
      s = "./instances/soc-gplus.txt";
      readDataLS(g,s);
      break;
    }
    else if (a == 12) {
      cout << endl << "Introduce a valid path, otherwise the program will not run propertly" <<
      endl << "File path (./path): ";
      cin >> s;
      readDataLS(g,s);
      break;
    }
    else cout << "Introduce a valid option." << endl;
  }

    cout << endl << "Select the initial solution thechnique: " << endl << endl << "   1.Greedy"
    << endl << "   2.Initally all nodes are part of the S set" << endl << endl;
    while(cin >> a) {
      if (a == 1) {
        greedy greedy;
        greedy.IGA_PIDS(g, initialSolution);
        break;
      }
      else if (a == 2) {
        generateInitialSolution(g, initialSolution);
        break;
      }
      else cout << "Introduce a valid option." << endl;
    }
}


//-------------------------------------------MAIN------------------------------------------------//
int main(){
    Graph g;
    set<int> initialSolution;
    intputInfoLS(g, initialSolution);
    g.printNodeList();
    solutionLS(g, initialSolution);
}
