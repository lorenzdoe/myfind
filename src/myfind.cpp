/*
    Filename: myfind.cpp

    Description: searches for passed filename in directory and subdirectories
    Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenameN]
    Author: Bartosik, Döllinger

*/
#include <unistd.h>      /* Included for getopt */
#include <iostream>
#include <filesystem>   /* Included for directory iterator functions */
#include <exception>

#include "myfind.h"

namespace myfind
{
    using std::filesystem::recursive_directory_iterator;
    using std::filesystem::directory_iterator;
    using std::string;
    using std::cout;
    using std::endl;
    using std::cerr;
}

using namespace myfind;

void print_usage(const string& program_name)
{
    cout << "Usage: " << program_name << " [-R] [-i] searchpath filename1 [filename2] ...[filenameN]\n" << endl;
}

void parseOptions(int &argc, char *argv[], int &optcount, bool &recursive_mode, bool &case_sensitive)
{
    /*
    *  Parse options
    */
    int c;
    while ((c = getopt(argc, argv, ":Ri")) != EOF)
    {
        switch(c)
        {
            case '?':
                throw std::invalid_argument("error: unknown option");
                break;

            case 'R':
                recursive_mode = true;
                optcount++;
                break;

            case 'i':
                case_sensitive = true;
                optcount++;
                break;

            default: // should never happen
                throw std::exception();
        }
    }

}

bool find(const string &searchpath, const string &searchfile, bool recursive, bool case_sensitive)
{
    bool found = false;

    if(recursive)
    {
        for(const auto& dirEntry: recursive_directory_iterator(searchpath))
        {
            if(compare(dirEntry.path().filename(), searchfile, case_sensitive))
            {
                found = true;
                cout << (int)getpid() << ": \"" << searchfile << "\": " << dirEntry.path() << endl;
            }
        }
    }

    else
    {
        for(const auto& dirEntry: directory_iterator(searchpath))
        {
            if(compare(dirEntry.path().filename(), searchfile, case_sensitive))
            {
                found = true;
                cout << (int)getpid() << ": \"" << searchfile << "\": " << dirEntry.path() << endl;
            }
        }
    }

    return found;
}

bool compare(const string& a, const string& b, bool cs)
{
    if (cs) {
        return a == b;
    }
    else
    {
        return std::equal(a.begin(), a.end(),
                          b.begin(), b.end(),
                          [](char a, char b) {
                              return tolower(a) == tolower(b);
                          });
    }
}