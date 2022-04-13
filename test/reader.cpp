#include "syn/reader.h"
#include <iostream>
#include <vector>
#include "fmt/core.h"

using namespace quirk;
using std::string;
using std::vector;

bool empty() {
    Reader reader(TEST_DIR "reader/empty.qk");
    if (reader.get_letter() != '\n') {
        fmt::print("FAILED: empty file");
        return false;
    }
    reader.move();
    if (reader.get_letter() != '\0') {
        fmt::print("FAILED: empty file");
        return false;
    }
    reader.move();
    if (reader.get_letter() != '\0') {
        fmt::print("FAILED: empty file");
        return false;
    }
    return true;
}

bool bom() {
    Reader reader(TEST_DIR "reader/bom.qk");

    auto expected = U"this file contains byte order mark\n";
    for (auto ptr = expected; *ptr != '\0'; ptr++) {
        if (reader.get_letter() != *ptr) {
            fmt::print("FAILED: bom");
            return false;
        }
        reader.move();
    }
    return true;
}

bool unicode() {
    Reader reader(TEST_DIR "reader/кириллица.qk");

    auto expected = U"текст на русском языке 😎";
    for (auto ptr = expected; *ptr != '\0'; ptr++) {
        if (reader.get_letter() != *ptr) {
            fmt::print("FAILED: unicode");
            return false;
        }
        reader.move();
    }
    return true;
}

bool ln_col() {
    string folder = TEST_DIR "reader/";
    auto files = {
        "ln_col_unix",
        "ln_col_win",
        "tab",
    };
    for (auto filename : files) {
        Reader reader(folder + filename + ".qk");

        uint32_t letter;
        do {
            letter = reader.get_letter();
            if (letter >= '0' && letter <= '9') {
                if (reader.get_column() != letter - '0') {
                    fmt::print("FAILED: ln_col");
                    return false;
                }
            }
            reader.move();
        } while (letter != '\0');

        if (reader.get_line() != 7) {
            fmt::print("FAILED: ln_col");
            return false;
        }
    }

    return true;
}

bool slice() {
    Reader reader(TEST_DIR "reader/slice.qk");

    auto is_id = [&]() { return reader.get_letter() >= 'a' && reader.get_letter() <= 'z'; };

    vector<string> expected = {
        "lorem",  "ipsum", "dolor",  "sit",     "amet",   "consectetur", "adipiscing",
        "elit",   "sed",   "do",     "eiusmod", "tempor", "incididunt",  "ut",
        "labore", "et",    "dolore", "magna",   "aliqua",
    };

    for (auto str : expected) {
        auto begin = reader.get_index();
        while (is_id()) {
            reader.move();
        }
        if (reader.slice(begin) != str) {
            fmt::print("FAILED: slice");
            return false;
        }
        while (!is_id() && reader.get_letter() != '\0') {
            reader.move();
        }
    }
    return true;
}

int main() {
    return (empty() && bom() && unicode() && slice() && ln_col()) ? 0 : 1;
}
