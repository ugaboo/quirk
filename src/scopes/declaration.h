#pragma once

#include <string>

namespace quirk::scopes {

class Declaration {
public:
    virtual ~Declaration() {}

    virtual std::string_view get_name() = 0;
};

} // namespace quirk::scopes