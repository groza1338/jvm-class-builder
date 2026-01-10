#include "jvm/constant-float.h"

#include <cstring>

#include "jvm/internal/utils.h"

using namespace Jvm;

float ConstantFloat::getValue() const
{
    return value_;
}

void ConstantFloat::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    Internal::Utils::writeBigEndian(os, value_);
}

ConstantFloat::ConstantFloat(float value, Class* classOwner)
    : Constant(CONSTANT_Float, classOwner),
      value_(value)
{
}
