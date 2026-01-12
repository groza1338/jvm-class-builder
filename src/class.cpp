#include "jvm/class.h"

#include <cassert>
#include <cstring>
#include <ostream>
#include <utility>

#include "jvm/constant.h"
#include "jvm/constant-class.h"
#include "jvm/constant-double.h"
#include "jvm/constant-fieldref.h"
#include "jvm/constant-float.h"
#include "jvm/constant-integer.h"
#include "jvm/constant-interface-methodref.h"
#include "jvm/constant-long.h"
#include "jvm/constant-methodref.h"
#include "jvm/constant-name-and-type.h"
#include "jvm/constant-string.h"
#include "jvm/constant-utf-8-info.h"
#include "jvm/descriptor-method.h"
#include "jvm/descriptor.h"
#include "jvm/field.h"
#include "jvm/method.h"
#include "jvm/internal/utils.h"


using namespace jvm;

MajorVersion Class::majorVersion = MAJOR_VERSION_16;

Class::Class(const std::string& className, const std::string& parentName)
{
    thisClassConstant_ = getOrCreateClassConstant(className);
    superClassConstant_ = getOrCreateClassConstant(parentName);
}

uint16_t Class::minorVersion = 0x0000;

ConstantClass* Class::getOrCreateClassConstant(const std::string& name)
{
    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    return getOrCreateClassConstant(nameConstant);
}

ConstantClass* Class::getOrCreateClassConstant(ConstantUtf8Info* name)
{
    assert(this == name->getOwner());

    // try search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Class)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* classConstant = static_cast<ConstantClass*>(constant);
            if (classConstant->getName() == name)
            {
                return classConstant;
            }
        }
    }

    // create new
    auto* classConstant = new ConstantClass(name);
    addNewConstant(classConstant);
    return classConstant;
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(const std::string& className, const std::string& fieldName,
    const DescriptorField& fieldDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(fieldName, fieldDescriptor);
    return getOrCreateFieldrefConstant(classConstant, nameAndTypeConstant);
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(ConstantClass* classConstant, const std::string& fieldName,
    const DescriptorField& fieldDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(fieldName, fieldDescriptor);
    return getOrCreateFieldrefConstant(classConstant, nameAndTypeConstant);
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(ConstantClass* classConstant, ConstantUtf8Info* fieldNameConstant,
    const DescriptorField& fieldDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(fieldNameConstant, fieldDescriptor);
    return getOrCreateFieldrefConstant(classConstant, nameAndTypeConstant);
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(ConstantClass* classConstant, ConstantUtf8Info* fieldNameConstant,
    ConstantUtf8Info* fieldDescriptorConstant)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(fieldNameConstant, fieldDescriptorConstant);
    return getOrCreateFieldrefConstant(classConstant, nameAndTypeConstant);
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(ConstantClass* classConstant,
                                                     ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getOwner());
    assert(this == nameAndTypeConstant -> getOwner());

    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Fieldref)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* fieldrefConstant = static_cast<ConstantFieldref*>(constant);
            if (fieldrefConstant->getClass() == classConstant && fieldrefConstant->getNameAndType() ==
                nameAndTypeConstant)
            {
                return fieldrefConstant;
            }
        }
    }

    // create new
    auto* fieldrefConstant = new ConstantFieldref(classConstant, nameAndTypeConstant);
    addNewConstant(fieldrefConstant);
    return fieldrefConstant;
}


ConstantMethodref* Class::getOrCreateMethodrefConstant(const std::string& className, const std::string& methodName,
    const DescriptorMethod& methodDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantMethodref* Class::getOrCreateMethodrefConstant(ConstantClass* classConstant, const std::string& methodName,
    const DescriptorMethod& methodDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantMethodref* Class::getOrCreateMethodrefConstant(ConstantClass* classConstant, ConstantUtf8Info* methodNameConstant,
    const DescriptorMethod& methodDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodNameConstant, methodDescriptor);
    return getOrCreateMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantMethodref* Class::getOrCreateMethodrefConstant(ConstantClass* classConstant, ConstantUtf8Info* methodNameConstant,
    ConstantUtf8Info* methodDescriptorConstant)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodNameConstant, methodDescriptorConstant);
    return getOrCreateMethodrefConstant(classConstant, nameAndTypeConstant);
}


