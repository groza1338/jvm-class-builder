#include "jvm/constant-integer.h"

#include <ostream>

#include "jvm/internal/utils.h"

using namespace jvm;

int32_t ConstantInteger::getValue()
{
    return value_;
}

void ConstantInteger::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    internal::Utils::writeBigEndian(os, value_);
}

ConstantInteger::ConstantInteger(int32_t value, Class* classOwner) : Constant(CONSTANT_Integer, classOwner),
                                                                     value_(value)
{
}
