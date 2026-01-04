#include "constant-double.h"

#include <cstring>
#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

ConstantDouble* ConstantDouble::getOrCreate(double value, Class* classOwner)
{
    // search constant
    for (auto* constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Double)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* constantDouble = static_cast<ConstantDouble*>(constant);
            if (std::memcmp(&constantDouble->value_, &value, sizeof(double)) == 0)
            {
                return constantDouble;
            }
        }
    }
    // create new
    return new ConstantDouble(value, classOwner);
}

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
    uint64_t bits = 0;

    std::memcpy(&bits, &value_, sizeof(bits));

    uint32_t high = static_cast<uint32_t>(bits >> 32);
    uint32_t low = static_cast<uint32_t>(bits & 0xFFFFFFFFULL);

    uint32_t bigEndianHigh = htonl(high);
    uint32_t bigEndianLow = htonl(low);

    os.write(reinterpret_cast<const char*>(&bigEndianHigh), sizeof(bigEndianHigh));
    os.write(reinterpret_cast<const char*>(&bigEndianLow), sizeof(bigEndianLow));
}

ConstantDouble::ConstantDouble(double value, Class* classOwner)
    : Constant(CONSTANT_Double, classOwner),
      value_(value)
{
}
