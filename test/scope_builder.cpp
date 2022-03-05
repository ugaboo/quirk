#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "fmt/core.h"
#include "parser.h"

#include "visitors/ast_printer.h"
#include "visitors/scope_builder.h"

using namespace std;
using namespace quirk;

bool test() {
    string folder = string(TEST_DIR) + "scope_builder/";
    vector<string> names = {"ops", "funcs", "structs"};

    for (auto name : names) {
        Parser parser(folder + name + ".qk");
        unique_ptr<ast::Module> m;
        if (!parser.parse(m)) {
            return 1;
        }

        ScopeBuilder builder;
        builder.visit(m.get());

        // ofstream fout(folder + name + ".txt", ios_base::binary | ios_base::out);
        // AstPrinter printer(fout);
        // printer.visit(m.get());

        stringstream sout;
        AstPrinter printer(sout);
        printer.visit(m.get());

        ifstream fin(folder + name + ".txt");

        string expected, received;
        while (getline(fin, expected) && getline(sout, received)) {
            if (expected != received) {
                fmt::print("expected: {}\n", expected);
                fmt::print("received: {}\n", received);
                return false;
            }
        }
    }
    return true;
}

bool test_errors() {
    string folder = string(TEST_DIR) + "scope_builder/";
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