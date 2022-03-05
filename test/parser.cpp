#include "parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "fmt/core.h"
#include "visitors/ast_printer.h"

using namespace std;
using namespace quirk;

auto empty() {
    Parser parser(string(TEST_DIR) + "/parser/empty.qk");
    unique_ptr<ast::Module> m;
    if (parser.parse(m) && m->count_stmts() == 0) {
        return true;
    }
    return false;
}

auto all_rules() {
    Parser parser(string(TEST_DIR) + "parser/ast.qk");
    unique_ptr<ast::Module> m;
    if (!parser.parse(m)) {
        return false;
    }

    // ofstream fout(string(TEST_DIR) + "/parser/ast.txt", ios_base::binary | ios_base::out);
    // AstPrinter printer(fout);
    // printer.visit(m.get());

    stringstream sout;
    AstPrinter printer(sout);
    printer.visit(m.get());

    ifstream fin(string(TEST_DIR) + "parser/ast.txt");

    string expected, received;
    while (getline(fin, expected) && getline(sout, received)) {
        if (expected != received) {
            fmt::print("expected: {}\n", expected);
            fmt::print("received: {}\n", received);
            return false;
        }
    }
    return true;
}

auto test_error(string filename, CompilationError expected) {
    Parser parser(filename);
    unique_ptr<ast::Module> m;
    try {
        parser.parse(m);
    } catch (CompilationError err) {
        if (err == expected) {
            return true;
        }
    }
    return false;
}

int main() {
    // auto syntax_error = test_error(string(TEST_DIR) + "parser/syntax_error.qk", CompilationError::InvalidSyntax);
    // auto asg_to_call_error =
    //     test_error(string(TEST_DIR) + "parser/asg_to_call_error.qk", CompilationError::CantAssignToFunctionCall);
    // auto annotation_error =
    //     test_error(string(TEST_DIR) + "parser/annotation_error.qk", CompilationError::IllegalTargetForAnnotation);

    // return (empty() && all_rules() && syntax_error && asg_to_call_error && annotation_error) ? 0 : 1;

    return (empty() && all_rules()) ? 0 : 1;
}