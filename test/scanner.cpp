#include "scanner.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include "compilation_error.h"
#include "fmt/core.h"
#include "magic_enum.hpp"

using namespace std;
using namespace quirk;

string format_lexeme(Scanner& scan) {
    auto tk = magic_enum::enum_name(scan.get_token());
    auto val = scan.get_value();

    if (scan.get_token() == Token::NewLine) {
        val = string_view();  // make the dump prettier
    }

    auto str = fmt::format("[{}:{}] {}", scan.get_line(), scan.get_column(), tk);
    if (val != "") {
        str += fmt::format(" '{}'", val);
    }
    return str;
}

void dump(Scanner& scan, string filename) {
    ofstream out(filename);

    out << format_lexeme(scan) << endl;
    while (scan.get_token() != Token::EndMarker) {
        scan.move();
        out << format_lexeme(scan) << endl;
    }
}

bool compare(Scanner& scan, string filename) {
    ifstream in(filename);
    if (!in) {
        return false;
    }
    string line;
    for (int i = 1; getline(in, line); i++) {
        if (*line.rbegin() == '\r') {
            line.erase(line.length() - 1, 1);
        }
        auto lex = format_lexeme(scan);
        if (line != lex) {
            fmt::print("file '{}'\n", filename);
            fmt::print("expected: {}\n", line);
            fmt::print("received: {}\n", lex);
            return false;
        }
        scan.move();
    }
    return true;
}

bool test() {
    string folder = string(TEST_DIR) + "scanner/";
    vector<string> names = {
        "names", "keywords", "indents", "indents2", "simple_lexemes", "new_lines", "integers", "floats",
    };

    for (auto name : names) {
        Scanner scan(folder + name + ".qk");
        // dump(scan, folder + name + ".txt");
        if (!compare(scan, folder + name + ".txt")) {
            return false;
        }
    }
    return true;
}

bool tab_error() {
    try {
        Scanner scan(string(TEST_DIR) + "scanner/tab_error.qk");
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

bool dedent_doesnt_match() {
    try {
        Scanner scan(string(TEST_DIR) + "scanner/dedent_doesnt_match.qk");
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

int main() {
    return (test() && tab_error() && dedent_doesnt_match()) ? 0 : 1;
}