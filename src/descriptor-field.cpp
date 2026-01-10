#include "jvm/descriptor-field.h"

#include <stdexcept>
#include <utility>

using namespace jvm;

DescriptorField DescriptorField::primitive(PrimitiveFieldType primitiveFieldType)
{
    isValidPrimitiveFieldType(primitiveFieldType);
    return DescriptorField(primitiveFieldType);
}

DescriptorField DescriptorField::primitiveArray(PrimitiveFieldType primitiveFieldType, uint8_t arrayDepth)
{
    isValidPrimitiveFieldType(primitiveFieldType);
    return DescriptorField(primitiveFieldType, arrayDepth);
}

DescriptorField DescriptorField::object(std::string classReference)
{
    isEmptyClassReference(classReference);
    return DescriptorField(std::move(classReference));
}

DescriptorField DescriptorField::objectArray(std::string classReference, uint8_t arrayDepth)
{
    isEmptyClassReference(classReference);
    return DescriptorField(std::move(classReference), arrayDepth);
}

std::string DescriptorField::toString() const
{
    std::string result;

    for (uint8_t i = 0; i < fieldType_.arrayDepth_; i++)
    {
        result.push_back('[');
    }

    if (fieldType_.primitiveFieldType_ != PrimitiveFieldType::UNKNOWN)
    {
        result.push_back(primitiveTypeToChar(fieldType_.primitiveFieldType_));
        return result;
    }

    if (!fieldType_.classReference_.empty())
    {
        result.push_back('L');
        result += fieldType_.classReference_;
        result.push_back(';');
        return result;
    }

    throw std::logic_error("Invalid field descriptor state");
}

Descriptor::PrimitiveFieldType DescriptorField::getPrimitiveFieldType() const
{
    return fieldType_.primitiveFieldType_;
}

uint8_t DescriptorField::getArrayDepth() const
{
    return fieldType_.arrayDepth_;
}

std::string DescriptorField::getClassReference() const
{
    return fieldType_.classReference_;
}
