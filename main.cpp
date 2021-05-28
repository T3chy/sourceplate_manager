#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>


std::vector<std::pair<std::string, std::vector<std::pair<Well, std::pair<int, int>>>>> find(std::vector<Plate> plates, std::string name, double conc){
    if (conc == -1)
        std::cout << "searching for any concentration of " << name << std::endl;
    else
        std::cout << "searching for " << name << " at a concentration of " << conc << "uM" << std::endl;
    std::vector<std::pair<std::string, std::vector<std::pair<Well, std::pair<int, int>>>>> hits;
    for (int i=0; i < plates.size(); i++){
        std::vector<std::pair<Well, std::pair<int, int>>> tmp = {};
        if (conc != -1)
            tmp = plates[i].compoundExists(name, conc);
        else
            tmp = plates[i].compoundExists(name);
        if (tmp.size() > 0){
            std::cout << "matches for: " << plates[i].getName() << std::endl;
            for (auto match : tmp)
                std::cout << match.first.toString() << ", located at row " << match.second.first << " column " << match.second.second << std::endl;
            hits.push_back(std::make_pair(plates[i].getName(), tmp));
        }
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
Plate read_csv(std::string filename){
    std::fstream fin;
    fin.open(filename, std::ios::in);
    std::string line, word, temp;
    std::vector<std::vector<std::pair<std::string, std::pair<double, double>>>> platevals;
    int nrows = 0;
    int ncols = 0;
    while (fin >> temp){
        std::vector<std::string> compounds = {};
        std::vector<double> concs,vols = {};
        std::vector<std::pair<std::string, std::pair<double,double>>> thisrow;
        for (int i=0; i <3; i++){
            getline(fin, line);
            std::stringstream s(line);
            getline(s, word, ','); // skip first column (has labels)
            switch (i){
                case 0:
                    while (getline(s, word, ',')) {
                        compounds.push_back(word);
                    }
                    break;
                case 1:
                    while (getline(s, word, ',')) {
                        concs.push_back(stod(word));
                    }
                    break;
                case 2:
                    while (getline(s, word, ',')) {
                        vols.push_back(stod(word));
                    }
                    break;
            }

        }
        for(int i=0; i < compounds.size(); i++)
            thisrow.push_back(std::make_pair(compounds[i], std::make_pair(concs[i], vols[i])));
        platevals.push_back(thisrow);
        ncols = thisrow.size();
        nrows++;
    }
    std::cout << "nrows:" << nrows << " ncols:" << ncols << std::endl;
    size_t lastindex = filename.find_last_of(".");
    std::string platename = filename.substr(0, lastindex); // strip off .csv or whatever extension
    Plate finalplate = Plate(nrows, ncols, 20, filename);
    for(int i=0; i < platevals.size(); i++)
        for(int j=0; j <platevals[0].size(); j++)
            finalplate.changeWellContents(i,j, platevals[i][j].second.second, platevals[i][j].second.first, platevals[i][j].first);

    return finalplate;

}

int main(){

    Plate pp = Plate(12,16,20.0, "Elam's plate");
    Plate dd = Plate(12,16,20.0, "Doug's plate");
    std::vector<std::vector<Well>> tmp = pp.getWells();
    pp.changeWellContents(10,1, 10, .1, "abc");
    serialDilution(&pp, 10, 1, 5, 2.0);
    dd.changeWellContents(10,1, 10, .1, "abc");
    serialDilution(&dd, 10, 1, 5, 2.0);
    /* std::cout << pp.changeWellContents(10,15, 10, .1, "abc") << std::endl; */
    /* std::cout << pp.getWells()[0][0].toString() << std::endl; */

    Plate p = read_csv("test.csv");
    auto col = {pp,dd,p};
    auto b = find(col, "abc", .1);

    std::cout << b.size() <<  " "  << std::endl;
}
