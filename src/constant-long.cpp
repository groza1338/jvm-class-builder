#include "constant-long.h"

#include <cstring>
#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

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
    uint32_t low = static_cast<uint32_t>(bits & 0xFFFFFFFFULL);

    uint32_t bigEndianHigh = htonl(high);
    uint32_t bigEndianLow = htonl(low);

    os.write(reinterpret_cast<const char*>(&bigEndianHigh), sizeof(bigEndianHigh));
    os.write(reinterpret_cast<const char*>(&bigEndianLow), sizeof(bigEndianLow));
}

ConstantLong::ConstantLong(int64_t value, Class* classOwner)
    : Constant(CONSTANT_Long, classOwner),
      value_(value)
{
}
