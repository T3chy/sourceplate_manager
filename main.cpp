#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include "utils.h"
#include "sheet.h"


int main(){

    Plate doug = utils::read_csv("test.csv");
    std::vector<Plate> plates = {doug};
    std::cout << doug.toString() << std::endl;
    utils::find(plates, "CT-42210");


}
