/*
    Filename: myfind.cpp

    Description: searches for passed filename in directory and subdirectories
    Usage: ./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenameN]
    Author: Bartosik, Döllinger

*/
#include <unistd.h>      /* Included for getopt */
#include <sys/wait.h>
#include <iostream>
#include <filesystem>   /* Included for directory iterator functions */
#include <exception>

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

void parseOptions(int &argc, char *argv[], int &optcount, bool &recursive_mode, bool &case_sensitive);

bool find(const string &searchpath, const string &searchfile, bool recursive, bool case_sensitive);

bool compare(const string& a, const string& b, bool cs);

int main(int argc, char* argv[])
{
    pid_t pid, wpid;
    int status;
    bool recursive_mode;
    bool case_sensitive;
    int optcount;
    string program_name;
    string searchpath;

    optcount = 0;
    recursive_mode = case_sensitive = false;
    program_name    = argv[0];

    cout << "PID: " << (int)getpid() << endl << endl;

    try
    {
        parseOptions(argc, argv, optcount, recursive_mode, case_sensitive);
        /*
         * argc = number of arguments passed + 1
         * optcount + 1 because the first argument is the searchpath
         * if no filename to search for is passed -> program terminates
         */
        if (argc == optcount + 1 || argc == optcount + 2) {
            throw std::logic_error("error: no search-path or filename passed");
        }

        /*
         * now we can start with the main process
         */
        searchpath = argv[optind];
        optind++;


        // check if passed path is an existing directory
        if (!std::filesystem::is_directory(searchpath)) {
            throw std::invalid_argument("error: \"" + searchpath + "\" is not an existing directory");
        }

        // iterate over input arguments
        while ( optind < argc)
        {
            bool found;
            string searchfile = argv[optind];
            optind++;

            // for each file fork the process
            pid = fork();

            if (pid == -1)
            {
                throw std::runtime_error("error: failed to fork process");
            }
            if (pid == 0) //child
            {
                found = find(searchpath, searchfile, recursive_mode, case_sensitive);

                if (!found) {
                    cout << "\"" << searchfile << "\" not found" << endl;
                }

                break; //after forked child finishes file-searching, it escapes the loop and terminates
            }

        }

        // only enters in parent process
        if(pid)
        {
            while ((wpid = wait(&status)) != pid)
            {
                if (wpid != -1)
                {
                    continue; /* different child process has terminated, continue waiting */
                }

                /* error waiting */
                cerr << "myfork: error when waiting for child process" << endl;
                return EXIT_FAILURE;
            }
            /* check exit code of child after finishing */
            if (WIFEXITED(status)) /* child has finished normally with exit code WEXITSTATUS(status) */
            {
                //cout <<"\nChild processes finished normally, exit code: " << WEXITSTATUS(status) << endl;
            }
            else /* child has finished with error */
            {
                cout <<"\nChild processes finished with error or via signal" << endl;
            }
        }

    }
    catch (std::logic_error& e) // also catches invalid_argument exception
    {
        cerr << e.what() << endl;
        print_usage(program_name);
        exit(EXIT_FAILURE);
    }
    catch (std::runtime_error& e)
    {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch (...)
    {
        cerr << "error: unknown error" << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

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