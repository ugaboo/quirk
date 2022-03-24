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

void AstPrinter::visit(ast::NameLiteral* item) {
    print_indent();
    print(out, "NameLiteral: '{}'", item->get_value());
    if (item->get_decl() != nullptr) {
        print(out, " -> ");
        item->get_decl()->accept(this);
    }
    print(out, "\n");
}

void AstPrinter::visit(ast::IntLiteral* item) {
    print_indent();
    print(out, "IntLiteral: {}\n", item->get_value());
}

void AstPrinter::visit(ast::FloatLiteral* item) {
    print_indent();
    print(out, "FloatLiteral: {}\n", item->get_value());
}

void AstPrinter::visit(ast::BoolLiteral* item) {
    print_indent();
    print(out, "BoolLiteral: {}\n", item->get_value());
}

void AstPrinter::visit(ast::NoneLiteral*) {
    print_indent();
    print(out, "NoneLiteral\n");
}

void AstPrinter::visit(ast::ListLiteral* item) {
    print_indent();
    print(out, "ListLiteral:");
    if (item->count_exprs() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_exprs(); i++) {
            item->get_expr(i)->accept(this);
        }
        indent--;
    } else {
        print(out, " <empty>\n");
    }
}

void AstPrinter::visit(ast::AsgStmt* item) {
    print_indent();
    print(out, "AsgStmt:\n");
    indent++;
    print_indent();
    print(out, "lvalue:\n");
    indent++;
    item->get_lvalue()->accept(this);
    indent--;
    if (item->get_type_expr() != nullptr) {
        print_indent();
        print(out, "type:\n");
        indent++;
        item->get_type_expr()->accept(this);
        indent--;
    }
    if (item->get_rvalue() != nullptr) {
        print_indent();
        print(out, "rvalue:\n");
        indent++;
        item->get_rvalue()->accept(this);
        indent--;
    }
    indent--;
}

