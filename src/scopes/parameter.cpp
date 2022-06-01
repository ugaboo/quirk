#include "visitor.h"

namespace quirk::scopes {

void Parameter::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes