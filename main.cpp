#include "plate.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
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
    std::cout << getsourcefiles()[0];
    std::vector<Plate> plates;
    std::vector<std::string> filenames = getsourcefiles();
    for (std::string fname : filenames)
        plates.push_back(utils::read_plate_csv(fname));
    std::cout << plates.size();





}
