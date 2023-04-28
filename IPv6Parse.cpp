#include "include/IPv6Parse.h"

std::vector<std::string> Split(const std::string& s, char seperator)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;
    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring(s.substr(prev_pos, pos-prev_pos));
        output.push_back(substring);
        prev_pos = ++pos;
    }
    output.push_back(s.substr(prev_pos, pos-prev_pos));
    return output;
}

//::1
//1::

std::string Parse(const std::string& IPv6String)
{
    std::vector<std::string> r = Split(IPv6String, ':');
    std::string parsedValue;
    for(decltype(r.begin()) iter = r.begin(); iter != r.end(); ++iter) 
    {
        if(iter->size() == 0)
        {
            parsedValue.append(iter == r.begin() || iter == r.end() - 1 ? 4 : (8 - r.size() + 1) * 4, '0');
        }
        else if(iter->size() < 4)
        {
            parsedValue.append(4 - iter->size(), '0');
            parsedValue.append(*iter);
        }
        else
            parsedValue.append(*iter);
    }
    return parsedValue;
}