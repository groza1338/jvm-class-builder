#include "constant-fieldref.h"

#include <cassert>
#include <ostream>
#include <utility>

using namespace Jvm;

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
    os.write(reinterpret_cast<const char*>(&classIndex), sizeof(classIndex));
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameAndTypeIndex), sizeof(nameAndTypeIndex));
}

ConstantFieldref::ConstantFieldref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_Fieldref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
