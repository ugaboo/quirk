#include "../src/compilation_error.h"
#include "../src/scanner/scanner.h"
#include "fmt/core.h"
#include "magic_enum.hpp"
#include "utils.h"
#include <filesystem>
#include <fstream>
#include <vector>

using namespace std;
using namespace quirk;

string format_lexeme(Scanner& scan)
{
    auto tk = magic_enum::enum_name(scan.get_token());
    auto ctx = scan.get_context();
    auto val = ctx.value;

    if (scan.get_token() == Token::NewLine) {
        val = string_view(); // make the dump prettier
    }

    auto str = fmt::format("[{}:{}] {}", ctx.line, ctx.column, tk);
    if (val != "") {
        str += fmt::format(" '{}'", val);
    }
    return str;
}

bool test()
{
    string folder = TEST_DIR "scanner/";
    vector<string> names = {
        "names",          "keywords",  "indents",  "indents2",
        "simple_lexemes", "new_lines", "integers", "floats",
    };

    for (auto name : names) {
        Scanner scan(folder + name + ".qk");

        stringstream output;
        do {
            output << format_lexeme(scan) << endl;
            scan.move();
        } while (scan.get_token() != Token::EndMarker);

        ifstream file(folder + name + ".txt");

        if (!diff(file, output)) {
            return false;
        }
    }
    return true;
}

bool tab_error()
{
    try {
        Scanner scan(TEST_DIR "scanner/tab_error.qk");
        while (scan.get_token() != Token::EndMarker) {
            scan.move();
        }
    } catch (CompilationError err) {
        if (err == CompilationError::TabError) {
            return true;
        }
    }
    fmt::print("file 'tab_error', no error emitted");
    return false;
}

bool dedent_doesnt_match()
{
    try {
        Scanner scan(TEST_DIR "scanner/dedent_doesnt_match.qk");
        while (scan.get_token() != Token::EndMarker) {
            scan.move();
        }
    } catch (CompilationError err) {
        if (err == CompilationError::DedentDoesntMatch) {
            return true;
        }
    }
    fmt::print("file 'dedent_doesnt_match', no error emitted");
    return false;
}

int main()
{
    return (test() && tab_error() && dedent_doesnt_match()) ? 0 : 1;
}