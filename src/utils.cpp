#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
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

std::vector<std::pair<Plate, std::vector<Well>>> utils::find(std::vector<Plate> plates, std::string name, double conc, double vol){
    if (conc == -1)
        std::cout << "searching for any concentration of " << name << std::endl;
    else
        std::cout << "searching for " << name << " at a concentration of " << conc << "uM" << std::endl;
    std::vector<std::pair<Plate, std::vector<Well>>> hits;
    for (int i=0; i < plates.size(); i++){
        std::vector<Well> tmp = {};
        if (conc != -1)
            tmp = plates[i].compoundExists(name, conc, vol);
        else
            tmp = plates[i].compoundExists(name, vol);
        if (tmp.size() > 0){
            std::cout << tmp.size() << " matches for: " << plates[i].getName() << std::endl;
            for (auto match : tmp)
                std::cout << match.toString() << ", located at well " << match.getStrCoords() << std::endl;
            hits.push_back(std::make_pair(plates[i], tmp));
        }
    }
    return hits;
}
std::vector<std::pair<Plate, std::vector<Well>>> utils::find(std::vector<Plate> plates, std::string name, double vol){
    return utils::find(plates, name, -1, vol);
}
void utils::serialDilution(Plate * plate, int r, int c, int n, double dilution){
    auto tmp = plate -> getWells();
    double conc = tmp[r][c].concentration;
    std::string compound = tmp[r][c].compound;
    double volume = tmp[r][c].volume;
    for (int i=1; i <= n; i++){
        conc /= dilution;
        plate -> changeWellContents(r, c+i, volume, conc, compound);
    }
}
Plate utils::read_plate_csv(std::string filename){
    std::fstream fin;
    fin.open(filename, std::ios::in);
    if(!fin.is_open()) throw std::runtime_error("Could not open file");
    std::string line, word, temp;
    std::vector<std::vector<std::pair<std::string, std::pair<double, double>>>> platevals;
    while (fin >> temp){
            std::vector<std::string> compounds = {};
            std::vector<double> concs,vols = {};
            std::vector<std::pair<std::string, std::pair<double,double>>> thisrow;
            for (int i=0; i <3; i++){
                getline(fin, line);
                char c;
                std::stringstream s(line);
                switch (i){
                    case 0:
                        /* std::cout << s.str() << std::endl; */
                        while (s.get(c)) {
                            if (c == ','){
                                compounds.push_back(word);
                                word = "";
                            } else{
                                if (c != ' ')
                                    word += c;
                            }
                        }
                        compounds.push_back(word);
                        break;
                    case 1:
                        /* s.ignore(255, ','); */
                        /* std::cout << s.str() << std::endl; */
                        getline(s, word, ',');
                        while (getline(s, word, ',')) {
                            if (word != "")
                                concs.push_back(stod(word));
                        }
                        break;
                    case 2:
                        /* s.ignore(255, ','); */
                        getline(s, word, ',');
                        while (getline(s, word, ',')) {
                            if (word != "")
                                vols.push_back(stod(word));
                        }
                        break;
                }

            }
            /* std::cout << compounds.size() << " " << concs.size() << " " << vols.size() << std::endl; */
            for(int i=0; i < compounds.size(); i++)
                thisrow.push_back(std::make_pair(compounds[i], std::make_pair(concs[i], vols[i])));
            platevals.push_back(thisrow);

    }
    int nrows = platevals.size();
    int ncols = platevals[0].size();
    /* std::cout << "nrows:" << platevals.size() << " ncols:" << platevals[0].size() << std::endl; */
    size_t lastindex = filename.find_last_of(".");
    std::string platename = filename.substr(0, lastindex); // strip off .csv or whatever extension
    Plate finalplate = Plate(nrows, ncols, 20, platename);
    for(int i=0; i < platevals.size(); i++)
        for(int j=0; j <platevals[0].size(); j++){
            /* std::cout << platevals[i][j].second.second << platevals[i][j].second.first << platevals[i][j].first << std::endl; */

            finalplate.changeWellContents(i,j, platevals[i][j].second.second, platevals[i][j].second.first, platevals[i][j].first);
        }

    return finalplate;

}

std::string utils::create_transfer_sheet(std::string filename, std::vector<Plate> &plates, bool mutate){
    std::fstream fin;
    fin.open(filename, std::ios::in);
    if(!fin.is_open()) throw std::runtime_error("Could not open file");
    std::string line, word, temp;
    std::vector<std::vector<std::pair<std::string, std::pair<double, double>>>> platevals;
    std::string finalsheet = "compound, concentration, source plate, source well, destination plate, destination well, volume \n";
    /* getline(fin, line); // skip label columns */

    getline(fin, line);
    while (getline(fin, line)){
        std::stringstream s(line);
        std::string compound, dest_plate, dest_well;
        double conc, volume;
        int idx= 0;
        while (getline(s, word, ',')){
            switch (idx){
                case 0:
                    compound = word;
                    break;
                case 1:
                    conc = stod(word);
                    break;
                case 2:
                    dest_plate = word;
                    break;
                case 3:
                    dest_well = word;
                    break;
                case 4:
                    volume = stod(word);
                    break;
            }
            idx++;
        }
        auto result = find(plates, compound, conc, volume);
/* std::vector<std::pair<Plate, std::vector<Well>>> utils::find(std::vector<Plate> plates, std::string name, double conc){ */
        if (result.size() > 0){
            int idx = 0;
            finalsheet += compound + "," + std::to_string(conc) + "," + result[idx].first.getName() + "," + result[idx].second[idx].getStrCoords() + "," + dest_plate + "," + dest_well + "," + std::to_string(volume) + "\n";
            if (mutate)
                for (Plate p : plates)
                    if (p.getName() == result[idx].first.getName()) // god this is so bad but it'll probably work
                        for (int i=0; i < p.getWells().size(); i++)
                            for (int j=0; j < p.getWells()[0].size(); j++)
                                if (p.getWells()[i][j].getStrCoords() == result[idx].second[idx].getStrCoords()){
                                    p.changeWellContents(i,j, -1.0* volume);
                                    p.save();
                                }
        }
        else
            finalsheet+= compound + "," + std::to_string(conc) + "," + "NOT FOUND" + "," "NOT FOUND" + "," + dest_plate + "," + dest_well + "," + std::to_string(volume) + "\n";
    }
    std::ofstream out("final_" + filename);
    out << finalsheet;
    out.close();
    return finalsheet;

}
