#pragma once

namespace quirk {

// TODO: replace with exceptions
enum class CompilationError {
    InvalidSyntax,
    ExpectedAnIndentedBlock,
    DedentDoesntMatch,
    TabError,
    NotAStatement,
    ItemNotFound,
    ReservedName,
    Redefinition,
    NotCallable,
    TypeInferenceFailed,
};

}