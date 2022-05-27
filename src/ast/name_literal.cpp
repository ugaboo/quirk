#include "visitor.h"

namespace quirk::ast {

void NameLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast