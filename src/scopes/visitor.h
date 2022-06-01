#pragma once

#include "basic_type.h"
#include "field.h"
#include "function.h"
#include "module.h"
#include "parameter.h"
#include "structure.h"
#include "variable.h"

namespace quirk::scopes {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void visit(BasicType* decl);
    virtual void visit(Field* decl);
    virtual void visit(Function* decl);
    virtual void visit(Module* decl);
    virtual void visit(Parameter* decl);
    virtual void visit(Structure* decl);
    virtual void visit(Variable* decl);
};

} // namespace quirk::scopes