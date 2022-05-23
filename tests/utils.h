#pragma once
#include <fstream>
#include <string>
#include "fmt/core.h"
#include "../src/util/ast_printer.h"

using namespace std;
using namespace quirk;

void dump(string filename, vector<ast::StmtPtr>& stmts) {
    ofstream out(filename, ios_base::binary | ios_base::out);
    util::AstPrinter printer(out, stmts);
}

template <class T, class V>
bool diff(T& expected, V& received) {
    std::string expected_str, received_str;
    int line = 1;
    while (std::getline(expected, expected_str) && std::getline(received, received_str)) {
        if (expected_str != received_str) {
            fmt::print("line {}\n", line);
            fmt::print("expected: {}\n", expected_str);
            fmt::print("received: {}\n", received_str);
            return false;
        }
        line++;
    }
    return true;
}