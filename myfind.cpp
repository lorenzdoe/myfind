/*
    Filename: myfind.cpp

    Description: searches for passed filename in directory and subdirectories
    Author: Lorenz Döllinger

*/
#include <unistd.h>      /* Included for getopt */
#include <iostream>
#include <filesystem>   /* Included for directory iterator functions */

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

void print_usage(const string& program_name);

bool find(const string &searchpath, const string &searchfile, bool recursive);

int main(int argc, char* argv[])
{
    int c;
    bool recursive_mode;
    bool case_sensitive;
    unsigned short optcount;
    string program_name;
    string cwd_path;
    string searchpath;

    optcount = 0;
    recursive_mode = case_sensitive = false;
    program_name    = argv[0];
    cwd_path        = std::filesystem::current_path();

    /*
     *  Parse options
     */
    while ((c = getopt(argc, argv, ":Ri")) != EOF)
    {
        switch(c)
        {
            case '?':
                cerr << program_name << " error: Unknown option." << endl;
                print_usage(program_name);
                exit(EXIT_FAILURE);
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
                cerr << "Unknown error" << endl;
                exit(EXIT_FAILURE);
        }
    }

    /*
     * argc = number of arguments passed + 1
     * optcount + 1 because the first argument is the searchpath
     * if no filename to search for is passed -> program terminates
     */
    if( argc == optcount + 1 || argc == optcount + 2 )
    {
        cerr << "error: no searchpath or filename passed" << endl;
        print_usage(program_name);
        exit(EXIT_FAILURE);
    }

    if(recursive_mode) cout << "recoursive\n";
    if(case_sensitive) cout << "case sensitive\n";

    /*
     * now we can start with the main process
     */
    searchpath = argv[optind];
    optind++;

    // iterate over input arguments
    for(; optind < argc ; optind++)
    {
        bool found;
        string searchfile = argv[optind];
        try
        {
            found = find(searchpath,searchfile,recursive_mode);
        }

        // this exception is thrown when an invalid path is passed
        catch (std::filesystem::__cxx11::filesystem_error& e)
        {
            cerr << e.what() << endl;
            exit(EXIT_FAILURE);
        }
        catch (...)
        {
            cerr << "unknown error" << endl;
            exit(EXIT_FAILURE);
        }

        if( ! found )
        {
            cout << "file: " << searchfile << " not found" << endl;
        }
    }

    return 0;
}

void print_usage(const string& program_name)
{
    cout << "Usage: " << program_name << " [-R] [-i] searchpath filename1 [filename2] ...[filenameN]\n" << endl;
}

bool find(const string &searchpath, const string &searchfile, bool recursive)
{
    bool found = false;

    if(recursive)
    {
        for(const auto& dirEntry: recursive_directory_iterator(searchpath))
        {
            if(dirEntry.path().filename() == searchfile)
            {
                found = true;
                cout << "found: " << dirEntry.path() << endl;
            }
        }
    }

    else
    {
        for(const auto& dirEntry: directory_iterator(searchpath))
        {
            if(dirEntry.path().filename() == searchfile)
            {
                found = true;
                cout << "found: " << dirEntry.path() << endl;
            }
        }
    }

    return found;
}