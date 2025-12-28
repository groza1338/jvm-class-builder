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

    class Class
    {
        static uint16_t minorVersion;
        static uint16_t majorVersion;

    public:
        Class(std::string name);

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

    private:
        void toBinary(std::ostream& os);

        std::vector<Constant*> constants_{};
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
