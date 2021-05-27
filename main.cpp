#include "plate.h"
#include<iostream>
#include<vector>

std::vector<std::pair<std::string, std::vector<std::pair<Well, std::pair<int, int>>>>> find(std::vector<Plate> plates, std::string name, double conc){
    std::vector<std::pair<std::string, std::vector<std::pair<Well, std::pair<int, int>>>>> hits;
    for (int i=0; i < plates.size(); i++){
        std::vector<std::pair<Well, std::pair<int, int>>> tmp = {};
        if (conc != -1)
            tmp = plates[i].compoundExists(name, conc);
        else
            tmp = plates[i].compoundExists(name);
        if (tmp.size() > 0)
            hits.push_back(std::make_pair(plates[i].getName(), tmp));
    }
    return hits;
}
std::vector<std::pair<std::string, std::vector<std::pair<Well, std::pair<int, int>>>>> find(std::vector<Plate> plates, std::string name){
    return find(plates, name, -1);
}
int main(){
    Plate pp = Plate(12,16,20.0, "Elam's plate");
    std::vector<std::vector<Well>> tmp = pp.getWells();
    std::cout << pp.changeWellContents(10,15, 10, .1, "abc") << std::endl;
    std::cout << pp.getWells()[0][0].toString() << std::endl;

    auto col = {pp};
    auto b = find(col, "abc");
    std::cout << b[0].first << " "  << std::endl;
}
