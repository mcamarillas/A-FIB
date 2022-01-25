#include "basicsC.h"
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
void readDefaultGraphBasics(Graph &g) {
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
void readDataB(Graph &g, string s) {
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
  Reads the dominating set that will be used to check if is dominant or not.
*/
void readDominatingSet(set<int> &dominatingSet) {
    cout << endl << "Introduce the subset of nodes which pretends to be a PIDS:";
    cout << endl << "(Write -1 when you want to finish)" << endl << endl;
    int a;
    while(cin >> a and a != -1) {
        dominatingSet.insert(a);
    }
}

/*
  Display all possible graphs the user can test.
*/
void intputInfoB(Graph &g, set<int> &dominatingSet) {
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
      readDefaultGraphBasics(g);
      break;
    }
    else if (a == 2) {
      s = "./instances/ego-facebook.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 3) {
      s = "./instances/graph_actors_dat.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 4) {
      s = "./instances/graph_CA-AstroPh.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 5) {
      s = "./instances/graph_CA-CondMat.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 6) {
      s = "./instances/graph_CA-HepPh.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 7) {
      s = "./instances/graph_football.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 8) {
      s = "./instances/graph_jazz.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 9) {
      s = "./instances/socfb-Brandeis99.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 10) {
      s = "./instances/socfb-Mich67.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 11) {
      s = "./instances/soc-gplus.txt";
      readDataB(g,s);
      break;
    }
    else if (a == 12) {
      cout << endl << "Introduce a valid path, otherwise the program will not run propertly" <<
      endl << "File path (./path): ";
      cin >> s;
      readDataB(g,s);
      break;
    }
    else cout << "Introduce a valid option." << endl;
  }

    readDominatingSet(dominatingSet);
    basics b;
}

/*
    Gets the solution to the problem: given a dominatingSet say if isDominating
    or not.
*/
void solutionB(Graph &g, set<int> &dominatingSet) {

  // Get starting timepoint
  auto start = high_resolution_clock::now();

  basics b;
  int n = b.isPIDS(g, dominatingSet);

  // Get ending timepoint
  auto stop = high_resolution_clock::now();

  // Get duration. Substart timepoints to
  // get durarion. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Solution:" << endl << endl;

  if (n == 1) {
      cout << "   Is a Dominating Set. (Found in " << duration.count() << " microseconds)" << endl;
      auto start2 = high_resolution_clock::now();
      int n1 = b.isMinimalPIDS(g,dominatingSet);
      auto stop2 = high_resolution_clock::now();
      auto duration2 = duration_cast<microseconds>(stop2 - start2);
      if(n1) cout << "   Is Minimal.";
      else cout << "   Is NOT Minimal.";
      cout << " (Found in " << duration2.count() << "microseconds)" << endl;
      cout << endl;
    }
    else cout << "Is NOT a Dominating Set" << endl;
}

//-------------------------------------------MAIN------------------------------------------------//
int main() {
    Graph g;
    set<int> dominatingSet;
    intputInfoB(g, dominatingSet);
    g.printNodeList();
    solutionB(g, dominatingSet);

}
