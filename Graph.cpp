#include "Graph.h"
//constructors
Graph::Graph(string files[]){
    //to declare codes
    unordered_map<string, int> cityCodes;
    ifstream file(files[0]);
    string line;
    int lineCounter = 0;
    while(getline(file, line)){
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        int code = stoi(token);

        getline(ss, token, ',');

        cityCodes[token] = code;
        labelOfNodes.push_back(token);
        adjList[code] = LinkedList();
        ++lineCounter;
    }
    file.close();
    V=lineCounter;

    //to declare adjacents
    ifstream file2(files[1]);
    lineCounter = 1;
    while(getline(file2, line)){
        stringstream ss(line);
        string token;
        getline(ss, token, ','); // avoid first city (its the center)
        
        while(getline(ss, token, ',')){
            int code = cityCodes[token];

            adjList[lineCounter].insert(code);
        }
        ++lineCounter;
    }
    file2.close();
    //to declare costs 
    ifstream file3(files[2]);
    lineCounter = 1;
    //avoid first line (titles)
    getline(file3, line);
    int edgeCount = 0;
    while(getline(file3, line)){
        stringstream ss(line);
        string token;
        getline(ss, token, ';'); // code
        getline(ss, token, ';'); // city
        int targetCity = 1;
        while(getline(ss, token, ';')){
            if(targetCity == lineCounter){
                ++targetCity;
                continue;
            }
            Node* vertex = adjacentVertex(lineCounter, targetCity);
            if(vertex != nullptr){
                vertex->edgeCost = stoi(token);
                ++edgeCount;
            }
            ++targetCity;
        }
        ++lineCounter;
    }
    file3.close();

    E = edgeCount;
}
//-----------------------------------------------------------------------

//methods
bool Graph::adjacent(int x, int y){
    Node* searchNode = adjList[x].getHead();
    while (searchNode != nullptr && searchNode->value != y){
        searchNode = searchNode->next;
    }
    if(searchNode == nullptr){
        searchNode = nullptr;
        return false;
    }else{
        searchNode = nullptr;
        return true;
    }
}

Node* Graph::adjacentVertex(int x, int y){
    Node* searchNode = adjList[x].getHead();
    while (searchNode != nullptr && searchNode->value != y){
        searchNode = searchNode->next;
    }
    
    return searchNode;
}

LinkedList Graph::neighbors(int x){
    return adjList[x];
}

//!add edge ile remove edge i değiştir zaten linkedlist çıkarıyor
bool Graph::add_edge(int x, int y){
    if(adjacent(x, y)) return false; //! yeni metodla değitşir

    // Node* cur = adjList[x].getHead();
    // while(cur->next != nullptr){
    //     cur = cur->next;
    // }
    // Node* newAdj = new Node(y);
    // cur->next = newAdj;
    // return true;
    adjList[x].insert(y);
    return true;
}

bool Graph::remove_edge(int x, int y){
    if(!adjacent(x, y)) return false; //! yeni metodla değitşir

    // Node* cur = adjList[x].getHead();
    // Node* pre = nullptr;
    // while(cur->value != y){
    //     pre = cur;
    //     cur = cur->next;
    // }
    // pre->next = cur->next;
    // pre = nullptr;
    // delete cur;
    // delete pre;
    adjList[x].remove(y);
    return true;
}

int Graph::getV() {return V;}

int Graph::getE() {return E;}

string Graph::toString(){
    stringstream result;
    for(int i = 1; i<=V; ++i){
        result << "---------------------------------------------------------------" << endl;
        result << "City Name: " << labelOfNodes[i-1] << endl;
        result << "City Code: " << i << endl;
        result << "Adjacent Cities: " << adjList[i] << endl;
        result << "---------------------------------------------------------------" << endl;
    }
    return result.str();
}

ostream& operator<<(ostream& os, const Graph& G) {
    for (int i = 1; i <= G.V; ++i) {
        os << "---------------------------------------------------------------" << endl;
        os << "City Name: " << G.labelOfNodes[i-1] << endl;
        os << "City Code: " << i << endl;
        os << "Adjacent Cities: " << G.adjList.at(i) << endl;
        os << "---------------------------------------------------------------" << endl;
    }
    return os;
}

int Graph::get_edge_value(int x, int y){
    Node* city = adjacentVertex(x, y);

    if(city) return -1;
    else return city->edgeCost;
}

bool Graph::set_edge_value(int x, int y, int cost){
    Node* city = adjacentVertex(x, y);

    if(city) return false;
    else{
        city->edgeCost = cost;
        return true;
    }
}
//----------------------------------------------------------------