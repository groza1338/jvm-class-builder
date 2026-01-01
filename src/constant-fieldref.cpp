#include "constant-fieldref.h"

#include <cassert>
#include <ostream>
#include <utility>

using namespace Jvm;

ConstantFieldref* ConstantFieldref::getOrCreate(std::string className, std::string fieldName,
                                                std::string fieldDescriptor, Class* classOwner)
{
    ConstantClass* classConstant = ConstantClass::getOrCreate(std::move(className), classOwner);
    ConstantNameAndType* nameAndTypeConstant = ConstantNameAndType::getOrCreate(
        std::move(fieldName), std::move(fieldDescriptor), classOwner);
    return getOrCreate(classConstant, nameAndTypeConstant);
}

ConstantFieldref* ConstantFieldref::getOrCreate(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant)
{
    bool equalClassOwner = classConstant->getClassOwner() == nameAndTypeConstant->getClassOwner();
    assert(equalClassOwner);

    // search constant
    Class* classOwner = classConstant->getClassOwner();
    for (auto constant : classOwner->constants())
    {
        if (constant->getTag() == CONSTANT_Fieldref)
        {
            // Use static method because only one tag can be associated with only one class type.
            ConstantFieldref* constantFieldref = static_cast<ConstantFieldref*>(constant);
            if (constantFieldref->getClass() == classConstant && constantFieldref->getNameAndType() ==
                nameAndTypeConstant)
            {
                return constantFieldref;
            }
        }
    }
    // create new
    return new ConstantFieldref(classConstant, nameAndTypeConstant);
}

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
