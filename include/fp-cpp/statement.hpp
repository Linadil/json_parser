#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <map>
#include <cstdarg>

namespace alionapermes {

using namespace std;


template<typename match_case, typename return_value>
return_value
match(
    match_case target,
    return_value default_result,
    map<match_case, return_value> patterns
) {
    for (const auto& [value, result] : patterns) {
        if (value == target) {
            return result;
        }
    }

    return default_result;
}


}

#endif
