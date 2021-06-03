#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include "plate.h"
namespace utils{
    std::vector<std::pair<Plate, std::vector<Well>>> find(std::vector<Plate> plates, std::string name, double conc);
    std::vector<std::pair<Plate, std::vector<Well>>> find(std::vector<Plate> plates, std::string name);
    void serialDilution(Plate * plate, int r, int c, int n, double dilution);
    Plate read_csv(std::string filename);
}