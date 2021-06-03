#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include "utils.h"
/* #include "sheet.h" */


int main(){

    Plate doug = utils::read_plate_csv("test.csv");
    std::vector<Plate> plates = {doug};
    /* std::cout << doug.toString() << std::endl; */
    utils::find(plates, "CT-42210");
    std::cout << utils::create_transfer_sheet("t.csv", plates) << std::endl;


}
