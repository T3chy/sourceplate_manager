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
};
#endif

#ifndef PLATE_H
#define WELL_H
class Plate{
    private:
        double maxvol;
        int timesopened;
        std::vector<std::vector<Well>> wells;
    public:
        Plate(int r, int c, double mv);
        std::string changeWellContents(int r, int c, double vol);
        std::string changeWellContents(int r, int c, double vol, double conc, std::string compound);
        std::vector<std::pair<Well, std::tuple<int, int, double>>> compoundExists(std::string compound, double conc);
        std::vector<std::pair<Well, std::tuple<int, int, double>>> compoundExists(std::string compound);
};
#endif
