#include "constant-methodref.h"

#include <cassert>
#include <ostream>

using namespace Jvm;

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
    os.write(reinterpret_cast<const char*>(&classIndex), sizeof(classIndex));
    uint16_t nameAndTypeIndex = nameAndType_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameAndTypeIndex), sizeof(nameAndTypeIndex));
}

ConstantMethodref::ConstantMethodref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant) :
    Constant(CONSTANT_Methodref, classConstant->getClassOwner()), class_(classConstant),
    nameAndType_(nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);
}
