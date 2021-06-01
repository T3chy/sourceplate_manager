#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include "utils.cpp"


int main(){

    Plate pp = Plate(12,16,20.0, "Elam");
    Plate dd = Plate(12,16,20.0, "Doug's plate");
    std::vector<std::vector<Well>> tmp = pp.getWells();
    pp.changeWellContents(10,1, 10, .1, "abc");
    utils::serialDilution(&pp, 10, 1, 12, 2.0);
    pp.save();
    std::vector<Plate> b = {pp};
    utils::find(b, "abc");


}
