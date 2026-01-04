#include "class.h"
#include "constant.h"
#include "constant-class.h"
#include "constant-double.h"
#include "constant-fieldref.h"
#include "constant-float.h"
#include "constant-integer.h"
#include "constant-interface-methodref.h"
#include "constant-long.h"
#include "constant-methodref.h"
#include "constant-name-and-type.h"
#include "constant-string.h"
#include "constant-utf-8-info.h"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <ostream>
#include <utility>


using namespace Jvm;

MajorVersion Class::majorVersion = MAJOR_VERSION_16;
uint16_t Class::minorVersion = 0x0000;

ConstantClass* Class::getOrCreateClassConstant(const std::string& name)
{
    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    return getOrCreateClassConstant(nameConstant);
}

ConstantClass* Class::getOrCreateClassConstant(ConstantUtf8Info* name)
{
    assert(this == name->getClassOwner());

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
                                                     const std::string& fieldDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(fieldName, fieldDescriptor);
    return getOrCreateFieldrefConstant(classConstant, nameAndTypeConstant);
}

ConstantFieldref* Class::getOrCreateFieldrefConstant(ConstantClass* classConstant,
                                                     ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getClassOwner());
    assert(this == nameAndTypeConstant -> getClassOwner());

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
                                                       const std::string& methodDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantMethodref* Class::getOrCreateMethodrefConstant(ConstantClass* classConstant,
                                                       ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getClassOwner());
    assert(this == nameAndTypeConstant->getClassOwner());

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
                                                                         const std::string& methodName,
                                                                         const std::string& methodDescriptor)
{
    ConstantClass* classConstant = getOrCreateClassConstant(className);
    ConstantNameAndType* nameAndTypeConstant = getOrCreateNameAndTypeConstant(methodName, methodDescriptor);
    return getOrCreateInterfaceMethodrefConstant(classConstant, nameAndTypeConstant);
}

ConstantInterfaceMethodref* Class::getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
                                                                         ConstantNameAndType* nameAndTypeConstant)
{
    assert(this == classConstant->getClassOwner());
    assert(this == nameAndTypeConstant->getClassOwner());

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
    assert(this == utf8Constant->getClassOwner());

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
            if (std::memcmp(&floatConstant->value_, &value, sizeof(float)) == 0)
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
            if (longConstant->value_ == value)
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
            if (std::memcmp(&doubleConstant->value_, &value, sizeof(double)) == 0)
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

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(const std::string& name, const std::string& descriptor)
{
    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    ConstantUtf8Info* descriptorConstant = getOrCreateUtf8Constant(descriptor);
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(const std::string& name,
                                                           ConstantUtf8Info* descriptorConstant)
{
    assert(this == descriptorConstant->getClassOwner());

    ConstantUtf8Info* nameConstant = getOrCreateUtf8Constant(name);
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                           const std::string& descriptor)
{
    assert(this == nameConstant->getClassOwner());

    ConstantUtf8Info* descriptorConstant = getOrCreateUtf8Constant(descriptor);
    return getOrCreateNameAndTypeConstant(nameConstant, descriptorConstant);
}

ConstantNameAndType* Class::getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                           ConstantUtf8Info* descriptorConstant)
{
    assert(this == nameConstant->getClassOwner());
    assert(this == descriptorConstant->getClassOwner());

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

void Class::addNewConstant(Constant* constant)
{
    constants_.push_back(constant);
    constant->setIndex(nextCpIndex);

    nextCpIndex += constant->getOccupiedSlots();
}

std::span<Constant*> Class::constants()
{
    return constants_;
}

void Class::toBinary(std::ostream& os) const
{
    // u4             magic;
    static uint32_t magicNumber = 0xCAFEBABE;
    os.write(reinterpret_cast<const char*>(&magicNumber), sizeof(magicNumber));

    // u2             minor_version;
    os.write(reinterpret_cast<const char*>(&minorVersion), sizeof(minorVersion));

    // u2             major_version;
    os.write(reinterpret_cast<const char*>(&majorVersion), sizeof(majorVersion));

    // u2             constant_pool_count;
    uint16_t constantCount = static_cast<uint16_t>(constants_.size());
    os.write(reinterpret_cast<const char*>(&constantCount), sizeof(constantCount));

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
    os.write(reinterpret_cast<const char*>(&accessFlags), sizeof(accessFlags));

    // u2             this_class;
    uint16_t thisClass = thisClassConstant_->getIndex();
    os.write(reinterpret_cast<const char*>(&thisClass), sizeof(thisClass));

    // u2             super_class;
    uint16_t superClass = superClassConstant_->getIndex();
    os.write(reinterpret_cast<const char*>(&superClass), sizeof(superClass));

    // u2             interfaces_count;
    uint16_t interfacesCount = static_cast<uint16_t>(interfacesConstant_.size());
    os.write(reinterpret_cast<const char*>(&interfacesCount), sizeof(interfacesCount));

    // u2             interfaces[interfaces_count];
    for (const auto& interface : interfacesConstant_)
    {
        uint16_t interfaceIndex = interface->getIndex();
        os.write(reinterpret_cast<const char*>(&interfaceIndex), sizeof(interfaceIndex));
    }

    // u2             fields_count;
    uint16_t fieldsCount = static_cast<uint16_t>(fields_.size());
    os.write(reinterpret_cast<const char*>(&fieldsCount), sizeof(fieldsCount));

    // field_info     fields[fields_count];
    for (const auto& field : fields_)
    {
        os << field;
    }

    // u2             methods_count;
    uint16_t methodsCount = static_cast<uint16_t>(fields_.size());
    os.write(reinterpret_cast<const char*>(&methodsCount), sizeof(methodsCount));

    // method_info    methods[methods_count];
    for (const auto& method : fields_)
    {
        os << method;
    }

    // u2             attributes_count;
    uint16_t attributesCount = static_cast<uint16_t>(fields_.size());
    os.write(reinterpret_cast<const char*>(&attributesCount), sizeof(attributesCount));

    // attribute_info attributes[attributes_count];
    for (const auto& attribute : fields_)
    {
        os << attribute;
    }
}
