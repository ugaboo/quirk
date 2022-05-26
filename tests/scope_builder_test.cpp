#include "../src/parser/parser.h"
#include "../src/scopes/scope_builder.h"
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

        vector<unique_ptr<Stmt>> stmts;
        if (!parser.parse(stmts)) {
            return 1;
        }

        scopes::ScopeBuilder builder(stmts);

        stringstream output;
        util::AstPrinter printer(output, stmts);

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

        vector<unique_ptr<Stmt>> stmts;
        if (!parser.parse(stmts)) {
            return 1;
        }

        try {
            scopes::ScopeBuilder builder(stmts);
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