#include "reader.h"
#include <filesystem>
#include <fstream>
#include "settings.h"
#include "utf8proc.h"

namespace quirk {

using namespace std;

Reader::Reader(string filename) {
    read_text(filename);

    pos = text.get();
    iterate();
}

void Reader::move() {
    auto tab = Settings::tab_width;
    switch (letter) {
    case '\0':
        return;
    case '\n':
        line++;
        column = 1;
        break;
    case '\t':
        column = ((column - 1) / tab + 1) * tab + 1;  // idiv
        break;
    default:
        column++;
        break;
    }
    iterate();
}

string_view Reader::slice(size_t begin) {
    auto end = get_index();
    if (begin < end) {
        auto c_str = reinterpret_cast<char*>(text.get());
        return string_view(c_str + begin, end - begin);
    }
    return string_view();
}

void Reader::read_text(string filename) {
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);

    auto utf8_c_str = reinterpret_cast<const char8_t*>(filename.c_str());
    file.open(filesystem::path(utf8_c_str), ios::binary | ios::in);

    auto begin = file.tellg();
    file.seekg(0, ios::end);
    auto end = file.tellg();
    file.seekg(0);

    if (end - begin >= 3) {
        uint8_t bytes[3];
        file.read(reinterpret_cast<char*>(bytes), 3);
        if (bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF) {  // byte order mark
            begin = file.tellg();
        } else {
            file.seekg(0);
        }
    }

    auto size = end - begin;
    text.reset(new uint8_t[size + 2]);  // using reset instead of make_unique to avoid default initialization
    if (size > 0) {
        file.read(reinterpret_cast<char*>(text.get()), size);
    }
    text[size] = '\n';  // force Dedent(s) before EndMarker
    text[size + 1] = '\0';
}

int32_t Reader::iterate() {
    auto prev = letter;

    auto bytes_read = utf8proc_iterate(pos, -1, &letter);
    if (bytes_read < 0) {
        throw std::runtime_error(utf8proc_errmsg(bytes_read));
    }

    prev_pos = pos;
    pos += bytes_read;

    return prev;
}

}  // namespace quirk