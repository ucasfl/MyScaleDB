#pragma once

#include <Parsers/IAST.h>

namespace DB
{

class ASTFunction;

/** name BY expr TYPE typename(args) GRANULARITY int in create query
 * expr TYPE typename(args) GRANULARITY int in create index query
  */
class ASTIndexDeclaration : public IAST
{
public:
    String name;
    IAST * expr;
    ASTFunction * type;
    UInt64 granularity;
    bool part_of_create_index_query = false;

    /** Get the text that identifies this element. */
    String getID(char) const override { return "Index"; }

    ASTPtr clone() const override;
    void formatImpl(const FormatSettings & s, FormatState & state, FormatStateStacked frame) const override;

    void forEachPointerToChild(std::function<void(void**)> f) override
    {
        f(reinterpret_cast<void **>(&expr));
        f(reinterpret_cast<void **>(&type));
    }
};

}
