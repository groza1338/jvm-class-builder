#include "jvm/constant-double.h"

#include <cstring>
#include <arpa/inet.h>

#include "jvm/internal/utils.h"

using namespace jvm;

double ConstantDouble::getValue() const
{
    return value_;
}

uint16_t ConstantDouble::getOccupiedSlots() const
{
    return 2;
}

void ConstantDouble::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    internal::Utils::writeBigEndian(os, value_);
}

ConstantDouble::ConstantDouble(double value, Class* classOwner)
    : Constant(CONSTANT_Double, classOwner),
      value_(value)
{
}
