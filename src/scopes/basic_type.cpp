#include "visitor.h"

namespace quirk::scopes {

void BasicType::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes