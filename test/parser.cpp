#include "syn/parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "fmt/core.h"
#include "syn/sem/ast_printer.h"
#include "utils.h"

using namespace std;
using namespace quirk;

auto empty() {
    Parser parser(TEST_DIR "/parser/empty.qk");
    unique_ptr<ast::Module> m;
    return parser.parse(m) && m->count_stmts() == 0;
}

auto all_rules() {
    Parser parser(TEST_DIR "parser/ast.qk");
    unique_ptr<ast::Module> m;
    if (!parser.parse(m)) {
        return false;
    }

    stringstream output;
    AstPrinter printer(output);
    printer.visit(m.get());

    ifstream file(TEST_DIR "parser/ast.txt");

    return diff(file, output);
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
    // auto syntax_error = test_error(TEST_DIR "parser/syntax_error.qk", CompilationError::InvalidSyntax);
    // auto asg_to_call_error =
    //     test_error(TEST_DIR "parser/asg_to_call_error.qk", CompilationError::CantAssignToFunctionCall);
    // auto annotation_error =
    //     test_error(TEST_DIR "parser/annotation_error.qk", CompilationError::IllegalTargetForAnnotation);

    // return (empty() && all_rules() && syntax_error && asg_to_call_error && annotation_error) ? 0 : 1;

    return (empty() && all_rules()) ? 0 : 1;
}