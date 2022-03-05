#pragma once
#include "prog_obj.h"

namespace quirk::ast {

class BinaryExpr : public Expr {
public:
    enum class Kind {
        Or,
        And,
        Less,
        Greater,
        Equal,
        LessOrEqual,
        GreaterOrEqual,
        NotEqual,
        BitOr,
        BitXor,
        BitAnd,
        LeftShift,
        RightShift,
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        IntDiv,
        Power,
    };

private:
    Decl* type;
    Kind kind;
    unique_ptr<Expr> left, right;

public:
    BinaryExpr(Kind kind, unique_ptr<Expr>& left, unique_ptr<Expr>& right)
        : kind(kind), left(move(left)), right(move(right)) {}

    auto get_kind() { return kind; }
    auto get_left() { return left.get(); }
    auto get_right() { return right.get(); }
    auto get_type() { return type; }
    void set_type(Decl* type) { BinaryExpr::type = type; }

    void accept(Visitor* visitor) override;
};

}  // namespace quirk::ast