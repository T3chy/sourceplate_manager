#include "sheet.h"
#include "utils.h"

#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
std::string Sheet::toString (){
    std::string tmp = "Source Plate Barcode,Source Well,Destination Plate Barcode,Destination Well,Transfer Volume\n";
    for (int i=0; i < transfers.size(); i++)
        tmp += transfers[i].toString() + "\n";
    return tmp;
}
void Sheet::save(std::string name){
    std::ofstream out(name + ".csv");
    out << this -> toString();
    out.close();
}
void Sheet::addTransfer(std::string compound, double conc, Plate destplate, Well destwell, double vol){
    auto matches = utils::find(sourcePlates, compound, conc);
    if (matches.size() > 0)
        transfers.push_back(transfer(matches[0].first.getName(), matches[0].second[0].getStrCoords(), destplate.getName(), destwell.getStrCoords(),vol));
    else
        throw "nothing found!";
}
void Sheet::addTransfer(Plate sourceplate, Well sourcewell, Plate destplate, Well destwell, double vol){
    transfers.push_back(transfer(sourceplate.getName(), sourcewell.getStrCoords(), destplate.getName(), destwell.getStrCoords(), vol));
}
