#include "plate.h"
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
Plate::Plate(int r, int c, double mv, std::string n){
    maxvol = mv;
    name = n;
    timesopened = 0;
    for (int i=0; i < r; i++){
        std::vector<Well> tmp (c, Well(mv));
        wells.push_back(tmp);
    }
    for (int i=0; i < wells.size(); i++)
        for (int j=0; j < wells[0].size(); j++)
            wells[i][j].setCoords(i, j);
}
bool Well::canChange(double amt){
    if (amt > 0)
        return (amt + volume <= maxvol);
    else
        return (amt >= volume);
}
Well::Well(double mv){
    maxvol = mv;
    volume = 0;
    compound = "";
    concentration = 0;
}
int Well::changeVol(double vol){
    if (vol == 0)
        return 0;
    if (canChange(vol)) {
        volume += vol;
        return vol;
    }

    return -1;
}

std::string Plate::toString (){
    std::string tmp = "";
    for (int i=0; i < wells.size(); i++) {
        std::string names = "";
        std::string concs = "";
        std::string vols = "";
        for (int j=0; j < wells[0].size(); j++){
            names += wells[i][j].compound + ",";
            concs += std::to_string(wells[i][j].concentration) + ",";
            vols += std::to_string(wells[i][j].volume) + ",";
        }
        tmp += "compound, " + names + "\n" + "concentration (uM), " + concs + "\n" + "volume (uL), " + vols + "\n";

    }
    return tmp;
}
std::string Plate::changeWellContents(int r, int c, double vol){
    if (wells[r][c].changeVol(vol) == -1)
            throw(vol);

    return wells[r][c].compound;

}
std::string Plate::changeWellContents(int r, int c, double vol, double conc, std::string compound){
    if (wells[r][c].volume == 0){
        if (wells[r][c].canChange(vol)){
            wells[r][c].compound = compound;
            wells[r][c].concentration = conc;
            wells[r][c].changeVol(vol);
            return compound;
        } else
            throw(vol);
    }
    throw(compound);
}
std::vector<Well> Plate::compoundExists(std::string compound, double conc){
    std::vector<Well> matches;
    for (int row=0; row < wells.size(); row++){
        for (int col=0; col < wells[0].size(); col++){
            if (conc != -1){
                if (wells[row][col].compound == compound && wells[row][col].concentration == conc){
                    matches.push_back(wells[row][col]);
                }
            }
            else{
                if (wells[row][col].compound == compound){
                    matches.push_back(wells[row][col]);
                }
            }
        }
    }
    return matches;
}
std::vector<Well> Plate::compoundExists(std::string compound){
    return compoundExists(compound, -1);
}
int Plate::save(){
    std::ofstream out(name + ".csv");
    out << this -> toString();
    out.close();
    return 0;
}
std::string Well::getStrCoords(){
    char tmp = 'A' + (char)col; // c is 0 indexed
    return tmp + std::to_string(row);
}
