#include "jvm/label.h"

#include <cassert>

using namespace jvm;

Instruction* Label::getInstruction() const
{
    return instruction_;
}

AttributeCode* Label::getAttributeCodeOwner() const
{
    return attributeCodeOwner_;
}

Label::Label(AttributeCode* codeAttributeOwner) : attributeCodeOwner_(codeAttributeOwner)
{
    assert(codeAttributeOwner != nullptr);
}

bool Label::isInitialized() const
{
    return instruction_ != nullptr;
}

void Label::setInstruction(Instruction* instruction)
{
    assert(instruction != nullptr);
    assert(instruction_ == nullptr);

    instruction_ = instruction;
}
