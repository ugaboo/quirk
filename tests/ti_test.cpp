#include "../src/parser/parser.h"
#include "../src/scopes/scope_builder.h"
#include "../src/ti/type_inference.h"
#include "../src/util/operator_table.h"

using namespace quirk;

int main()
{
    Parser parser(TEST_DIR "ti/test.qk");

    std::unique_ptr<ast::TranslationUnit> tu;
    if (!parser.parse(tu)) {
        return 1;
    }

    scopes::Scope global_scope;
    util::OperatorTable op_table;
    op_table.fill_scope(global_scope);

    std::unordered_map<ast::Node*, scopes::Declaration*> bindings;
    scopes::ScopeBuilder builder(tu.get(), global_scope, bindings);
    builder.process();

    std::unordered_map<scopes::Declaration*, scopes::Declaration*> type_table;
    ti::TypeInference inferer(tu.get(), op_table, bindings, type_table);

    return 0;
}