#pragma once
#include <iostream>
#include <string>

namespace quirk {

enum class Token {
    None,

    Indent,
    Dedent,

    NewLine,
    EndMarker,

    Ignore,

    NotEqual,          // !=
    Percent,           // %
    BitAnd,            // &
    LeftParenthesis,   // (
    RightParenthesis,  // )
    Star,              // *
    Power,             // **
    Plus,              // +
    Comma,             // ,
    Minus,             // -
    RightArrow,        // ->
    Point,             // .
    Slash,             // /
    DoubleSlash,       // //
    Colon,             // :
    Semicolon,         // ;
    Less,              // <
    LeftShift,         // <<
    LessOrEqual,       // <=
    AsgStmt,           // =
    Equal,             // ==
    Greater,           // >
    GreaterOrEqual,    // >=
    RightShift,        // >>
    At,                // @
    LeftBracket,       // [
    RightBracket,      // ]
    BitXor,            // ^
    LeftBrace,         // {
    BitOr,             // |
    RightBrace,        // }
    BitNot,            // ~

    Int,    // 42
    Float,  // 42.0

    Name,

    KwAnd,       // and
    KwBreak,     // break
    KwContinue,  // continue
    KwDef,       // def
    KwElif,      // elif
    KwElse,      // else
    KwFalse,     // False
    KwIf,        // if
    KwNone,      // None
    KwNot,       // not
    KwOr,        // or
    KwPass,      // pass
    KwReturn,    // return
    KwStruct,    // struct
    KwTrue,      // True
    KwWhile,     // while
};

}