#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
//typedef pair<bool,vector<int>> infoVertex;

class Graph {
	private:
		int graphSize;
		map<int,vector<int>> adjacentList;
		set<int> dominatingSet;

		bool existsNode(int node);
		bool existsEdge(int node1, int node2);
		void addAdjacent(int node1, int node2);
		bool isInDominatingSet(int node);

	public:

		// Constructora
		Graph();

		// Consultora
		int size();
		bool isMIPDS(set<int> &dominatingSet);
		int getDegree(int node);
		void getNodes(vector<int> &v);
		void getSetNodes(set<int> &s);
		void getAdjacent(int node, vector<int> &v);
		void getSetAdjacent(int node, set<int> &s);

		// Modificadora
		bool addEdge(int node1, int node2);
		bool addNode(int node);

		// Prints
		void printNodeList();
};
