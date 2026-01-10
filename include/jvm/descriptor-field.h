#ifndef JVM__DESCRIPTOR_FIELD_H
#define JVM__DESCRIPTOR_FIELD_H

#include <utility>

#include "descriptor.h"

namespace jvm
{
    class DescriptorField: public Descriptor
    {
    public:
        /**
         * @brief Creates a descriptor for a primitive (non-array) field type.
         *
         * Examples:
         * - int        -> "I"
         * - boolean   -> "Z"
         *
         * @param primitiveFieldType Primitive JVM field type.
         * @return DescriptorField representing the primitive field type.
         */
        static DescriptorField primitive(PrimitiveFieldType primitiveFieldType);

        /**
         * @brief Creates a descriptor for an array of primitive field type.
         *
         * Examples:
         * - int[]      -> "[I"
         * - double[][]-> "[[D"
         *
         * @param primitiveFieldType Primitive JVM field type.
         * @param arrayDepth Number of array dimensions (must be >= 1).
         * @return DescriptorField representing the primitive array field type.
         */
        static DescriptorField primitiveArray(PrimitiveFieldType primitiveFieldType, uint8_t arrayDepth);

        /**
         * @brief Creates a descriptor for an object (reference) field type.
         *
         * The class name must be provided in JVM internal form
         * (e.g. "java/lang/String").
         *
         * Example:
         * - String -> "Ljava/lang/String;"
         *
         * @param classReference JVM internal class name.
         * @return DescriptorField representing the object field type.
         */
        static DescriptorField object(std::string classReference);

        /**
         * @brief Creates a descriptor for an array of object (reference) field type.
         *
         * The class name must be provided in JVM internal form
         * (e.g. "java/lang/String").
         *
         * Examples:
         * - String[]    -> "[Ljava/lang/String;"
         * - String[][] -> "[[Ljava/lang/String;"
         *
         * @param classReference JVM internal class name.
         * @param arrayDepth Number of array dimensions (must be >= 1).
         * @return DescriptorField representing the object array field type.
         */
        static DescriptorField objectArray(std::string classReference, uint8_t arrayDepth);

        /**
         * @return primitive field type
         */
        [[nodiscard]] PrimitiveFieldType getPrimitiveFieldType() const;

        /**
         * @return array depth
         */
        [[nodiscard]] uint8_t getArrayDepth() const;

        /**
         * @return class reference
         */
        [[nodiscard]] std::string getClassReference() const;

        /**
         * @return JVM field descriptor string (e.g. "I", "[[D")
         */
        [[nodiscard]] std::string toString() const override;

    private:
        explicit DescriptorField(PrimitiveFieldType primitiveFieldType)
        {
            fieldType_.primitiveFieldType_ = primitiveFieldType;
        }

        explicit DescriptorField(PrimitiveFieldType primitiveFieldType, uint8_t arrayDepth)
        {
            fieldType_ = {
                .primitiveFieldType_ = primitiveFieldType,
                .arrayDepth_ = arrayDepth,
            };
            fieldType_.classReference_.clear();
        }

        explicit DescriptorField(std::string classReference)
        {
            fieldType_ = {
                .primitiveFieldType_ = PrimitiveFieldType::UNKNOWN,
                .arrayDepth_ = 0,
                .classReference_ = std::move(classReference)
            };
        }

        explicit DescriptorField(std::string classReference, uint8_t arrayDepth)
        {
            fieldType_ = {
                .primitiveFieldType_ = PrimitiveFieldType::UNKNOWN,
                .arrayDepth_ = arrayDepth,
                .classReference_ = std::move(classReference)
            };
        }

    };
}

#endif //JVM__DESCRIPTOR_FIELD_H