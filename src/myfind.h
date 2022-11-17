#ifndef MYFIND_MYFIND_H
#define MYFIND_MYFIND_H

#include <unistd.h>      /* Included for getopt */
#include <sys/wait.h>
#include <iostream>
#include <filesystem>   /* Included for directory iterator functions */
#include <exception>

namespace myfind
{
    using std::string;
}

using namespace myfind;

void print_usage(const string& program_name);

void parseOptions(int &argc, char *argv[], int &optcount, bool &recursive_mode, bool &case_sensitive);

bool find(const string &searchpath, const string &searchfile, bool recursive, bool case_sensitive);

bool compare(const string& a, const string& b, bool cs);


#endif //MYFIND_MYFIND_H
