#include <iostream>
#include "Graph.h"

using namespace std;

void displayMenu();
int citySelection();

int main(){
    string files[] = {"cityCodes.txt", "adjacent_cities.txt", "CityDistances.txt"};
    Graph G(files); 

    char option;
    int selectedCity;
    do{
        displayMenu();
        cin >> option;
        switch (option)
        {
        case 'a':
            selectedCity = citySelection();
            if(selectedCity < 0 || G.getV() < selectedCity){
                cout << "City does not exists!" << endl;
            }else{
                cout << "City Successfully Selected!" << endl;
            }
            break;
        case 'b':
            cout << G.toString(selectedCity);
            break;     
        case 'c':
            if(G.getV() < selectedCity && selectedCity < 0) break;
            int k;
            cout << "k: ";
            cin >> k;
            G.findKShortestCities(selectedCity, k); 
            break;
        case 'd':
            int target;
            cout << "Target city code: ";
            cin >> target;
            G.shortestPath(selectedCity, target);
            break;   
        default:
            break;
        }
    }while(option!= 'x');

    cout << "Exiting...";
    
    return 0;
}

void displayMenu(){
    cout << endl <<"a.Enter city(or select)\nb.Print selected(or entered) city\nc. List k closest  cities (to selected city)\nd. Find shortest path to\nx.Exit" << endl;
}
int citySelection(){
    int selection;
    cout << "Enter city code: ";
    cin >>  selection;
    return selection;
}
