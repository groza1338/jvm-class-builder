#include "attribute.h"

#include <ostream>

using namespace Jvm;

ConstantUtf8Info* Attribute::getName() const
{
    return name_;
}

bool Attribute::isClassAttribute() const
{
    return false;
}

bool Attribute::isFieldAttribute() const
{
    return false;
}

bool Attribute::isMethodAttribute() const
{
    return false;
}

bool Attribute::isRecordComponentAttribute() const
{
    return false;
}

bool Attribute::isCodeAttribute() const
{
    return false;
}

void Attribute::toBinary(std::ostream& os) const
{
    // u2 attribute_name_index;
    uint16_t nameIndex = name_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));

    // u4 attribute_length;
    uint32_t length = getAttributeLength();
    os.write(reinterpret_cast<const char*>(&length), sizeof(length));
}

std::ostream& Jvm::operator<<(std::ostream& os, const Attribute& attribute)
{
    attribute.toBinary(os);
    return os;
}
