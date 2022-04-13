#include "syn/parser.h"

#include "syn/sem/codegen.h"
#include "syn/sem/scope_builder.h"
#include "syn/sem/type_inference.h"

using namespace std;
using namespace quirk;

int main() {
    Parser parser(TEST_DIR "codegen/ops_overload.qk");
    unique_ptr<ast::Module> m;
    if (!parser.parse(m)) {
        return 1;
    }

    ScopeBuilder builder;
    builder.visit(m.get());

    CodeGen codegen(TEST_DIR "codegen/ops_overload.ll");
    codegen.visit(m.get());

    return 0;
}