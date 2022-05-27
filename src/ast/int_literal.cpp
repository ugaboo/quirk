#include "visitor.h"

namespace quirk::ast {

void IntLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast