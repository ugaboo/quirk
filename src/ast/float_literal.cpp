#include "visitor.h"

namespace quirk::ast {

void FloatLiteral::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast