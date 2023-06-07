#include "include/IPv6Parse.h"
#include "include/utils.h"

std::string Parse(const std::string &IPv6String)
{
    std::vector<std::string> r = std::move(Split(IPv6String, ':'));
    std::string parsedValue;
    for (decltype(r.begin()) iter = r.begin(); iter != r.end(); ++iter)
    {
        if (iter->size() == 0)
            parsedValue.append(iter == r.begin() || iter == r.end() - 1 ? 4 : (8 - r.size() + 1) * 4, '0');
        else if (iter->size() < 4)
        {
            parsedValue.append(4 - iter->size(), '0');
            parsedValue.append(*iter);
        }
        else
            parsedValue.append(*iter);
    }
    return parsedValue;
}