ConstantMethodref* Class::getOrCreateMethodrefConstant(ConstantClass* classConstant,
                                                       ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getOwner());
    assert(this == nameAndTypeConstant->getOwner());

    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Methodref)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* constantMethodref = static_cast<ConstantMethodref*>(constant);
            if (constantMethodref->getClass() == classConstant && constantMethodref->getNameAndType() ==
                nameAndTypeConstant)
            {
                return constantMethodref;
            }
        }
    }

    // create new
    auto* methodrefConstant = new ConstantMethodref(classConstant, nameAndTypeConstant);
    addNewConstant(methodrefConstant);
    return methodrefConstant;
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(const std::string& className,
    const std::string& methodName, const DescriptorMethod& methodDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateInterfaceMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
    const std::string& methodName, const DescriptorMethod& methodDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateInterfaceMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
    ConstantUtf8Info* methodNameConstant, const DescriptorMethod& methodDescriptor)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodNameConstant, methodDescriptor);
    return getOrCreateInterfaceMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
    ConstantUtf8Info* methodNameConstant, ConstantUtf8Info* methodDescriptorConstant)
{
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodNameConstant,methodDescriptorConstant);
    return getOrCreateInterfaceMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
                                                                         ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getOwner());
    assert(this == nameAndTypeConstant->getOwner());

    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_InterfaceMethodref)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* interfaceMethodrefConstant = static_cast<ConstantInterfaceMethodref*>(constant);
            if (interfaceMethodrefConstant->getClass() == classConstant && interfaceMethodrefConstant->getNameAndType()
                ==
                nameAndTypeConstant)
            {
                return interfaceMethodrefConstant;
            }
        }
    }

    // create new
    auto* interfaceMethodrefConstant = new ConstantInterfaceMethodref(classConstant, nameAndTypeConstant);
    addNewConstant(interfaceMethodrefConstant);
    return interfaceMethodrefConstant;
}

ConstantString* Class::getOrCreateStringConstant(const std::string& value)
{
    ConstantUtf8Info* stringConstant = getOrCreateUtf8Constant(value);
    return getOrCreateStringConstant(stringConstant);
}

ConstantString* Class::getOrCreateStringConstant(ConstantUtf8Info* utf8Constant)
{
    assert(this == utf8Constant->getOwner());

    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_String)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* stringConstant = static_cast<ConstantString*>(constant);
            if (stringConstant->getString() == utf8Constant)
            {
                return stringConstant;
            }
        }
    }

    // create new
    auto* stringConstant = new ConstantString(utf8Constant);
    addNewConstant(stringConstant);
    return stringConstant;
}

ConstantInteger* Class::getOrCreateIntegerConstant(int32_t value)
{
    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Integer)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* integerConstant = static_cast<ConstantInteger*>(constant);
            if (integerConstant->getValue() == value)
            {
                return integerConstant;
            }
        }
    }

    // create new
    auto* integerConstant = new ConstantInteger(value, this);
    addNewConstant(integerConstant);
    return integerConstant;
}

ConstantFloat* Class::getOrCreateFloatConstant(float value)
{
    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Float)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* floatConstant = static_cast<ConstantFloat*>(constant);
            auto valueFromConstant = floatConstant->getValue();
            if (std::memcmp(&valueFromConstant, &value, sizeof(float)) == 0)
            {
                return floatConstant;
            }
        }
    }

    // create new
    auto* floatConstant = new ConstantFloat(value, this);
    addNewConstant(floatConstant);
    return floatConstant;
}

