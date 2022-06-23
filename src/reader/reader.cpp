#include "reader.h"

#include <filesystem>
#include <fstream>

#include "utf8proc.h"

namespace quirk {

Reader::Reader(std::string filename)
{
    read_text(filename);
    pos = text.get();
    iterate();
}

void Reader::move()
{
    switch (letter) {
    case '\0':
        return;
    case '\n':
        line++;
        column = 1;
        break;
    case '\t':
        column = ((column - 1) / tab_size + 1) * tab_size + 1; // idiv
        break;
    default:
        column++;
        break;
    }
    iterate();
}

std::string_view Reader::slice(size_t begin)
{
    auto end = get_index();
    if (begin < end) {
        auto c_str = reinterpret_cast<char*>(text.get());
        return std::string_view(c_str + begin, end - begin);
    }
    return std::string_view();
}

void Reader::read_text(std::string filename)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    auto utf8_c_str = reinterpret_cast<const char8_t*>(filename.c_str());
    file.open(std::filesystem::path(utf8_c_str), std::ios::binary | std::ios::in);

    auto begin = file.tellg();
    file.seekg(0, std::ios::end);
    auto end = file.tellg();
    file.seekg(0);

    if (end - begin >= 3) {
        uint8_t bytes[3];
        file.read(reinterpret_cast<char*>(bytes), 3);
        if (bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF) { // byte order mark
            begin = file.tellg();
        } else {
            file.seekg(0);
        }
    }

    auto size = end - begin;
    // using reset instead of make_unique to avoid default initialization
    text.reset(new uint8_t[size + 2]);
    if (size > 0) {
        file.read(reinterpret_cast<char*>(text.get()), size);
    }
    text[size] = '\n'; // force Dedent(s) before EndMarker
    text[size + 1] = '\0';
}

int32_t Reader::iterate()
{
    auto prev = letter;

    auto bytes_read = utf8proc_iterate(pos, -1, &letter);
    if (bytes_read < 0) {
        throw std::runtime_error(utf8proc_errmsg(bytes_read));
    }

    prev_pos = pos;
    pos += bytes_read;

    return prev;
}

} // namespace quirk