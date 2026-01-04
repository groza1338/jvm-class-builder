#include "constant-class.h"

#include <ostream>

using namespace Jvm;

ConstantUtf8Info* ConstantClass::getName() const
{
    return name_;
}

void ConstantClass::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t nameIndex = name_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));
}

ConstantClass::ConstantClass(ConstantUtf8Info* name) : Constant(CONSTANT_Class, name->getClassOwner()), name_(name)
{
}
