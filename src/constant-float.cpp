#include "constant-float.h"

#include <cstring>
#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

ConstantFloat* ConstantFloat::getOrCreate(float value, Class* classOwner)
{
    // search constant
    for (auto* constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Float)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* constantFloat = static_cast<ConstantFloat*>(constant);
            if (std::memcmp(&constantFloat->value_, &value, sizeof(float)) == 0)
            {
                return constantFloat;
            }
        }
    }
    // create new
    return new ConstantFloat(value, classOwner);
}

float ConstantFloat::getValue() const
{
    return value_;
}

void ConstantFloat::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint32_t bits = 0;
    static_assert(sizeof(float) == sizeof(uint32_t), "float must big-endian 32-bit IEEE-754");
    std::memcpy(&bits, &value_, sizeof(bits));

    uint32_t bigEndianFloat = htonl(bits);
    os.write(reinterpret_cast<const char*>(&bigEndianFloat), sizeof(bigEndianFloat));
}

ConstantFloat::ConstantFloat(float value, Class* classOwner)
    : Constant(CONSTANT_Float, classOwner),
      value_(value)
{
}
