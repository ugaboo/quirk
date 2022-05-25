#pragma once

#include "../reader/reader.h"
#include "token.h"
#include <stack>

namespace quirk {

struct Context {
    size_t line;
    size_t column;
    string_view value;
};

class Scanner {
    Reader reader;

    std::stack<uint64_t> indentation;
    uint64_t indent;
    bool update_indent = true;

    Token token = Token::None;
    size_t token_index;
    size_t line;
    size_t column;

    int64_t ignore_new_line = 0;

public:
    Scanner(string filename);

    void move();

    Token get_token() { return token; }

    Context get_context()
    {
        return Context{.line = line, .column = column, .value = reader.slice(token_index)};
    }

    // auto get_line() { return line; }
    // auto get_column() { return column; }
    // auto get_value() { return reader.slice(token_index); }

private:
    bool is(char32_t letter);
    bool is_space();
    bool is_new_line();
    bool is_eof();
    bool is_digit();
    bool is_id_start();
    bool is_id_continue();
    bool is_bidi();

    void iterate();

    void count_indentation();
    bool skip_empty_line();
    void skip_comment();

    void id_or_keyword();
    void number();
    void integer();
    void real();
    void simple_token();
};

} // namespace quirk