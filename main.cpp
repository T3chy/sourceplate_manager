#include "plate.h"
#include<iostream>

int main(){
    Plate pp = Plate(12,16,20.0);
    std::vector<std::vector<Well>> tmp = pp.getWells();
    std::cout << pp.changeWellContents(10,15, 10, .1, "abc") << std::endl;
    std::cout << pp.getWells()[0][0].toString() << std::endl;

    std::vector<std::pair<Well, std::pair<int, int>>> b = pp.compoundExists("abc");
    std::cout << b[0].second.first << " " << b[0].second.second << std::endl;
    /* std::cout << "bruh" << std::endl; */





}
