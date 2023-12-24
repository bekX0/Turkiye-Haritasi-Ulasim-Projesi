#include <iostream>
#include "Graph.h"
#include <fstream>

using namespace std;

int main(){
    //city codes prep
    // unordered_map<int, string> cityCode; // purpose => || 1->"Adana" || 2->"Adıyaman" -----

    // ifstream file("cities.txt");
    // string line; //? pointer kullansam sonrasında line kullanılmayacak || file da değişecek ?
    // int ctr = 1; // 1 adana ile başlayacak
    // while(getline(file, line)){
    //     cityCode[ctr] = line;
    // }


    string files[] = {"cityCodes.txt", "adjacent_cities.txt", "CityDistances.txt"};
    Graph G(files);

    cout << G;

}