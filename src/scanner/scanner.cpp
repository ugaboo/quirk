#include "scanner.h"
#include "../compilation_error.h"
#include <map>

namespace quirk {

using namespace std;

map<string, Token, less<>> keywords = {
    {"and", Token::KwAnd},       {"break", Token::KwBreak},   {"continue", Token::KwContinue},
    {"def", Token::KwDef},       {"elif", Token::KwElif},     {"else", Token::KwElse},
    {"False", Token::KwFalse},   {"if", Token::KwIf},         {"None", Token::KwNone},
    {"not", Token::KwNot},       {"or", Token::KwOr},         {"pass", Token::KwPass},
    {"return", Token::KwReturn}, {"struct", Token::KwStruct}, {"True", Token::KwTrue},
    {"while", Token::KwWhile},
};

Scanner::Scanner(string filename) : reader(filename)
{
    indentation.push(0);
    move();
}

void Scanner::move()
{
    do {
        iterate();
    } while (token == Token::Ignore);
}

void Scanner::iterate()
{
    if (update_indent) {
        count_indentation();
        update_indent = false;
    }

    line = reader.get_line();
    column = reader.get_column();
    token_index = reader.get_index();

    if (indent > indentation.top()) {
        indentation.push(indent);
        token = Token::Indent;
        return;
    }
    if (indent < indentation.top()) {
        indentation.pop();
        if (indent > indentation.top()) {
            throw CompilationError::DedentDoesntMatch;
        }
        token = Token::Dedent;
        return;
    }

    token = Token::None;

    if (is_space()) {
        token = Token::Ignore;
        reader.move();
    } else if (is_new_line()) {
        if (ignore_new_line > 0) {
            token = Token::Ignore;
        } else {
            token = Token::NewLine;
            update_indent = true;
        }
        reader.move();
    } else if (is_id_start()) {
        id_or_keyword();
    } else if (is_digit()) {
        number();
    } else if (is_eof()) {
        token = Token::EndMarker;
    } else {
        simple_token();
    }

    if (token == Token::None) {
        throw CompilationError::InvalidSyntax;
    }
}

bool Scanner::is(char32_t letter)
{
    return reader.get_letter() == letter;
}

bool Scanner::is_space()
{
    return is(' ') || is('\t') || is('\r');
}

bool Scanner::is_new_line()
{
    return is('\n');
}

bool Scanner::is_eof()
{
    return is('\0');
}

bool Scanner::is_digit()
{
    return reader.get_letter() >= '0' && reader.get_letter() <= '9';
}

bool Scanner::is_id_start()
{
    // ASCII for simplicity, implementing unicode identifiers will require text normalization
    // and additional efforts to prevent the homoglyph attack
    auto l = reader.get_letter();
    return l == '_' || (l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z');
}

bool Scanner::is_id_continue()
{
    return is_id_start() || is_digit();
}

bool Scanner::is_bidi()
{
    switch (reader.get_letter()) {
    case 0x202A: // Left-to-Right Embedding
    case 0x202B: // Right-to-Left Embedding
    case 0x202D: // Left-to-Right Override
    case 0x202E: // Right-to-Left Override
    case 0x2066: // Left-to-Right Isolate
    case 0x2067: // Right-to-Left Isolate
    case 0x2068: // First Strong Isolate
    case 0x202C: // Pop Directional Formatting
    case 0x2069: // Pop Directional Isolate
        return true;
    default:
        return false;
    }
}

void Scanner::count_indentation()
{
    auto empty_line = false;
    do {
        indent = 0;
        while (is(' ')) {
            indent++;
            reader.move();
        }
        empty_line = skip_empty_line();
    } while (empty_line);
}

bool Scanner::skip_empty_line()
{
    bool tabs = false;
    while (is_space()) {
        if (is('\t')) {
            tabs = true;
        }
        reader.move();
    }
    if (is('#')) {
        skip_comment();
    }
    if (is_new_line()) {
        reader.move();
        return true;
    }
    if (!is_eof() && tabs) {
        throw CompilationError::TabError;
    }
    return false;
}

void Scanner::skip_comment()
{
    do {
        reader.move();

        if (is_bidi()) {
            throw CompilationError::InvalidSyntax; // TODO: implement BIDI analysis instead
        }
    } while (!is_new_line() && !is_eof());
}

void Scanner::id_or_keyword()
{
    token = Token::Name;
    do {
        reader.move();
    } while (is_id_continue());

    auto result = keywords.find(reader.slice(token_index));
    if (result != keywords.end()) {
        token = result->second;
    }
}

void Scanner::number()
{
    integer();
}

void Scanner::integer()
{
    token = Token::Int;
    do {
        reader.move();
    } while (is_digit());

    if (is('.')) {
        real();
    }
}

void Scanner::real()
{
    token = Token::Float;
    do {
        reader.move();
    } while (is_digit());
}

void Scanner::simple_token()
{
    switch (reader.get_letter()) {
    case '*':
        reader.move();
        if (is('*')) {
            token = Token::Power;
            reader.move();
        } else {
            token = Token::Star;
        }
        break;
    case '/':
        reader.move();
        if (is('/')) {
            token = Token::DoubleSlash;
            reader.move();
        } else {
            token = Token::Slash;
        }
        break;
    case '<':
        reader.move();
        if (is('=')) {
            token = Token::LessOrEqual;
            reader.move();
        } else if (is('<')) {
            token = Token::LeftShift;
            reader.move();
        } else {
            token = Token::Less;
        }
        break;
    case '>':
        reader.move();
        if (is('>')) {
            token = Token::RightShift;
            reader.move();
        } else if (is('=')) {
            token = Token::GreaterOrEqual;
            reader.move();
        } else {
            token = Token::Greater;
        }
        break;
    case ',':
        token = Token::Comma;
        reader.move();
        break;
    case ':':
        token = Token::Colon;
        reader.move();
        break;
    case ';':
        token = Token::Semicolon;
        reader.move();
        break;
    case '~':
        token = Token::BitNot;
        reader.move();
        break;
    case '\\':
        reader.move();
        if (is('\r')) {
            reader.move();
        }
        if (is('\n')) {
            token = Token::Ignore;
            reader.move();
        }
        break;
    case '!':
        reader.move();
        if (is('=')) {
            token = Token::NotEqual;
            reader.move();
        }
        break;
    case '=':
        reader.move();
        if (is('=')) {
            token = Token::Equal;
            reader.move();
        } else {
            token = Token::AsgStmt;
        }
        break;
    case '+':
        token = Token::Plus;
        reader.move();
        break;
    case '-':
        reader.move();
        if (is('>')) {
            token = Token::RightArrow;
            reader.move();
        } else {
            token = Token::Minus;
        }
        break;
    case '%':
        token = Token::Percent;
        reader.move();
        break;
    case '^':
        token = Token::BitXor;
        reader.move();
        break;
    case '|':
        token = Token::BitOr;
        reader.move();
        break;
    case '&':
        token = Token::BitAnd;
        reader.move();
        break;
    case '(':
        token = Token::LeftParenthesis;
        ignore_new_line++;
        reader.move();
        break;
    case ')':
        token = Token::RightParenthesis;
        if (ignore_new_line > 0) {
            ignore_new_line--;
        }
        reader.move();
        break;
    case '[':
        token = Token::LeftBracket;
        ignore_new_line++;
        reader.move();
        break;
    case ']':
        token = Token::RightBracket;
        if (ignore_new_line > 0) {
            ignore_new_line--;
        }
        reader.move();
        break;
    case '{':
        token = Token::LeftBrace;
        ignore_new_line++;
        reader.move();
        break;
    case '}':
        token = Token::RightBrace;
        if (ignore_new_line > 0) {
            ignore_new_line--;
        }
        reader.move();
        break;
    case '.':
        reader.move();
        if (is_digit()) {
            real();
        } else {
            token = Token::Point;
        }
        break;
    case '#':
        token = Token::Ignore;
        skip_comment();
        break;
    default:
        break;
    }
}

} // namespace quirk