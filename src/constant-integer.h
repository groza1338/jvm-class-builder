#ifndef JVM__CONSTANT_INTEGER_H
#define JVM__CONSTANT_INTEGER_H
#include "constant.h"

namespace Jvm
{
    class ConstantInteger : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param value Integer value.
         * @param classOwner Class owner.
         * @return Integer constant.
         */
        ConstantInteger* getOrCreate(int32_t value, Class* classOwner);

        /**
         * @return Integer value.
         */
        [[nodiscard]] int32_t getValue();

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create integer constant.
         * @param value Integer value.
         * @param classOwner Class owner.
         */
        ConstantInteger(int32_t value, Class* classOwner);

        int32_t value_; ///< Integer value.
    };
} // Jvm

#endif //JVM__CONSTANT_INTEGER_H
