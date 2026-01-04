#ifndef JVM__CLASS_H
#define JVM__CLASS_H

#include <cstdint>
#include <set>
#include <span>
#include <string>
#include <vector>

namespace Jvm
{
    class Constant;
    class Field;
    class Method;
    class Attribute;

    enum MajorVersion:uint16_t
    {
        MAJOR_VERSION_1_0_2 = 45,
        MAJOR_VERSION_1_1 = 45,
        MAJOR_VERSION_1_2 = 46,
        MAJOR_VERSION_1_3 = 47,
        MAJOR_VERSION_1_4 = 48,
        MAJOR_VERSION_5 = 49,
        MAJOR_VERSION_6 = 50,
        MAJOR_VERSION_7 = 51,
        MAJOR_VERSION_8 = 52,
        MAJOR_VERSION_9 = 53,
        MAJOR_VERSION_10 = 54,
        MAJOR_VERSION_11 = 55,
        MAJOR_VERSION_12 = 56,
        MAJOR_VERSION_13 = 57,
        MAJOR_VERSION_14 = 58,
        MAJOR_VERSION_15 = 59,
        MAJOR_VERSION_16 = 60,
    };

    class Class
    {
        static uint16_t minorVersion;
        static MajorVersion majorVersion;

    public:
        enum AccessFlags
        {
            ACC_PUBLIC = 0x0001, // Declared public; may be accessed from outside its package.
            ACC_FINAL = 0x0010, // Declared final; no subclasses allowed.
            ACC_SUPER = 0x0020, // Treat superclass methods specially when invoked by the invokespecial instruction.
            ACC_INTERFACE = 0x0200, // Is an interface, not a class.
            ACC_ABSTRACT = 0x0400, // Declared abstract; must not be instantiated.
            ACC_SYNTHETIC = 0x1000, // Declared synthetic; not present in the source code.
            ACC_ANNOTATION = 0x2000, // Declared as an annotation interface.
            ACC_ENUM = 0x4000, // Declared as an enum class.
            ACC_MODULE = 0x8000, // Is a module, not a class or interface.
        };

        Class(std::string name);

        void addNewConstant(Constant* constant);

        std::span<Constant*> constants();

    private:
        void toBinary(std::ostream& os) const;

        std::vector<Constant*> constants_{};
        uint16_t nextCpIndex = 1; // 0 index is not available for writing
        std::set<AccessFlags> accessFlags_{};
        Constant* thisClassConstant_ = nullptr;
        Constant* superClassConstant_ = nullptr;
        std::set<Constant*> interfacesConstant_{};
        std::set<Field*> fields_;
        std::set<Method*> methods_;
        std::set<Attribute*> attributes_;
    };
}
#endif //JVM__CLASS_H
