#include "visitor.h"

namespace quirk::scopes {

void Variable::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes