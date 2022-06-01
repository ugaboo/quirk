#include "scopes_printer.h"

namespace quirk::util {

ScopesPrinter::ScopesPrinter(std::ostream& out, scopes::Scope& global_scope) : out(out) {}

void ScopesPrinter::visit(scopes::BasicType* decl) {}

void ScopesPrinter::visit(scopes::Field* decl) {}

void ScopesPrinter::visit(scopes::Function* decl) {}

void ScopesPrinter::visit(scopes::Module* decl) {}

void ScopesPrinter::visit(scopes::Parameter* decl) {}

void ScopesPrinter::visit(scopes::Structure* decl) {}

void ScopesPrinter::visit(scopes::Variable* decl) {}

} // namespace quirk::util

// void AstPrinter::visit(Variable* node)
// {
//     if (node->is_global()) {
//         print(out, "Global ");
//     }
//     print(out, "Variable {}", node->get_id());
// }

// void AstPrinter::visit(Parameter* node)
// {
//     print(out, "Parameter {}", node->get_id());
// }

// void AstPrinter::visit(Function* node)
// {
//     print(out, "Function {}", node->get_id());
// }

// void AstPrinter::visit(Structure* node)
// {
//     print(out, "Structure {}", node->get_id());
// }

// void AstPrinter::visit(Field* node)
// {
//     print(out, "Field {}", node->get_id());
// }

// void AstPrinter::visit(Int64Type*)
// {
//     print(out, "Int64Type");
// }

// void AstPrinter::visit(Float64Type*)
// {
//     print(out, "Float64Type");
// }
