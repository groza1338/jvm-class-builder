#include "jvm/constant-string.h"

#include <ostream>

#include "jvm/internal/utils.h"

using namespace jvm;

ConstantUtf8Info* ConstantString::getString()
{
    return string_;
}

void ConstantString::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t stringIndex = string_->getIndex();
    internal::Utils::writeBigEndian(os, stringIndex);
}

ConstantString::ConstantString(ConstantUtf8Info* utf8StringConstant) :
    Constant(CONSTANT_String, utf8StringConstant->getClassOwner()), string_(utf8StringConstant)
{
}
