#include "jvm/attribute.h"

#include <ostream>

#include "jvm/internal/utils.h"

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
    Internal::Utils::writeBigEndian(os, static_cast<uint16_t>(nameIndex));

    // u4 attribute_length;
    uint32_t length = getAttributeLength();
    Internal::Utils::writeBigEndian(os, static_cast<uint32_t>(length));
}

std::ostream& Jvm::operator<<(std::ostream& os, const Attribute& attribute)
{
    attribute.toBinary(os);
    return os;
}
