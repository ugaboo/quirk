#include "visitor.h"

namespace quirk::ast {

void FuncDefStmt::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast