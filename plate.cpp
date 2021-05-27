#include "plate.h"
#include <tuple>
#include <vector>
Plate::Plate(int r, int c, double mv, std::string n){
    maxvol = mv;
    name = n;
    timesopened = 0;
    for (int i=0; i < r; i++){
        std::vector<Well> tmp (c, Well(mv));
        wells.push_back(tmp);
    }
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
std::vector<std::pair<Well, std::pair<int, int>>> Plate::compoundExists(std::string compound, double conc){
    std::vector<std::pair<Well, std::pair<int, int>>> matches;
    for (int row=0; row < wells.size(); row++){
        for (int col=0; col < wells[0].size(); col++){
            if (conc != -1){
                if (wells[row][col].compound == compound && wells[row][col].concentration == conc){
                    std::pair<Well, std::pair<int,int>> tmp = {wells[row][col], {row, col}};
                    matches.push_back(tmp);
                }
            }
            else{
                if (wells[row][col].compound == compound){
                    std::pair<Well, std::pair<int,int>> tmp = {wells[row][col], {row, col}};
                    matches.push_back(tmp);
                }
            }
        }
    }
    return matches;
}
std::vector<std::pair<Well, std::pair<int, int>>> Plate::compoundExists(std::string compound){
    return compoundExists(compound, -1);
}
