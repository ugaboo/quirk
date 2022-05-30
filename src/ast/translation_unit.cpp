#include "visitor.h"

namespace quirk::ast {

void TranslationUnit::accept(Visitor* visitor)
{
    visitor->visit(this);
}

} // namespace quirk::ast