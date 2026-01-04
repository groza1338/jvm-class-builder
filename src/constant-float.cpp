#include "constant-float.h"

#include <cstring>
#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

float ConstantFloat::getValue() const
{
    return value_;
}

void ConstantFloat::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint32_t bits = 0;

    std::memcpy(&bits, &value_, sizeof(bits));

    uint32_t bigEndianFloat = htonl(bits);
    os.write(reinterpret_cast<const char*>(&bigEndianFloat), sizeof(bigEndianFloat));
}

ConstantFloat::ConstantFloat(float value, Class* classOwner)
    : Constant(CONSTANT_Float, classOwner),
      value_(value)
{
}
