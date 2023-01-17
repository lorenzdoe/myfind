/*
 * Created by lorenz on 01.10.22.
 * print out passed arguments
 */

#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[]){

    std::cout << "number of arguments passed: " << argc << std::endl;

    for(; optind < argc; optind++){
        std::cout << "Argument " << optind << ": " << argv[optind] << std::endl;
    }

    return 0;
}