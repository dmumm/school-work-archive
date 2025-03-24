#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char*[] argv)
{

    vector<int> input;
    for(int i = 1; i <= argc; i++)
      input.push_back(argv[i])


    return 0;
}
