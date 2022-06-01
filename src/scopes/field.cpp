#include "visitor.h"

namespace quirk::scopes {

void Field::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes