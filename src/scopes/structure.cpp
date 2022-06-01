#include "visitor.h"

namespace quirk::scopes {

void Structure::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::scopes