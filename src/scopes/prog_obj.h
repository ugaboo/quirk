#pragma once

namespace quirk::scopes {

class Visitor;

// ProgObj is a base class for logical representations of entities defined in the code.
class ProgObj {
public:
    virtual ~ProgObj() {}

    virtual void accept(Visitor* visitor) = 0;
};

// Type is a base class for types.
class Type : public ProgObj {
};

} // namespace quirk::scopes