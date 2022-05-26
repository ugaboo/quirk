#pragma once

#include <string>

namespace quirk::scopes {

using namespace std;

class Declaration {
public:
    virtual ~Declaration() {}

    virtual string_view get_name() = 0;
};

} // namespace quirk::scopes