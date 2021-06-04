#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include "plate.h"
namespace utils{
    std::vector<std::pair<Plate, std::vector<Well>>> find(std::vector<Plate> plates, std::string name, double conc, double vol);
    std::vector<std::pair<Plate, std::vector<Well>>> find(std::vector<Plate> plates, std::string name, double vol);
    void serialDilution(Plate * plate, int r, int c, int n, double dilution);
    Plate read_plate_csv(std::string filename);
    std::string create_transfer_sheet(std::string filename, std::vector<Plate> & plates, bool mutate);
}
