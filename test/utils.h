#pragma once
#include <fstream>
#include <string>
#include "fmt/core.h"
#include "visitors/ast_printer.h"

void dump(quirk::ast::Module* m, std::string filename) {
    std::ofstream out(filename, std::ios_base::binary | std::ios_base::out);
    quirk::AstPrinter printer(out);
    printer.visit(m);
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