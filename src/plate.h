#include<string>
#include <vector>
#pragma once

#ifndef WELL_H
#define WELL_H
class Well{
    private:
        int row;
        int col;
    public:
        double concentration;
        double volume;
        double maxvol;
        std::string compound;
        /* Well(double vol, std::string comp, double conc, double maxvol); */
        Well(double maxvol);
        Well(double maxvol, int r, int c);
        int getRow(){return row;}
        int getCol(){return col;}
        std::pair<int, int>getCoords(){return std::make_pair(row, col);}
        std::string getStrCoords();
        void setCoords(int r, int c){row = r; col = c;}
        int changeVol(double amt);
        bool canChange(double amt);
        std::string toString(){return (volume == 0) ? "Empty!" : std::to_string(volume) + "uL of " + compound + " at " + std::to_string(concentration) + "uM";}
};
#endif

#ifndef PLATE_H
#define WELL_H
class Plate{
    private:
        double maxvol;
        std::string name;
        std::vector<std::vector<Well>> wells;
        int timesopened;
        bool opened_this_session;
    public:
        std::vector<std::vector<Well>> getWells() {return wells;}
        std::string getName() {return name;}
        std::string toString();
        int save();

        Plate(int r, int c, double mv, std::string name);
        std::string changeWellContents(int r, int c, double vol);
        std::string changeWellContents(int r, int c, double vol, double conc, std::string compound);
        std::vector<Well> compoundExists(std::string compound, double conc, double vol);
        std::vector<Well> compoundExists(std::string compound, double conc);
        std::vector<Well> compoundExists(std::string compound);
};
#endif
