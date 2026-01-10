#ifndef JVM__DESCRIPTOR_H
#define JVM__DESCRIPTOR_H

#include <cstdint>
#include <string>

namespace jvm
{
    class Descriptor
    {
    public:
        /**
         * Destructor.
         */
        virtual ~Descriptor() = default;

        /**
         * Primitive field types.
         */
        enum class PrimitiveFieldType
        {
            BYTE,
            CHAR,
            DOUBLE,
            FLOAT,
            INT,
            LONG,
            SHORT,
            BOOLEAN,
            UNKNOWN
        };

        /**
         * @return descriptor by string
         */
        [[nodiscard]] virtual std::string toString() const;

    protected:

        /**
        * struct of field type.
        */
        struct FieldType
        {
            PrimitiveFieldType primitiveFieldType_;
            uint8_t arrayDepth_; // only for arrays
            std::string classReference_; // only for class references
        };

        /**
         * @param primitiveType  primitive field type.
         * @return primitive field type by char.
         */
        static constexpr char primitiveTypeToChar(PrimitiveFieldType primitiveType)
        {
            switch (primitiveType)
            {
                case PrimitiveFieldType::BYTE: return 'B';
                case PrimitiveFieldType::CHAR: return 'C';
                case PrimitiveFieldType::DOUBLE: return 'D';
                case PrimitiveFieldType::FLOAT: return 'F';
                case PrimitiveFieldType::INT: return 'I';
                case PrimitiveFieldType::LONG: return 'J';
                case PrimitiveFieldType::SHORT: return 'S';
                case PrimitiveFieldType::BOOLEAN: return 'Z';
                case PrimitiveFieldType::UNKNOWN: return '_';
                default: return '?';
            }
        }

        static void isValidPrimitiveFieldType(PrimitiveFieldType primitiveFieldType);
        static void isEmptyClassReference(const std::string& classReference);

        FieldType fieldType_ = {PrimitiveFieldType::UNKNOWN, 0, ""};
    };
}

#endif //JVM__DESCRIPTOR_H