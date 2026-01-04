#include "method.h"

#include <cassert>
#include <ostream>
#include <utility>

using namespace Jvm;

Method::Method(ConstantUtf8Info* name, ConstantUtf8Info* descriptor)
{
    Class* nameOwner = name->getClassOwner();
    Class* descriptorOwner = descriptor->getClassOwner();
    assert(nameOwner == descriptorOwner);
    classOwner_ = nameOwner;
}

Method::Method(std::string name, std::string descriptor, Class* classOwner) : classOwner_(classOwner)
{
    name_ = classOwner->getOrCreateUtf8Constant(name);
    descriptor_ = classOwner->getOrCreateUtf8Constant(descriptor);
}


void Method::addFlag(AccessFlag flag)
{
    accessFlags_.insert(flag);
}

void Method::removeFlag(AccessFlag flag)
{
    accessFlags_.erase(flag);
}

void Method::addAttribute(Attribute* attribute)
{
    attributes_.insert(attribute);
}

void Method::removeAttribute(Attribute* attribute)
{
    attributes_.erase(attribute);
}

const std::set<Method::AccessFlag>* Method::getAccessFlags() const
{
    return &accessFlags_;
}

ConstantUtf8Info* Method::getName() const
{
    return name_;
}

ConstantUtf8Info* Method::getDescriptor() const
{
    return descriptor_;
}

const std::set<Attribute*>* Method::getAttributes() const
{
    return &attributes_;
}

Class* Method::getClassOwner() const
{
    return classOwner_;
}

void Method::toBinary(std::ostream& os) const
{
    // u2             access_flags;
    uint16_t accessFlags = 0x0000;
    for (auto flag : accessFlags_)
    {
        accessFlags = accessFlags | flag;
    }
    os.write(reinterpret_cast<const char*>(&accessFlags), sizeof(accessFlags));

    // u2             name_index;
    uint16_t nameIndex = name_->getIndex();
    os.write(reinterpret_cast<const char*>(&nameIndex), sizeof(nameIndex));

    // u2             descriptor_index;
    uint16_t descriptorIndex = descriptor_->getIndex();
    os.write(reinterpret_cast<const char*>(&descriptorIndex), sizeof(descriptorIndex));

    // u2             attributes_count;
    uint16_t attributeCount = attributes_.size();
    os.write(reinterpret_cast<const char*>(&attributeCount), sizeof(attributeCount));

    // attribute_info attributes[attributes_count];
    for (auto attribute : attributes_)
    {
        os << attribute;
    }
}

std::ostream& Jvm::operator<<(std::ostream& os, const Method& method)
{
    method.toBinary(os);
    return os;
}
