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

    virtual void visit(BasicType* decl) = 0;
    virtual void visit(Field* decl) = 0;
    virtual void visit(Function* decl) = 0;
    virtual void visit(Module* decl) = 0;
    virtual void visit(Parameter* decl) = 0;
    virtual void visit(Structure* decl) = 0;
    virtual void visit(Variable* decl) = 0;
};

} // namespace quirk::scopes