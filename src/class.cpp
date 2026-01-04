#include "class.h"
#include "constant.h"

#include <cstdint>
#include <ostream>

using namespace Jvm;

MajorVersion Class::majorVersion = MAJOR_VERSION_16;
uint16_t Class::minorVersion = 0x0000;

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
