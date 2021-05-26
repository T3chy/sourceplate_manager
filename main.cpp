#include "plate.h"
#include<iostream>

int main(){
    Plate pp = Plate(12,16,20.0);
    std::vector<std::pair<Well, std::tuple<int, int, double>>> b = pp.compoundExists("peepeepoopoo");
    std::cout << b.size() << std::endl;
    /* std::cout << "bruh" << std::endl; */





}
