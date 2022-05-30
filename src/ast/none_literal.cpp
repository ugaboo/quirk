#include "visitor.h"

namespace quirk::ast {

void NoneLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast