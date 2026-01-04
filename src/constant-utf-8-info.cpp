#include "constant-utf-8-info.h"

#include <ostream>
using namespace Jvm;

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
