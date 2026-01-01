#include "constant-integer.h"

#include <ostream>
#include <arpa/inet.h>

using namespace Jvm;

ConstantInteger* ConstantInteger::getOrCreate(int32_t value, Class* classOwner)
{
    // search constant
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Integer)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantInteger* constantInteger = static_cast<ConstantInteger*>(constant);
            if (constantInteger->getValue() == value)
            {
                return constantInteger;
            }
        }
    }
    // create new
    return new ConstantInteger(value, classOwner);
}

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
