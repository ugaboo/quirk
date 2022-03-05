#pragma once

namespace quirk {

enum class CompilationError {
    InvalidSyntax,
    ExpectedAnIndentedBlock,
    DedentDoesntMatch,
    TabError,
    ConstantTooLarge,
    NotAStatement,
    ItemNotFound,
    Redefinition,
    NotCallable,
};

}