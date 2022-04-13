#include "syn/sem/scope_builder.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "fmt/core.h"
#include "syn/parser.h"
#include "syn/sem/ast_printer.h"
#include "utils.h"

using namespace std;
using namespace quirk;

bool test() {
    string folder = TEST_DIR "scope_builder/";
    vector<string> names = {"ops", "funcs", "structs"};

    for (auto name : names) {
        Parser parser(folder + name + ".qk");
        unique_ptr<ast::Module> m;
        if (!parser.parse(m)) {
            return 1;
        }

        ScopeBuilder builder;
        builder.visit(m.get());

        stringstream output;
        AstPrinter printer(output);
        printer.visit(m.get());

        ifstream file(folder + name + ".txt");

        if (!diff(file, output)) {
            return false;
        }
    }
    return true;
}

bool test_errors() {
    string folder = TEST_DIR "scope_builder/";
    vector<string> names = {"error1", "error2"};

    for (auto name : names) {
        Parser parser(folder + name + ".qk");
        unique_ptr<ast::Module> m;
        if (!parser.parse(m)) {
            return 1;
        }

        try {
            ScopeBuilder builder;
            builder.visit(m.get());
        } catch (CompilationError exc) {
            if (exc == CompilationError::ItemNotFound) {
                continue;
            }
        }
    }
    return true;
}

int main() {
    return test() && test_errors() ? 0 : 1;
}