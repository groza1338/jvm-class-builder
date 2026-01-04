#include "constant-name-and-type.h"

#include <assert.h>
#include <ostream>
#include <utility>

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
        os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));
        uint16_t descriptorIndex = descriptor_->getIndex();
        os.write(reinterpret_cast<const char*>(&descriptorIndex), sizeof(descriptorIndex));
    }

    ConstantNameAndType::ConstantNameAndType(ConstantUtf8Info* name, ConstantUtf8Info* descriptor) :
        Constant(CONSTANT_NameAndType, name->getClassOwner()), name_(name), descriptor_(descriptor)
    {
        Class* nameClassOwner = name->getClassOwner();
        Class* descriptorClassOwner = descriptor->getClassOwner();
        assert(nameClassOwner == descriptorClassOwner);
    }
} // Jvm
