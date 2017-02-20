//
// Created by liu on 17-2-1.
//

#include <dirent.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "md5.h"

using namespace std;

void rec(string dir_name, int depth = 0)
{
    auto dir = opendir(dir_name.c_str());
    dirent *file;
    while ((file = readdir(dir)) != NULL)
    {
        switch (file->d_type)
        {
        case DT_REG: // Regular file
        {

        }
        case DT_DIR: // Directory
        {

        }
        }
    }
    closedir(dir);
    delete (file);
    return;
}

int main()
{
    string root_dir;
    cout << "Please input the root dir:";
    getline(cin, root_dir);
    cout << root_dir << endl;
    rec(root_dir);
    return 0;
}

