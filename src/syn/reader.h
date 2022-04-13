#pragma once
#include <memory>
#include <string>
#include <tuple>

namespace quirk {

using std::string;
using std::string_view;

class Reader {
    inline static int tab = 4;  // tab size

    std::unique_ptr<uint8_t[]> text;  // utf-8 encoded text, C-style string to use with the utf8proc library
    uint8_t* pos;
    uint8_t* prev_pos;

    int32_t letter;

    size_t line = 1;
    size_t column = 1;

public:
    Reader(string filename);

    void move();

    char32_t get_letter() { return letter; }
    auto get_line() { return line; }
    auto get_column() { return column; }
    size_t get_index() { return prev_pos - text.get(); }

    string_view slice(size_t begin);

private:
    void read_text(string filename);
    int32_t iterate();
};

}  // namespace quirk