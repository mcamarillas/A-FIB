#include "greedyC.h"
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
    Reads the nodes which will form the new graph.
*/
void readData(Graph &g, string s) {
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
  Solves the problem using Pans algorithm.
*/
void solve(Graph &g) {

  vector<int> v;
  g.getAdjacent(2,v);

  greedy greed;
  set<int> sol;

  // Get starting timepoint
  auto start = high_resolution_clock::now();

  greed.Pans(g, sol);
  set<int>::iterator it = sol.begin();

  // Get ending timepoint
  auto stop = high_resolution_clock::now();

  // Get duration. Substart timepoints to
  // get durarion. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<microseconds>(stop - start);


  basics b;
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
    cout << endl << "   Solution: (found in " << duration.count() << " microseconds)" << endl;
    vector<int> v;
    g.getNodes(v);
    cout << endl << "       Size of the set: " << sol.size() << ". Which represents " << (sol.size()/float(v.size()))*100 << "% of the nodes." << endl;
    start = high_resolution_clock::now();
    bool bool1 = b.isMinimalPIDS(g,sol);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    if(bool1) cout << "       Found set is minimal";
    else cout << "      Found set is not minimal";
    cout << endl << "       Checked in " << duration.count() << " microseconds" << endl;
  }
  else cout << "        This graph has no dominating set" << endl;
  cout << endl;
  bool first = true;
}

/*
  Display all possible graphs the user can test.
*/
void intputInfoG(Graph &g) {
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
        readData(g,s);
        break;
      }
      else if (a == 3) {
        s = "./instances/graph_actors_dat.txt";
        readData(g,s);
        break;
      }
      else if (a == 4) {
        s = "./instances/graph_CA-AstroPh.txt";
        readData(g,s);
        break;
      }
      else if (a == 5) {
        s = "./instances/graph_CA-CondMat.txt";
        readData(g,s);
        break;
      }
      else if (a == 6) {
        s = "./instances/graph_CA-HepPh.txt";
        readData(g,s);
        break;
      }
      else if (a == 7) {
        s = "./instances/graph_football.txt";
        readData(g,s);
        break;
      }
      else if (a == 8) {
        s = "./instances/graph_jazz.txt";
        readData(g,s);
        break;
      }
      else if (a == 9) {
        s = "./instances/socfb-Brandeis99.txt";
        readData(g,s);
        break;
      }
      else if (a == 10) {
        s = "./instances/socfb-Mich67.txt";
        readData(g,s);
        break;
      }
      else if (a == 11) {
        s = "./instances/soc-gplus.txt";
        readData(g,s);
        break;
      }
      else if (a == 12) {
        cout << endl << "Introduce a valid path, otherwise the program will not run propertly" <<
        endl << "File path (./path): ";
        cin >> s;
        readData(g,s);
        break;
      }
      else cout << "Introduce a valid option." << endl;
    }
}

//-------------------------------------------MAIN------------------------------------------------//
int main() {
    Graph g;
    intputInfoG(g);
    g.printNodeList();
    solve(g);
}
