#include "constant-string.h"

#include <ostream>
#include <utility>

using namespace Jvm;

ConstantUtf8Info* ConstantString::getString()
{
    return string_;
}

void ConstantString::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t stringIndex = string_->getIndex();
    os.write(reinterpret_cast<const char*>(&stringIndex), sizeof(stringIndex));
}

ConstantString::ConstantString(ConstantUtf8Info* utf8StringConstant) :
    Constant(CONSTANT_String, utf8StringConstant->getClassOwner()), string_(utf8StringConstant)
{
}
