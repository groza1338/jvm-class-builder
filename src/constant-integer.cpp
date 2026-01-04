#include "constant-integer.h"

#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

int32_t ConstantInteger::getValue()
{
    return value_;
}

void ConstantInteger::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    auto integer = htonl(static_cast<uint32_t>(value_));
    os.write(reinterpret_cast<const char*>(&integer), sizeof(integer));
}

ConstantInteger::ConstantInteger(int32_t value, Class* classOwner) : Constant(CONSTANT_Integer, classOwner),
                                                                     value_(value)
{
}
