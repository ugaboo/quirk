#pragma once

#include <memory>
#include <string>

namespace quirk {

class Reader {
    inline static int tab = 4; // tab size

    std::unique_ptr<uint8_t[]> text; // utf-8 encoded text, C-style string to use with the utf8proc

    uint8_t* pos;
    uint8_t* prev_pos;

    int32_t letter;

    size_t line = 1;
    size_t column = 1;

public:
    Reader(std::string filename);

    void move();

    char32_t get_letter() { return letter; }
    size_t get_line() { return line; }
    size_t get_column() { return column; }
    size_t get_index() { return prev_pos - text.get(); }

    std::string_view slice(size_t begin);

private:
    void read_text(std::string filename);
    int32_t iterate();
};

} // namespace quirk