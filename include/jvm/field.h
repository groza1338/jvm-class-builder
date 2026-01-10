#ifndef JVM__FIELD_H
#define JVM__FIELD_H
#include <iosfwd>

#include "constant-utf-8-info.h"

namespace jvm
{
    class Attribute;

    class Field
    {
        friend std::ostream& operator<<(std::ostream& os, const Field& field);

    public:
        enum AccessFlag
        {
            ACC_PUBLIC = 0x0001, ///< Declared public; may be accessed from outside its package.
            ACC_PRIVATE = 0x0002,
            ///< Declared private; accessible only within the defining class and other classes belonging to the same nest.
            ACC_PROTECTED = 0x0004, ///< Declared protected; may be accessed within subclasses.
            ACC_STATIC = 0x0008, ///< Declared static.
            ACC_FINAL = 0x0010, ///< Declared final; never directly assigned to after object construction (JLS §17.5).
            ACC_VOLATILE = 0x0040, ///< Declared volatile; cannot be cached.
            ACC_TRANSIENT = 0x0080, ///< Declared transient; not written or read by a persistent object manager.
            ACC_SYNTHETIC = 0x1000, ///< Declared synthetic; not present in the source code.
            ACC_ENUM = 0x4000, ///< Declared as an element of an enum class.
        };

        /**
         * Create field with selected name and descriptor.
         * @param name Pointer to UTF-8 constant with field name.
         * @param descriptor Pointer to UTF-8 constant with field descriptor.
         * @note The name and descriptor must belong to the same  owner.
         */
        Field(ConstantUtf8Info* name, ConstantUtf8Info* descriptor);

        /**
         * Create field with selected name, descriptor and classOwner.
         * @param name Field name string.
         * @param descriptor Field descriptor string.
         * @param classOwner Pointer to class owner.
         */
        Field(std::string name, std::string descriptor, Class* classOwner);

        /**
         * Add access flag to field.
         * @param flag Access flag.
         */
        void addFlag(AccessFlag flag);

        /**
         * Remove access flag from field.
         * @param flag Access flag.
         */
        void removeFlag(AccessFlag flag);

        /**
         * Add attribute to field.
         * @param attribute Field attribute.
         */
        void addAttribute(Attribute* attribute);

        /**
         * Remove attribute from field.
         * @param attribute Field attribute.
         */
        void removeAttribute(Attribute* attribute);

        /**
         * @return Access flags set.
         */
        [[nodiscard]] const std::set<AccessFlag>* getAccessFlags() const;

        /**
         * @return Constant of field name.
         */
        [[nodiscard]] ConstantUtf8Info* getName() const;

        /**
         * @return Constant of field descriptor.
         */
        [[nodiscard]] ConstantUtf8Info* getDescriptor() const;

        /**
         * @return Field attributes set.
         */
        [[nodiscard]] const std::set<Attribute*>* getAttributes() const;

        /**
         * @return Class owner.
         */
        [[nodiscard]] Class* getClass() const;

    private:
        /**
         * Write object to binary stream.
         * @param os Output stream.
         */
        void toBinary(std::ostream& os) const;

        std::set<AccessFlag> accessFlags_{}; ///< Access flags.
        ConstantUtf8Info* name_ = nullptr; ///< String constant with field name.
        ConstantUtf8Info* descriptor_ = nullptr; ///< String constant with field descriptor.
        std::set<Attribute*> attributes_{}; ///< Attributes.
        Class* classOwner_ = nullptr;
    };

    std::ostream& operator<<(std::ostream& os, const Field& field);
} // jvm

#endif //JVM__FIELD_H
