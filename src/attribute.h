#ifndef JVM__ATTRIBUTE_H
#define JVM__ATTRIBUTE_H
#include <iosfwd>

#include "constant-utf-8-info.h"

namespace Jvm
{
    class Attribute
    {
        friend std::ostream& operator<<(std::ostream& os, const Attribute& attribute);

    public:
        virtual ~Attribute() = default;

        /**
         * @return Attribute name constant.
         */
        [[nodiscard]] ConstantUtf8Info* getName() const;

        /**
         * Is it class @{Jvm::Class} attribute.
         * @return Is class attribute.
         */
        [[nodiscard]] virtual bool isClassAttribute() const;

        /**
         * Is it field @{Jvm::Field} attribute.
         * @return Is field attribute.
         */
        [[nodiscard]] virtual bool isFieldAttribute() const;

        /**
         * Is it method @{Jvm::Method} attribute.
         * @return Is method attribute.
         */
        [[nodiscard]] virtual bool isMethodAttribute() const;

        /**
         * Is it record component attribute.
         * @return Is record component attribute.
         */
        [[nodiscard]] virtual bool isRecordComponentAttribute() const;

        /**
         * Is it code attribute.
         * @return Is code attribute.
         */
        [[nodiscard]] virtual bool isCodeAttribute() const;

        /**
         * Length of attribute in bytes.
         * @return Size in bytes.
         */
        [[nodiscard]] virtual uint32_t getAttributeLength() const = 0;

    protected:
        /**
         * Write object to binary stream.
         * @param os Output stream.
         */
        virtual void toBinary(std::ostream& os) const;

    private:
        ConstantUtf8Info* name_ = nullptr; ///< Attribute name constant.
    };

    std::ostream& operator<<(std::ostream& os, const Attribute& attribute);
} // Jvm

#endif //JVM__ATTRIBUTE_H
