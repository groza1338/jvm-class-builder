#include "jvm/descriptor.h"

#include <stdexcept>

using namespace jvm;

void Descriptor::isValidPrimitiveFieldType(PrimitiveFieldType primitiveFieldType)
{
    if (primitiveFieldType == PrimitiveFieldType::UNKNOWN)
    {
        throw std::invalid_argument("PrimitiveFieldType::UNKNOWN is not allowed");
    }
}

void Descriptor::isEmptyClassReference(const std::string& classReference)
{
    if (classReference.empty())
    {
        throw std::invalid_argument(
            "Class reference must not be empty"
        );
    }
}
