#include "../src/analysis/scope_builder.h"
#include "../src/parser/parser.h"
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
    std::unordered_map<ast::Node*, scopes::ProgObj*> bindings;
    analysis::ScopeBuilder sb;
    auto m = sb.build(tu.get());

    // std::unordered_map<scopes::Declaration*, scopes::Declaration*> type_table;
    // ti::TypeInference inferer(tu.get(), bindings, type_table);

    return 0;
}