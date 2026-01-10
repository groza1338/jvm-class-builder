#include "jvm/constant-fieldref.h"

#include <cassert>

#include "jvm/internal/utils.h"

using namespace jvm;

ConstantClass* ConstantFieldref::getClass() const
{
    return class_;
}

ConstantNameAndType* ConstantFieldref::getNameAndType() const
{
    return nameAndType_;
}

void ConstantFieldref::toBinary(std::ostream& os) const
{
    Constant::toBinary(os);

    uint16_t classIndex = class_->getIndex();
    internal::Utils::writeBigEndian(os, classIndex);

    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    internal::Utils::writeBigEndian(os, nameAndTypeIndex);
}

ConstantFieldref::ConstantFieldref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_Fieldref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
