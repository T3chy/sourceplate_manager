#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include "utils.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

std::vector<std::string> getsourcefiles(){
    std::vector<std::string> filenames;
    DIR *d;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    d = opendir("plates/");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            p1=strtok(dir->d_name,".");
            p2=strtok(NULL,".");
            if(p2!=NULL)
            {
                ret=strcmp(p2,"csv");
                if(ret==0)
                {
                     filenames.push_back("plates/" + (std::string)p1 + ".csv");
                }
            }

        }
        closedir(d);
    } else
        throw "you probably forgot to create the 'plates' folder";
    return filenames;

}
int main(){
    /* initalize all source plates from the 'plates' directory */
    std::vector<Plate> plates;
    std::vector<std::string> filenames = getsourcefiles();
    for (std::string fname : filenames){
        std::cout << "Loading plate: " << fname << "..." << std::endl;
        plates.push_back(utils::read_plate_csv(fname));
    }
    std::cout << "Please put the transfer sheet you would like to complete in the same folder as this app" << std::endl;
    /* get name of transfer sheet input */
    std::cout << "Type in the name of the transfer sheet, and then press enter" << std::endl;
    std::string transfersheetin;
    getline(std::cin, transfersheetin);
    if (transfersheetin.find('.') == std::string::npos)
        transfersheetin += ".csv";
    std::cout << "Would you like to modify the source plate volumes accordingly? please type \"yes\" or \"no\". if you enter nothing, the source plate volumes will be changed. " << std::endl;
    /* Generate sheet and alert user of new fname */

    std::string yn;
    getline(std::cin, yn);
    std::cout << "Generating transfer sheet for: " << transfersheetin << std::endl;
    std::string finalsheet = utils::create_transfer_sheet(transfersheetin, plates, (yn != "no"));
    std::cout << "Final transfer sheet generated! Plate volumes were" << ((yn != "no") ? "" : "not") << " mutated!" << std::endl;
    std::cout << "you can find your completed transfer sheet in the file named final_" << transfersheetin << std::endl;
    std::cout << "Thanks for using this script! Have a great day :)" << std::endl;
}
