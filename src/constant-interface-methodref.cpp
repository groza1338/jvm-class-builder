#include "constant-interface-methodref.h"

#include <cassert>
#include <ostream>

using namespace Jvm;

ConstantClass* ConstantInterfaceMethodref::getClass() const
{
    return class_;
}

ConstantNameAndType* ConstantInterfaceMethodref::getNameAndType() const
{
    return nameAndType_;
}

void ConstantInterfaceMethodref::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t classIndex = class_->getIndex();
    os.write(reinterpret_cast<const char*>(&classIndex), sizeof(classIndex));
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameAndTypeIndex), sizeof(nameAndTypeIndex));
}

ConstantInterfaceMethodref::ConstantInterfaceMethodref(ConstantClass* classConstant,
                                                       ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_InterfaceMethodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
