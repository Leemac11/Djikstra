#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


struct Node{
    Node(int position): pos(position){}
    bool checked = false;
    int pos;
    int output = 0;
    map<int, int> connections;
    vector<int> working;
    inline int shortest(){
        return *min_element(this->working.begin(), this->working.end());
    }
};


Node& nextNode(vector<Node>& nodes){
    int smallest = 10000;
    Node *smallestNode = nullptr;
    for(auto &n : nodes){
        if(n.checked != true){
           int disNodesSmallest = n.shortest();
           if(disNodesSmallest < smallest){
              smallest=disNodesSmallest;
              smallestNode = &n;
            }
        }
    }
    return *smallestNode;
}


void updateWorkingVals(Node *From, vector<Node>& nodes, vector<int>&NodesChecked){
    for(auto &connection : From->connections){
        Node* NodeAttached = &nodes[connection.first-1];
        NodeAttached->working.push_back(From->output + connection.second);
        NodeAttached->connections.erase(From->pos);
        if(NodeAttached->connections.empty()){
            cout << NodeAttached->shortest() << " ";
            NodeAttached->checked = true;
            NodesChecked[NodeAttached->pos-1] = 1;
        }
    }
}


void Djisktras(Node *currNode, vector<Node>& nodes, vector<int>&NodesChecked){
    while(find(NodesChecked.begin(), NodesChecked.end(), 0) != NodesChecked.end()){
        currNode->output = *min_element(currNode->working.begin(), currNode->working.end());
        cout << currNode->output << " ";
        currNode->checked = true;
        NodesChecked[currNode->pos-1]=1;
        updateWorkingVals(currNode, nodes, NodesChecked);
        currNode = &nextNode(nodes);
    }
    
}



int main() {
    int Test, NodeAmount, Arcs, startNode;
    cin >> Test;
    cin >> NodeAmount >> Arcs;
    vector<Node>nodes;
    vector<int> minimum_paths;
    vector<int>NodeChecked(NodeAmount, 0);
    for(int i = 1; i != NodeAmount+1; ++i){
        Node noddy(i);
        if(i == 1){
            noddy.working.push_back(0);
        }
        nodes.push_back(noddy);
    }
    
    for(int x = 0; x != Arcs; ++x){
        Node *from, *to;
        int start, end, dist;
        cin >> start >> end >> dist;
        from = &nodes[start-1];
        to = &nodes[end-1];
        from->connections.insert(make_pair(end, dist));
        to->connections.insert(make_pair(start, dist));
    }
    
    cin >> startNode;
    
    Djisktras(&nodes[startNode-1], nodes, NodeChecked);
    
    
    
    
    return 0;
}