#include "constant.h"

#include <ostream>

using namespace Jvm;


Constant::Tag Constant::getTag() const
{
    return tag_;
}

uint16_t Constant::getOccupiedSlots() const
{
    return 1;
}

uint16_t Constant::getIndex() const
{
    return index_;
}

Class* Constant::getClassOwner() const
{
    return classOwner_;
}

Constant::Constant(Tag tag, Class* classOwner) : tag_(tag), classOwner_(classOwner)
{
}

void Constant::toBinary(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&tag_), sizeof(tag_));
}

void Constant::setIndex(uint32_t index)
{
    index_ = index;
}

std::ostream& Jvm::operator<<(std::ostream& os, const Constant& constant)
{
    constant.toBinary(os);
    return os;
}
