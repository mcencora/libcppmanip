#include "TextOperationApplier.hpp"

std::string TextOperationApplier::apply(const std::string& text)
{
    if (insertions.empty())
        return text;
    auto copy = text;
    for (auto const& ins : insertions)
    {
        unsigned insertionOffset = ins.first;
        auto textToInsert = ins.second;
        copy = copy.substr(0, insertionOffset) + textToInsert + copy.substr(insertionOffset);
    }
    return copy;
}

void TextOperationApplier::insertTextAt(const std::string& text, unsigned offset)
{
    insertions[offset] += text;
}