void AstPrinter::visit(ast::CallExprStmt* item) {
    print_indent();
    print(out, "CallExprStmt:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    item->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "args:");
    if (item->count_args() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_args(); i++) {
            item->get_arg(i)->accept(this);
        }
        indent--;
    } else {
        print(out, " <empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::SubscriptExpr* item) {
    print_indent();
    print(out, "SubscriptExpr:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    item->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "keys:\n");
    indent++;
    for (size_t i = 0; i < item->count_keys(); i++) {
        item->get_key(i)->accept(this);
    }
    indent--;
    indent--;
}

void AstPrinter::visit(ast::MemberAccessExpr* item) {
    print_indent();
    print(out, "MemberAccessExpr:\n");
    indent++;
    print_indent();
    print(out, "designator:\n");
    indent++;
    item->get_designator()->accept(this);
    indent--;
    print_indent();
    print(out, "selector:\n");
    indent++;
    item->get_selector()->accept(this);
    indent--;
    indent--;
}

void AstPrinter::visit(ast::Module* item) {
    for (size_t i = 0; i < item->count_stmts(); i++) {
        item->get_stmt(i)->accept(this);
    }
}

void AstPrinter::visit(ast::BinaryExpr* item) {
    print_indent();
    print(out, "BinaryExpr: {}\n", magic_enum::enum_name(item->get_kind()));
    indent++;
    item->get_left()->accept(this);
    item->get_right()->accept(this);
    indent--;
}

void AstPrinter::visit(ast::UnaryExpr* item) {
    print_indent();
    print(out, "UnaryExpr: {}\n", magic_enum::enum_name(item->get_kind()));
    indent++;
    item->get_expr()->accept(this);
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

void AstPrinter::visit(ast::ReturnStmt* item) {
    print_indent();
    print(out, "ReturnStmt\n");
    indent++;
    item->get_expr()->accept(this);
    indent--;
}

void AstPrinter::visit(ast::ParameterDef* item) {
    print_indent();
    print(out, "ParameterDef: '{}'", item->get_name());
    if (item->get_decl() != nullptr) {
        print(out, " -> ");
        item->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    print_indent();
    print(out, "type:\n");
    indent++;
    item->get_type()->accept(this);
    indent--;
    indent--;
}

void AstPrinter::visit(ast::IfStmt* item) {
    print_indent();
    print(out, "IfStmt:\n");
    indent++;
    for (size_t i = 0; i < item->count_branches(); i++) {
        print_indent();
        print(out, "condition:\n");
        indent++;
        item->get_condition(i)->accept(this);
        indent--;
        print_indent();
        print(out, "body: ");
        if (item->count_branch_stmts(i) > 0) {
            print(out, "\n");
            indent++;
            for (size_t j = 0; j < item->count_branch_stmts(i); j++) {
                item->get_branch_stmt(i, j)->accept(this);
            }
            indent--;
        } else {
            print(out, "<empty>\n");
        }
    }
    print_indent();
    print(out, "else: ");
    if (item->count_else_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_else_stmts(); i++) {
            item->get_else_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::WhileStmt* item) {
    print_indent();
    print(out, "WhileStmt:\n");
    indent++;
    print_indent();
    print(out, "condition:\n");
    indent++;
    item->get_condition()->accept(this);
    indent--;
    print_indent();
    print(out, "body: ");
    if (item->count_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_stmts(); i++) {
            item->get_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::FuncDefStmt* item) {
    print_indent();
    print(out, "FuncDefStmt: '{}'", item->get_name());
    if (item->get_decl() != nullptr) {
        print(out, " -> ");
        item->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    if (item->count_params() > 0) {
        print_indent();
        print(out, "params:\n");
        indent++;
        for (size_t i = 0; i < item->count_params(); i++) {
            item->get_param(i)->accept(this);
        }
        indent--;
    }
    if (item->get_ret_type_expr() != nullptr) {
        print_indent();
        print(out, "ret:\n");
        indent++;
        item->get_ret_type_expr()->accept(this);
        indent--;
    }
    print_indent();
    print(out, "body: ");
    if (item->count_stmts() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_stmts(); i++) {
            item->get_stmt(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::FieldDef* item) {
    print_indent();
    print(out, "FieldDef: '{}'", item->get_name());
    if (item->get_decl() != nullptr) {
        print(out, " -> ");
        item->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    if (item->get_type() != nullptr) {
        print_indent();
        print(out, "type:\n");
        indent++;
        item->get_type()->accept(this);
        indent--;
    }
    if (item->get_init_expr() != nullptr) {
        print_indent();
        print(out, "init:\n");
        indent++;
        item->get_init_expr()->accept(this);
        indent--;
    }
    indent--;
}

void AstPrinter::visit(ast::StructDefStmt* item) {
    print_indent();
    print(out, "StructDefStmt: '{}'", item->get_name());
    if (item->get_decl() != nullptr) {
        print(out, " -> ");
        item->get_decl()->accept(this);
    }
    print(out, "\n");
    indent++;
    print_indent();
    print(out, "fields: ");
    if (item->count_fields() > 0) {
        print(out, "\n");
        indent++;
        for (size_t i = 0; i < item->count_fields(); i++) {
            item->get_field(i)->accept(this);
        }
        indent--;
    } else {
        print(out, "<empty>\n");
    }
    indent--;
}

void AstPrinter::visit(ast::Variable* item) {
    if (item->is_global()) {
        print(out, "Global ");
    }
    print(out, "Variable {}", item->get_id());
}

void AstPrinter::visit(ast::Parameter* item) {
    print(out, "Parameter {}", item->get_id());
}

void AstPrinter::visit(ast::Function* item) {
    print(out, "Function {}", item->get_id());
}

void AstPrinter::visit(ast::Structure* item) {
    print(out, "Structure {}", item->get_id());
}

void AstPrinter::visit(ast::Field* item) {
    print(out, "Field {}", item->get_id());
}

void AstPrinter::visit(ast::Int64Type*) {
    print(out, "Int64Type");
}

void AstPrinter::visit(ast::Float64Type*) {
    print(out, "Float64Type");
}

}  // namespace quirk