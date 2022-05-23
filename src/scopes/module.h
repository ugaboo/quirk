#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "declaration.h"

namespace quirk::scopes {

using namespace std;

class Module {
    unordered_map<string, unique_ptr<Declaration>> decls;
};

}  // namespace quirk::scopes