ConstantLong* Class::getOrCreateLongConstant(int64_t value)
{
    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Long)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* longConstant = static_cast<ConstantLong*>(constant);
            if (longConstant->getValue() == value)
            {
                return longConstant;
            }
        }
    }

    // create new
    auto* longConstant = new ConstantLong(value, this);
    addNewConstant(longConstant);
    return longConstant;
}

ConstantDouble* Class::getOrCreateDoubleConstant(double value)
{
    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Double)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* doubleConstant = static_cast<ConstantDouble*>(constant);
            auto valueFromConstant = doubleConstant->getValue();
            if (std::memcmp(&valueFromConstant, &value, sizeof(double)) == 0)
            {
                return doubleConstant;
            }
        }
    }

    // create new
    auto doubleConstant = new ConstantDouble(value, this);
    addNewConstant(doubleConstant);
    return doubleConstant;
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(const std::string& name,
                                                           ConstantUtf8Info* descriptorConstant)
{
    assert(this == descriptorConstant->getOwner());

    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(const std::string& name, const Descriptor& descriptor)
{
    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    ConstantUtf8Info* descriptorConstant = getOrCreateUtf8Constant(descriptor.toString());
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant, const Descriptor& descriptor)
{
    assert(this == nameConstant->getOwner());

    ConstantUtf8Info* descriptorConstant = getOrCreateUtf8Constant(descriptor.toString());
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                           ConstantUtf8Info* descriptorConstant)
{
    assert(this == nameConstant->getOwner());
    assert(this == descriptorConstant->getOwner());

    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_NameAndType)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* nameAndTypeConstant = static_cast<ConstantNameAndType*>(constant);
            if (nameAndTypeConstant->getName() == nameConstant &&
                nameAndTypeConstant->getDescriptor() == descriptorConstant)
            {
                return nameAndTypeConstant;
            }
        }
    }

    // create new
    auto* nameAndTypeConstant = new ConstantNameAndType(nameConstant, descriptorConstant);
    addNewConstant(nameAndTypeConstant);
    return nameAndTypeConstant;
}

ConstantUtf8Info* Class::getOrCreateUtf8Constant(const std::string& value)
{
    // search constant
    for (auto* constant : constants_)
    {
        if (constant->getTag() == Constant::CONSTANT_Utf8)
        {
            // Use static method because only one tag can be associated with only one class type.
            auto* utf8Constant = static_cast<ConstantUtf8Info*>(constant);
            if (utf8Constant->getString() == value)
            {
                return utf8Constant;
            }
        }
    }

    // create new
    auto* utf8Constant = new ConstantUtf8Info(value, this);
    addNewConstant(utf8Constant);
    return utf8Constant;
}

Method* Class::getOrCreateMethod(const std::string& name, const DescriptorMethod& descriptor)
{
    auto* nameConstant = getOrCreateUtf8Constant(name);
    auto* descriptorConstant = getOrCreateUtf8Constant(descriptor.toString());
    return getOrCreateMethod(nameConstant, descriptorConstant);
}

Method* Class::getOrCreateMethod(const std::string& name, ConstantUtf8Info* descriptorConstant)
{
    auto* nameConstant = getOrCreateUtf8Constant(name);
    return getOrCreateMethod(nameConstant, descriptorConstant);
}

Method* Class::getOrCreateMethod(ConstantUtf8Info* nameConstant, const DescriptorMethod& descriptor)
{
    auto* descriptorConstant = getOrCreateUtf8Constant(descriptor.toString());
    return getOrCreateMethod(nameConstant, descriptorConstant);
}

Method* Class::getOrCreateMethod(ConstantUtf8Info* nameConstant, ConstantUtf8Info* descriptorConstant)
{
    assert(this == nameConstant->getOwner());
    assert(this == descriptorConstant->getOwner());

    // search method
    for (auto* method : methods_)
    {
        if (method->getName() == nameConstant && method->getDescriptor() == descriptorConstant)
        {
            return method;
        }
    }

    // create new
    auto* method = new Method(nameConstant, descriptorConstant);
    methods_.insert(method);
    return method;
}

