#include "../src/parser/parser.h"
#include "fmt/core.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace quirk;

auto empty()
{
    Parser parser(TEST_DIR "/parser/empty.qk");

    vector<unique_ptr<Stmt>> stmts;
    return parser.parse(stmts) && stmts.size() == 0;
}

auto all_rules()
{
    Parser parser(TEST_DIR "parser/ast.qk");

    vector<unique_ptr<Stmt>> stmts;
    if (!parser.parse(stmts)) {
        return false;
    }

    stringstream output;
    util::AstPrinter printer(output, stmts);

    ifstream file(TEST_DIR "parser/ast.txt");

    return diff(file, output);
}

auto test_error(string filename, CompilationError expected)
{
    Parser parser(filename);

    vector<unique_ptr<Stmt>> stmts;
    try {
        parser.parse(stmts);
    } catch (CompilationError err) {
        if (err == expected) {
            return true;
        }
    }
    return false;
}

int main()
{
    // auto syntax_error = test_error(TEST_DIR "parser/syntax_error.qk",
    // CompilationError::InvalidSyntax); auto asg_to_call_error =
    //     test_error(TEST_DIR "parser/asg_to_call_error.qk",
    //     CompilationError::CantAssignToFunctionCall);
    // auto annotation_error =
    //     test_error(TEST_DIR "parser/annotation_error.qk",
    //     CompilationError::IllegalTargetForAnnotation);

    // return (empty() && all_rules() && syntax_error && asg_to_call_error && annotation_error) ? 0
    // : 1;

    return (empty() && all_rules()) ? 0 : 1;
}