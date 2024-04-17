#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//void generate(string in, map<char, int> &floating, size_t index, const std::set<string>& dict, std::set<string>& result);
void generate(string in, string floating, size_t index, const std::set<string>& dict, std::set<string>& result);
size_t dashCount(const string& in);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<string> result;
    string in2 = in;
    string floating2 = floating;
    //map<char, int> floatMap;
    // for (char c : floating)
    // {
    //     floatMap[c]++;
    // }
    // std::map<char, int> open;
    
    // for (size_t size = 0; size < floating.length(); size++)
    // {
    //     char c = floating[size];
    //     open[c]++;
    // }
    generate(in2, floating2, 0, dict, result);

    return result;
}

// Define any helper functions here

size_t dashCount(const string& in)
{
    size_t count = 0;
    for(size_t i = 0; i < in.length(); i++)
    {
        if (in[i] == '-')
        {
            count += 1;
        }
    }
    return count;
}

void generate(string in, string floating, size_t index, const std::set<string>& dict, std::set<string>& result)
{
    if (in.length() == index)
    {
        if (!(dict.find(in) != dict.end())) 
        {
            return;
        }
        else
        {   
            result.insert(in);
            //cout << "inserting valid word " << in << endl;
            return;
        }       
    }

    size_t dashes = dashCount(in);

    if (in[index] != '-')
    {
        generate(in, floating, index + 1, dict, result);
        return;
    }

    for (size_t i = 0; i < floating.length(); i++)
    {
        string nextFloat = floating.substr(0,i) + floating.substr(i + 1);
        in[index] = floating[i];
        generate(in, nextFloat, index + 1, dict, result);
    }

    if (dashes > floating.length()) 
    {
        for(char c = 'a'; c <= 'z'; ++c)
        {
            in[index] = c;
            generate(in, floating, index + 1, dict, result);
        }
    }
}
    