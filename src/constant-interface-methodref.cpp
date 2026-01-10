#include "jvm/constant-interface-methodref.h"

#include <cassert>

#include "jvm/internal/utils.h"

using namespace jvm;

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
    internal::Utils::writeBigEndian(os, classIndex);
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    internal::Utils::writeBigEndian(os, nameAndTypeIndex);
}

ConstantInterfaceMethodref::ConstantInterfaceMethodref(ConstantClass* classConstant,
                                                       ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_InterfaceMethodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
