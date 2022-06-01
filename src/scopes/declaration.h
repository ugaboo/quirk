#pragma once

#include <string>

namespace quirk::scopes {

class Visitor;

class Declaration {
public:
    virtual ~Declaration() {}

    virtual std::string_view get_name() = 0;

    virtual void accept(Visitor* visitor) = 0;
};

} // namespace quirk::scopes