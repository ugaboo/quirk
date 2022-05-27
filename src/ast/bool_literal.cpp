#include "visitor.h"

namespace quirk::ast {

void BoolLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast