#include "visitor.h"

namespace quirk::ast {

void ListLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast