#include "constant-long.h"

#include <cstring>
#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

ConstantLong* ConstantLong::getOrCreate(long value, Class* classOwner)
{
    // search constant
    for (auto* constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Long)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* constantLong = static_cast<ConstantLong*>(constant);

            if (constantLong->value_ == value)
            {
                return constantLong;
            }
        }
    }
    return new ConstantLong(value, classOwner);
}

int64_t ConstantLong::getValue() const
{
    return value_;
}

uint16_t ConstantLong::getOccupiedSlots() const
{
    return 2;
}

void ConstantLong::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);

    uint64_t bits = static_cast<uint64_t>(value_);

    uint32_t high = static_cast<uint32_t>(bits >> 32);
    uint32_t low  = static_cast<uint32_t>(bits & 0xFFFFFFFFULL);

    uint32_t bigEndianHigh = htonl(high);
    uint32_t bigEndianLow  = htonl(low);

    os.write(reinterpret_cast<const char*>(&bigEndianHigh), sizeof(bigEndianHigh));
    os.write(reinterpret_cast<const char*>(&bigEndianLow), sizeof(bigEndianLow));
}

ConstantLong::ConstantLong(int64_t value, Class* classOwner)
    : Constant(CONSTANT_Long, classOwner),
      value_(value)
{
}
