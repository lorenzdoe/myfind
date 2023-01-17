//
// Created by lorenz on 01.10.22.
// print out names of files in cwd
//

#include <dirent.h>
#include <iostream>
#include <filesystem>

using std::string;
using std::filesystem::directory_iterator;

int main(int argc, char* argv[]) {

    // one way: use filesystem library
    string cwd_path;

    cwd_path = std::filesystem::current_path();
    for (const auto &dirEntry: directory_iterator(cwd_path)) {
        std::cout << dirEntry.path().filename() << std::endl;
    }

    // another way: use dirent.h library
    std::cout << "\nanother way:\n\n";
    struct dirent *direntp;
    DIR *dirp;

    dirp = opendir(".");
    if (dirp == NULL) {
        std::cerr << "Failed to open directory" << std::endl;
        exit(EXIT_FAILURE);
    }

    while ((direntp = readdir(dirp)) != NULL){
        std::cout << direntp->d_name << std::endl;
    }

    while ((closedir(dirp) == -1) && (errno == EINTR))
        ;

    return 0;
}