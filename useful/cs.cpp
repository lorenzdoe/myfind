#include <iostream>
#include <algorithm>

using namespace std;

bool compare(const string& a, const string& b, bool cs)
{
    if (!cs) {
        return std::equal(a.begin(), a.end(),
                          b.begin(), b.end(),
                          [](char a, char b) {
                              return tolower(a) == tolower(b);
                          });
    }
    else
    {
        return a == b;
    }
}

int main()
{
    string a = "hello!";
    string b = "hello!";

    if(compare(a,b, true))
    {
        cout << "equals" << endl;
    }

	return 0;
}