std::span<Constant*> Class::constants()
{
    return constants_;
}

void Class::writeTo(std::ostream& os) const
{
    // u4             magic;
    static uint32_t magicNumber = 0xCAFEBABE;
    internal::Utils::writeBigEndian(os, magicNumber);

    // u2             minor_version;
    internal::Utils::writeBigEndian(os, minorVersion);

    // u2             major_version;
    internal::Utils::writeBigEndian(os, static_cast<uint16_t>(majorVersion));

    // u2             constant_pool_count;
    uint16_t constantCount = static_cast<uint16_t>(nextCpIndex);
    internal::Utils::writeBigEndian(os, constantCount);

    // cp_info        constant_pool[constant_pool_count-1];
    for (const auto& constant : constants_)
    {
        os << *constant;
    }

    // u2             access_flags;
    uint16_t accessFlags = 0x0000;
    for (auto flag : accessFlags_)
    {
        accessFlags = accessFlags | flag;
    }
    internal::Utils::writeBigEndian(os, accessFlags);

    // u2             this_class;
    uint16_t thisClass = thisClassConstant_->getIndex();
    internal::Utils::writeBigEndian(os, thisClass);

    // u2             super_class;
    uint16_t superClass = superClassConstant_->getIndex();
    internal::Utils::writeBigEndian(os, superClass);

    // u2             interfaces_count;
    uint16_t interfacesCount = static_cast<uint16_t>(interfacesConstant_.size());
    internal::Utils::writeBigEndian(os, interfacesCount);

    // u2             interfaces[interfaces_count];
    for (const auto& interface : interfacesConstant_)
    {
        uint16_t interfaceIndex = interface->getIndex();
        internal::Utils::writeBigEndian(os, interfaceIndex);
    }

    // u2             fields_count;
    uint16_t fieldsCount = static_cast<uint16_t>(fields_.size());
    internal::Utils::writeBigEndian(os, fieldsCount);

    // field_info     fields[fields_count];
    for (const auto& field : fields_)
    {
        os << field;
    }

    // u2             methods_count;
    uint16_t methodsCount = static_cast<uint16_t>(fields_.size());
    internal::Utils::writeBigEndian(os, methodsCount);

    // method_info    methods[methods_count];
    for (const auto& method : methods_)
    {
        os << *method;
    }

    // u2             attributes_count;
    uint16_t attributesCount = static_cast<uint16_t>(fields_.size());
    internal::Utils::writeBigEndian(os, attributesCount);

    // attribute_info attributes[attributes_count];
    for (const auto& attribute : attributes_)
    {
        os << attribute;
    }
}

std::size_t Class::getByteSize() const
{
    size_t size = 0;

    // u4 magic;
    size += 4;
    // u2 minor_version;
    size += 2;
    // u2 major_version;
    size += 2;
    // u2 constant_pool_count;
    size += 2;
    // cp_info constant_pool[constant_pool_count-1];
    for (const auto& constant : constants_)
    {
        size += constant->getByteSize();
    }
    // u2 access_flags;
    size += 2;
    // u2 this_class;
    size += 2;
    // u2 super_class;
    size += 2;
    // u2 interfaces_count;
    size += 2;
    // u2 interfaces[interfaces_count];
    size += 2;
    // u2 fields_count;
    size += 2;
    // field_info fields[fields_count];
    for (auto* field : fields_)
    {
        size += field->getByteSize();
    }
    // u2 methods_count;
    size += 2;
    // method_info methods[methods_count];
    for (auto* method : methods_)
    {
        size += method->getByteSize();
    }
    // u2 attributes_count;
    size += 2;
    // attribute_info attributes[attributes_count];
    for (auto* attribute : attributes_)
    {
        size += attribute->getByteSize();
    }

    return size;
}

void Class::addNewConstant(Constant* constant)
{
    constants_.push_back(constant);
    constant->setIndex(nextCpIndex);

    nextCpIndex += constant->getOccupiedSlots();
}