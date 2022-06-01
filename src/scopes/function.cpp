#include "visitor.h"

namespace quirk::scopes {

void Function::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes