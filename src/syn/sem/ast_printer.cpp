#include "ast_printer.h"
#include "fmt/ostream.h"
#include "magic_enum.hpp"

namespace quirk {

using fmt::print;
using std::make_unique;

void AstPrinter::print_indent() {
    for (auto i = 0; i < indent; i++) {
        print(out, "    ");
    }
}

void AstPrinter::visit(ast::NameLiteral* node) {
    print_indent();
    print(out, "NameLiteral: '{}'", node->get_value());
    if (node->get_decl() != nullptr) {
        print(out, " -> ");
        node->get_decl()->accept(this);
    }
    print(out, "\n");
}

void AstPrinter::visit(ast::IntLiteral* node) {
    print_indent();
    print(out, "IntLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(ast::FloatLiteral* node) {
    print_indent();
    print(out, "FloatLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(ast::BoolLiteral* node) {
    print_indent();
    print(out, "BoolLiteral: {}\n", node->get_value());
}

void AstPrinter::visit(ast::NoneLiteral*) {
    print_indent();
    print(out, "NoneLiteral\n");
}

void AstPrinter::visit(ast::ListLiteral* node) {
    print_indent();
    print(out, "ListLiteral:");
    if (node->count_exprs() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_exprs(); i++) {
            node->get_expr(i)->accept(this);
        }
        indent--;
    } else {
        print(out, " <empty>\n");
    }
}

void AstPrinter::visit(ast::AsgStmt* node) {
    print_indent();
    print(out, "AsgStmt:\n");
    indent++;
    print_indent();
    print(out, "lvalue:\n");
    indent++;
    node->get_lvalue()->accept(this);
    indent--;
    if (node->get_type_expr() != nullptr) {
        print_indent();
        print(out, "type:\n");
        indent++;
        node->get_type_expr()->accept(this);
        indent--;
    }
    if (node->get_rvalue() != nullptr) {
        print_indent();
        print(out, "rvalue:\n");
        indent++;
        node->get_rvalue()->accept(this);
        indent--;
    }
    indent--;
}

void AstPrinter::visit(ast::CallExprStmt* node) {
    print_indent();
    print(out, "CallExprStmt:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    node->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "args:");
    if (node->count_args() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_args(); i++) {
            node->get_arg(i)->accept(this);
        }
        indent--;
    } else {
        print(out, " <empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::SubscriptExpr* node) {
    print_indent();
    print(out, "SubscriptExpr:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    node->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "keys:\n");
    indent++;
    for (size_t i = 0; i < node->count_keys(); i++) {
        node->get_key(i)->accept(this);
    }
    indent--;
    indent--;
}

void AstPrinter::visit(ast::MemberAccessExpr* node) {
    print_indent();
    print(out, "MemberAccessExpr:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    node->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "selector:\n");
    indent++;
    node->get_selector()->accept(this);
    indent--;
    indent--;
}

void AstPrinter::visit(ast::Module* node) {
    for (size_t i = 0; i < node->count_stmts(); i++) {
        node->get_stmt(i)->accept(this);
    }
}

void AstPrinter::visit(ast::BinaryExpr* node) {
    print_indent();
    print(out, "BinaryExpr: {}\n", magic_enum::enum_name(node->get_kind()));
    indent++;
    node->get_left()->accept(this);
    node->get_right()->accept(this);
    indent--;
}

void AstPrinter::visit(ast::UnaryExpr* node) {
    print_indent();
    print(out, "UnaryExpr: {}\n", magic_enum::enum_name(node->get_kind()));
    indent++;
    node->get_expr()->accept(this);
    indent--;
}

void AstPrinter::visit(ast::BreakStmt*) {
    print_indent();
    print(out, "BreakStmt\n");
}

void AstPrinter::visit(ast::ContinueStmt*) {
    print_indent();
    print(out, "ContinueStmt\n");
}

void AstPrinter::visit(ast::ReturnStmt* node) {
    print_indent();
    print(out, "ReturnStmt\n");
    indent++;
    node->get_expr()->accept(this);
    indent--;
}

void AstPrinter::visit(ast::ParameterDef* node) {
    print_indent();
    print(out, "ParameterDef: '{}'", node->get_name());
    if (node->get_decl() != nullptr) {
        print(out, " -> ");
        node->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    print_indent();
    print(out, "type:\n");
    indent++;
    node->get_type()->accept(this);
    indent--;
    indent--;
}

void AstPrinter::visit(ast::IfStmt* node) {
    print_indent();
    print(out, "IfStmt:\n");
    indent++;
    for (size_t i = 0; i < node->count_branches(); i++) {
        print_indent();
        print(out, "condition:\n");
        indent++;
        node->get_condition(i)->accept(this);
        indent--;
        print_indent();
        print(out, "body: ");
        if (node->count_branch_stmts(i) > 0) {
            print(out, "\n");
            indent++;
            for (size_t j = 0; j < node->count_branch_stmts(i); j++) {
                node->get_branch_stmt(i, j)->accept(this);
            }
            indent--;
        } else {
            print(out, "<empty>\n");
        }
    }
    print_indent();
    print(out, "else: ");
    if (node->count_else_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_else_stmts(); i++) {
            node->get_else_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::WhileStmt* node) {
    print_indent();
    print(out, "WhileStmt:\n");
    indent++;
    print_indent();
    print(out, "condition:\n");
    indent++;
    node->get_condition()->accept(this);
    indent--;
    print_indent();
    print(out, "body: ");
    if (node->count_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_stmts(); i++) {
            node->get_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::FuncDefStmt* node) {
    print_indent();
    print(out, "FuncDefStmt: '{}'", node->get_name());
    if (node->get_decl() != nullptr) {
        print(out, " -> ");
        node->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    if (node->count_params() > 0) {
        print_indent();
        print(out, "params:\n");
        indent++;
        for (size_t i = 0; i < node->count_params(); i++) {
            node->get_param(i)->accept(this);
        }
        indent--;
    }
    if (node->get_ret_type_expr() != nullptr) {
        print_indent();
        print(out, "ret:\n");
        indent++;
        node->get_ret_type_expr()->accept(this);
        indent--;
    }
    print_indent();
    print(out, "body: ");
    if (node->count_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_stmts(); i++) {
            node->get_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::FieldDef* node) {
    print_indent();
    print(out, "FieldDef: '{}'", node->get_name());
    if (node->get_decl() != nullptr) {
        print(out, " -> ");
        node->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    if (node->get_type() != nullptr) {
        print_indent();
        print(out, "type:\n");
        indent++;
        node->get_type()->accept(this);
        indent--;
    }
    if (node->get_init_expr() != nullptr) {
        print_indent();
        print(out, "init:\n");
        indent++;
        node->get_init_expr()->accept(this);
        indent--;
    }
    indent--;
}

void AstPrinter::visit(ast::StructDefStmt* node) {
    print_indent();
    print(out, "StructDefStmt: '{}'", node->get_name());
    if (node->get_decl() != nullptr) {
        print(out, " -> ");
        node->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    print_indent();
    print(out, "fields: ");
    if (node->count_fields() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < node->count_fields(); i++) {
            node->get_field(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::Variable* node) {
    if (node->is_global()) {
        print(out, "Global ");
    }
    print(out, "Variable {}", node->get_id());
}

void AstPrinter::visit(ast::Parameter* node) {
    print(out, "Parameter {}", node->get_id());
}

void AstPrinter::visit(ast::Function* node) {
    print(out, "Function {}", node->get_id());
}

void AstPrinter::visit(ast::Structure* node) {
    print(out, "Structure {}", node->get_id());
}

void AstPrinter::visit(ast::Field* node) {
    print(out, "Field {}", node->get_id());
}

void AstPrinter::visit(ast::Int64Type*) {
    print(out, "Int64Type");
}

void AstPrinter::visit(ast::Float64Type*) {
    print(out, "Float64Type");
}

}  // namespace quirk