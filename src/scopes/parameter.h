#pragma once

#include "prog_obj.h"

namespace quirk::scopes {

class Parameter : public ProgObj {
public:
    Parameter() {}

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes