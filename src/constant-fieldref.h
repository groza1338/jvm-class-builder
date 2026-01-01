#ifndef JVM__CONSTANT_FIELDREF_H
#define JVM__CONSTANT_FIELDREF_H

#include "constant-class.h"
#include "constant-name-and-type.h"
#include "constant.h"

namespace Jvm
{
    class ConstantFieldref : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @note Can create class constant or name and type constant.
         * @param className Class name string.
         * @param fieldName Field name string.
         * @param fieldDescriptor Filed descriptor.
         * @param classOwner Class owner.
         * @return Fieldref constant.
         */
        static ConstantFieldref* getOrCreate(std::string className, std::string fieldName, std::string fieldDescriptor,
                                             Class* classOwner);
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Field name and type constant.
         * @return Fieldref constant.
         */
        static ConstantFieldref* getOrCreate(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        /**
         * @return Class constant.
         */
        [[nodiscard]] ConstantClass* getClass() const;

        /**
         * @return Field name and type constant.
         */
        [[nodiscard]] ConstantNameAndType* getNameAndType() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create fieldref constant.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Field name and type constant.
         */
        ConstantFieldref(ConstantClass* classConstant, ConstantNameAndType* nameAndTypeConstant);

        ConstantClass* class_; ///< Class constant.
        ConstantNameAndType* nameAndType_; ///< Field name and type constant.
    };
} //Jvm


#endif //JVM__CONSTANT_FIELDREF_H
