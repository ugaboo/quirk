#pragma once

#include "prog_obj.h"

namespace quirk::scopes {

class Field : public ProgObj {
public:
    Field() {}

    void accept(Visitor* visitor) override;
};

} // namespace quirk::scopes