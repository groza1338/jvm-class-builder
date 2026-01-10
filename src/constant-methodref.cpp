#include "jvm/constant-methodref.h"

#include <cassert>

#include "jvm/internal/utils.h"

using namespace jvm;

ConstantClass* ConstantMethodref::getClass() const
{
    return class_;
}

ConstantNameAndType* ConstantMethodref::getNameAndType() const
{
    return nameAndType_;
}

void ConstantMethodref::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);
    uint16_t classIndex = class_->getIndex();
    internal::Utils::writeBigEndian(os, classIndex);
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    internal::Utils::writeBigEndian(os, nameAndTypeIndex);
}

ConstantMethodref::ConstantMethodref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_Methodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
