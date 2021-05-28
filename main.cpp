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
void serialDilution(Plate * plate, int r, int c, int n, double dilution){
    auto tmp = plate -> getWells();
    double conc = tmp[r][c].concentration;
    std::string compound = tmp[r][c].compound;
    double volume = tmp[r][c].volume;
    for (int i=1; i <= n; i++){
        conc /= dilution;
        plate -> changeWellContents(r, c+i, volume, conc, compound);
    }
}

int main(){
    Plate pp = Plate(12,16,20.0, "Elam's plate");
    std::vector<std::vector<Well>> tmp = pp.getWells();
    pp.changeWellContents(10,1, 10, .1, "abc");
    serialDilution(&pp, 10, 1, 5, 2.0);
    /* std::cout << pp.changeWellContents(10,15, 10, .1, "abc") << std::endl; */
    /* std::cout << pp.getWells()[0][0].toString() << std::endl; */
    std::cout << pp.toString() << std::endl;

    auto col = {pp};
    auto b = find(col, "abc");
    /* std::cout << b[0].first << " "  << std::endl; */
}
