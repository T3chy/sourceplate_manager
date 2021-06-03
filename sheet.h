#include "plate.h"
#include "utils.h"
typedef struct transfer{
    double volume;
    std::string sourceplate;
    std::string destplate;
    std::string sourcewell;
    std::string destwell;
    transfer(std::string sp, std::string sw, std::string dp, std::string dw, double vol){
        sourceplate = sp;
        destplate = dp;
        sourcewell = sw;
        destwell = dw;
        volume = vol;
    }
    std::string toString() {
        return sourceplate + "," + sourcewell + "," + destplate + "," + destwell + "," + std::to_string(volume);
    };
} transfer;
class Sheet{
    std::vector<Plate> sourcePlates;
    std::vector<Plate> destPlates;
    Sheet(std::vector<Plate> avail_plates, std::vector<Plate> dp){sourcePlates = avail_plates;destPlates = dp;}
    std::vector<transfer> transfers;
    void addTransfer(std::string compound, double conc, Plate destplate, Well destwell, double vol);
    void addTransfer(Plate sourceplate, Well sourcewell, Plate destplate, Well destwell, double vol);
    void read_csv(std::string filename);
    void save(std::string name);
    std::string toString();

};
