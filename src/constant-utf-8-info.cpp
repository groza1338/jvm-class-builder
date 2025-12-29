#include "constant-utf-8-info.h"

#include <ostream>
using namespace Jvm;

ConstantUtf8Info* ConstantUtf8Info::getOrCreate(std::string string, Class* classOwner)
{
    // search constant
    auto constants = classOwner->constants();
    for(auto constant : constants)
    {
        if (constant->getTag() == CONSTANT_Utf8)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantUtf8Info* constantUtf8 = static_cast<ConstantUtf8Info*>(constant);
            if(constantUtf8->getString() == string)
            {
                return constantUtf8;
            }
        }
    }
    // create new
    return new ConstantUtf8Info(string, classOwner);
}

std::string ConstantUtf8Info::getString() const
{
    return string_;
}

ConstantUtf8Info::ConstantUtf8Info(std::string string, Class* classOwner) :
    Constant(CONSTANT_Utf8, classOwner), string_(string)
{
}

void ConstantUtf8Info::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t size = string_.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(string_.c_str(), size);
}
