#include "../src/compilation_error.h"
#include "../src/parser/parser.h"
#include "../src/scopes/scope_builder.h"
#include "../src/util/operator_table.h"
#include "../src/util/scopes_printer.h"
#include "fmt/core.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace quirk;

bool test()
{
    string folder = TEST_DIR "scope_builder/";
    vector<string> names = {"ops", "funcs", "structs"};

    for (auto name : names) {
        Parser parser(folder + name + ".qk");

        unique_ptr<ast::TranslationUnit> tu;
        if (!parser.parse(tu)) {
            return 1;
        }

        scopes::Scope global_scope;
        util::OperatorTable op_table;
        op_table.fill_scope(global_scope);

        unordered_map<ast::Node*, scopes::Declaration*> bindings;
        scopes::ScopeBuilder builder(tu.get(), global_scope, bindings);
        builder.process();

        stringstream output;
        util::ScopesPrinter printer(output, global_scope);

        ifstream file(folder + name + ".txt");

        if (!diff(file, output)) {
            return false;
        }
    }
    return true;
}

bool test_errors()
{
    string folder = TEST_DIR "scope_builder/";
    vector<string> names = {"error1", "error2"};

    for (auto name : names) {
        Parser parser(folder + name + ".qk");

        unique_ptr<ast::TranslationUnit> tu;
        if (!parser.parse(tu)) {
            return 1;
        }

        try {
            scopes::Scope global_scope;
            util::OperatorTable op_table;
            op_table.fill_scope(global_scope);

            unordered_map<ast::Node*, scopes::Declaration*> bindings;
            scopes::ScopeBuilder builder(tu.get(), global_scope, bindings);
            builder.process();
        } catch (CompilationError exc) {
            if (exc == CompilationError::ItemNotFound) {
                continue;
            }
        }
    }
    return true;
}

int main()
{
    return test() && test_errors() ? 0 : 1;
}