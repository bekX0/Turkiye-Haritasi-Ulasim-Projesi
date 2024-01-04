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
    int baseCity = 1;
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
            if(targetCity == baseCity){
                ++targetCity;
                continue;
            }
            Node* vertex = adjacentVertex(baseCity, targetCity);
            if(vertex != nullptr){
                set_edge_value(vertex, stoi(token));
                ++edgeCount;
            }
            ++targetCity;
        }
        ++baseCity;
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

string Graph::toString(int code){
    stringstream result;
    result << "---------------------------------------------------------------" << endl;
    result << "City Name: " << labelOfNodes[code-1] << endl;
    result << "City Code: " << code << endl;
    result << "Adjacent Cities: " << adjList[code] << endl;
    result << "---------------------------------------------------------------" << endl;
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

    if(city == nullptr) return -1;
    else return city->edgeCost;
}

bool Graph::set_edge_value(int x, int y, int cost){
    Node* city = adjacentVertex(x, y);

    if(city == nullptr) return false;
    else{
        city->edgeCost = cost;
        return true;
    }
}
bool Graph::set_edge_value(Node* city, int cost){
    if(!city) return false;
    city->edgeCost = cost;
    return true;
}
pair<int*, int*> Graph::dijkstra(int cityCode){
    int* dist = new int[this->V];
    int* pre = new int[this->V];
    for(int i=0; i< this->V;++i){
        dist[i] = INT_MAX;
        pre[i] = -1;
    }
    // vector<int> dist(this->V, INT_MAX);
    // vector<int> pre(this->V, -1);
    vector<bool> isExplored(this->V, false);
    priority_queue<Node*, vector<Node*>, CompareNodes> pq;

    dist[cityCode-1] = 0;
    isExplored[cityCode-1] = true;
    
    Node* travel = this->adjList[cityCode].getHead();
    while(travel){
            pq.push(travel);
            dist[travel->value - 1] = travel->edgeCost;
            pre[travel->value -1] = cityCode;
            travel = travel->next;
    }
    
    
    
    do{
        Node* exploreNode = pq.top();
        pq.pop();
        isExplored[exploreNode->value - 1] = true;
        Node* travel = this->adjList[exploreNode->value].getHead();
        while(travel){
            if(isExplored[travel->value - 1]){
                travel = travel->next;
                continue;
            }else{
                pq.push(travel);
                if(travel->edgeCost + dist[exploreNode->value - 1] < dist[travel->value - 1]){
                    dist[travel->value - 1] = travel->edgeCost + dist[exploreNode->value - 1];
                    pre[travel->value -1] = exploreNode->value; // writes pre, previous cityCode
                }
            }
            travel = travel->next;
        }
    }while(!pq.empty());

    // for(int i = 1; i <= V; ++i){
    //     cout << "İl:" << i << " en kısa yol:" << dist[i-1] << " pre=> " << pre[i-1] << endl;
    // }

    return make_pair(dist, pre);
}

void Graph::findKShortestCities(int cityCode, int k){
    pair<int*, int*> results = dijkstra(cityCode);

    int* distances = results.first;
    int* kCities = new int[k];

    for(int i=0; i < k; ++i){
        int min = INT_MAX;
        int idx_min = -1;
        for(int j = 0; j < this->V;++j){
            if(distances[j] == 0) continue;
            if(distances[j] < min){
                min = distances[j];
                idx_min = j;
            }
        }
        kCities[i] = idx_min +1;
        distances[idx_min] = 0;
    }

    for(int i = 0; i< k; ++i){
        cout << kCities[i] << "->";
    }
    cout<< endl;

    delete[] distances;
    delete[] kCities;
    
    return;
}

void Graph::shortestPath(int startCity, int targetCity){
    pair<int*, int*> results = dijkstra(startCity);

    int* distances = results.first;
    int* predecessors = results.second;

    int cityCode = targetCity;
    string road = to_string(targetCity);

    while(predecessors[cityCode-1] != -1){
        cityCode = predecessors[cityCode-1];
        road = to_string(cityCode) + "(" + labelOfNodes[cityCode-1] + ")" + "->" + road;
    }

    cout << endl << road << "=>>" << distances[targetCity-1] << endl;

    delete[] distances;
    delete[] predecessors;

    return;
//----------------------------------------------------------------