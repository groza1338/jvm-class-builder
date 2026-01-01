#ifndef JVM__CONSTANT_NAME_AND_TYPE_H
#define JVM__CONSTANT_NAME_AND_TYPE_H
#include "constant-utf-8-info.h"
#include "constant.h"

namespace Jvm
{
    /**
     * Name and type constant.
     * Contains information about name and descriptor.
     */
    class ConstantNameAndType : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create UTF-8 constant with name or descriptor.
         * @param name Name string.
         * @param descriptor Descriptor string.
         * @param classOwner Pointer to class owner object.
         * @return Name and type constant.
         */
        static ConstantNameAndType* getOrCreate(std::string name, std::string descriptor, Class* classOwner);

        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create UTF-8 constant with name.
         * @param name Name string.
         * @param descriptorConstant UTF-8 constant with descriptor.
         * @return Name and type constant.
         */
        static ConstantNameAndType* getOrCreate(std::string name, ConstantUtf8Info* descriptorConstant);

        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create UTF-8 constant with descriptor.
         * @param nameConstant UTF-8 constant with name.
         * @param descriptor Descriptor string.
         * @return Name and type constant.
         */
        static ConstantNameAndType* getOrCreate(ConstantUtf8Info* nameConstant, std::string descriptor);

        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note nameConstant and descriptorConstant must have a common class owner.
         * @param nameConstant UTF-8 constant with name.
         * @param descriptorConstant UTF-8 constant with descriptor.
         * @return Name and type constant.
         */
        static ConstantNameAndType* getOrCreate(ConstantUtf8Info* nameConstant, ConstantUtf8Info* descriptorConstant);

        /**
         * @return UTF-8 constant with name.
         */
        [[nodiscard]] ConstantUtf8Info* getName() const;

        /**
         * @return UTF-8 constant with descriptor.
         */
        [[nodiscard]] ConstantUtf8Info* getDescriptor() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create name and type constant.
         * @param name UTF-8 constant with name.
         * @param descriptor UTF-8 constant with descriptor.
         */
        ConstantNameAndType(ConstantUtf8Info* name, ConstantUtf8Info* descriptor);

        ConstantUtf8Info* name_; ///< UTF-8 constant with name.
        ConstantUtf8Info* descriptor_; ///< UTF-8 constant with descriptor.
    };
} // Jvm

#endif //JVM__CONSTANT_NAME_AND_TYPE_H
