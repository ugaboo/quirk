#include "visitor.h"

namespace quirk::scopes {

void Module::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes