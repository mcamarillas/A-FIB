#include "Graph.h"

// ---------------------------Métodos Privados----------------------------------------

bool Graph::existsNode(int node) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node);
    return it != adjacentList.end();
}

bool Graph::existsEdge(int node1, int node2) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node1);
    if(it != adjacentList.end()) {
        for(int i = 0; i < it->second.size(); ++i) {
            if(it->second[i] == node2) return true;
        }
    }
    return false;
}

void Graph::addAdjacent(int node1, int node2) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node1);
    if(it != adjacentList.end()) {
        it->second.push_back(node2);
    }
}

bool Graph::isInDominatingSet(int node) {
    set<int>::iterator it;
    it = dominatingSet.find(node);
    return it != dominatingSet.end();
}



// ---------------------------Constructoras-------------------------------------- //

Graph::Graph() {
    graphSize = 0;
}

// ----------------------------Consultoras---------------------------------------- //


int Graph::size() {
    return graphSize;
}

bool Graph::isMIPDS(set<int> &dominatingSet) {
    this->dominatingSet = dominatingSet;
    map<int,vector<int>>::iterator it;
    it = adjacentList.begin();
    bool isDominating = true;
    while(it != adjacentList.end() and isDominating) {
        int count = 0;
        int size = it->second.size();
        for(int i = 0; i < size; ++i) {
            if(isInDominatingSet(it->second[i])) ++count;
        }
        isDominating = count >= size/2;
        ++it;
    }
    return isDominating;
}

int Graph::getDegree(int node) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node);
    if(it == adjacentList.end()) return -1;
    return it->second.size();
}

void Graph::getNodes(vector<int> &v) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.begin();
    while(it != adjacentList.end()) {
        v.push_back(it->first);
        ++it;
    }
}

void Graph::getSetNodes(set<int> &s){
    map<int,vector<int>>::iterator it;
    it = adjacentList.begin();
    while(it != adjacentList.end()) {
        s.insert(it->first);
        ++it;
    }
}


void Graph::getAdjacent(int node, vector<int> &v) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node);
    if(it != adjacentList.end()) {
        for(int i = 0; i < it->second.size(); ++i) {
            v.push_back(it->second[i]);
        }
    }
}

void Graph::getSetAdjacent(int node, set<int> &s) {
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node);
    if(it != adjacentList.end()) {
        for(int i = 0; i < it->second.size(); ++i) {
            s.insert(it->second[i]);
        }
    }
}

// ---------------------------Modificadoras--------------------------------------- //


bool Graph::addEdge(int node1, int node2){
    if(node1 != node2 and !existsEdge(node1,node2) and existsNode(node1) and existsNode(node2)) {
        addAdjacent(node1,node2);
        addAdjacent(node2,node1);
        return true;
    }
    return false;
}

bool Graph::addNode(int node) {
    if(existsNode(node)) return false;
    graphSize++;
    map<int,vector<int>>::iterator it;
    it = adjacentList.find(node);
    if(it == adjacentList.end()) {
        vector<int> v;
        adjacentList[node] = v;
    }
    return true;
}

// -------------------------------Prints---------------------------------------- //


void Graph::printNodeList() {
    cout << endl << "Introduced graph:" << endl << endl;
    map<int,vector<int>>::iterator it = adjacentList.begin();
    while(it != adjacentList.end()) {
        cout <<  "    " << it->first << "--> [";
        bool first = true;
        for(int i = 0; i < it->second.size(); ++i) {
            if (first) {
                first = false;
            }
            else cout << ",";
            cout << it->second[i];
        }
        cout << "]" << endl;
        it++;
    }
    cout << endl;
}
