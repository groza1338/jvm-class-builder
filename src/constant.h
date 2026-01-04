#ifndef JVM__CONSTANT_H
#define JVM__CONSTANT_H

#include <cstdint>
#include "class.h"

namespace Jvm
{
    /**
     * Base class of constant.
     */
    class Constant
    {
        // friend class and operators
        friend class Class;
        friend std::ostream& operator<<(std::ostream& os, const Constant& constant);

    public:
        /**
         * Destructor.
         */
        virtual ~Constant() = default;

        /**
         * Constant values tag.
         */
        enum Tag:uint8_t
        {
            CONSTANT_Class = 7,
            CONSTANT_Fieldref = 9,
            CONSTANT_Methodref = 10,
            CONSTANT_InterfaceMethodref = 11,
            CONSTANT_String = 8,
            CONSTANT_Integer = 3,
            CONSTANT_Float = 4,
            CONSTANT_Long = 5,
            CONSTANT_Double = 6,
            CONSTANT_NameAndType = 12,
            CONSTANT_Utf8 = 1,
            CONSTANT_MethodHandle = 15,
            CONSTANT_MethodType = 16,
            CONSTANT_Dynamic = 17,
            CONSTANT_InvokeDynamic = 18,
            CONSTANT_Module = 19,
            CONSTANT_Package = 20
        };

        /**
         * @return Tag of constant value.
         */
        Tag getTag() const;

        /**
         * @return the number of slots by the constant
         */
        [[nodiscard]] virtual uint16_t getOccupiedSlots() const;

        /**
         * @return Index in the table of constants.
         */
        uint16_t getIndex() const;

        /**
         * @return Constant owner class.
         */
        Class* getClassOwner() const;

    protected:
        /**
         * Create constant with tag and class owner.
         * Also set index in the table of constants.
         * @param tag Tag of constant.
         * @param classOwner Constant owner class.
         */
        explicit Constant(Tag tag, Class* classOwner);

        /**
         * Write object to binary stream.
         * @param os Output stream.
         */
        virtual void toBinary(std::ostream& os) const;

    private:
        /**
         * @param index Index in the table of constants.
         */
        void setIndex(uint32_t index);

        Tag tag_; ///< Tag of constant.
        uint16_t index_ = 0; ///< Index in the table of constants.
        Class* classOwner_ = nullptr; ///< Class owner.
    };

    /**
     * Write constant to binary output stream.
     * @param os Output stream.
     * @param constant Constant object.
     * @return Output stream.
     */
    std::ostream& operator<<(std::ostream& os, const Constant& constant);
}
#endif //JVM__CONSTANT_H
