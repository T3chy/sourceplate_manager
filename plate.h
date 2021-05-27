#include<string>
#include <vector>
#include<tuple>

#ifndef WELL_H
#define WELL_H
class Well{
    public:
        double concentration;
        double volume;
        double maxvol;
        std::string compound;
        /* Well(double vol, std::string comp, double conc, double maxvol); */
        Well(double maxvol);
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
        int timesopened;
        std::string name;
        std::vector<std::vector<Well>> wells;
    public:
        std::vector<std::vector<Well>> getWells() {return wells;}
        std::string getName() {return name;}

        Plate(int r, int c, double mv, std::string name);
        std::string changeWellContents(int r, int c, double vol);
        std::string changeWellContents(int r, int c, double vol, double conc, std::string compound);
        std::vector<std::pair<Well, std::pair<int, int>>> compoundExists(std::string compound, double conc);
        std::vector<std::pair<Well, std::pair<int, int>>> compoundExists(std::string compound);
};
#endif
