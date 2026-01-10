#include "jvm/constant-name-and-type.h"

#include <cassert>

#include "jvm/internal/utils.h"

namespace Jvm
{
    ConstantUtf8Info* ConstantNameAndType::getName() const
    {
        return name_;
    }

    ConstantUtf8Info* ConstantNameAndType::getDescriptor() const
    {
        return descriptor_;
    }

    void ConstantNameAndType::toBinary(std::ostream& os) const
    {
        Constant::toBinary(os);
        uint16_t nameIndex = name_->getIndex();
        Internal::Utils::writeBigEndian(os, nameIndex);
        uint16_t descriptorIndex = descriptor_->getIndex();
        Internal::Utils::writeBigEndian(os, descriptorIndex);
    }

    ConstantNameAndType::ConstantNameAndType(ConstantUtf8Info* name, ConstantUtf8Info* descriptor) :
        Constant(CONSTANT_NameAndType, name->getClassOwner()), name_(name), descriptor_(descriptor)
    {
        Class* nameClassOwner = name->getClassOwner();
        Class* descriptorClassOwner = descriptor->getClassOwner();
        assert(nameClassOwner == descriptorClassOwner);
    }
} // Jvm
