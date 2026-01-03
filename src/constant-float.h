#ifndef JVM__CONSTANT_FLOAT_H
#define JVM__CONSTANT_FLOAT_H

#include "constant.h"

namespace Jvm
{
    class ConstantFloat : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param value Float value.
         * @param classOwner Class owner.
         * @return Float constant.
         */
        static ConstantFloat* getOrCreate(float value, Class* classOwner);

        /**
         * @return Float value.
         */
        [[nodiscard]] float getValue() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create float constant.
         * @param value Float value.
         * @param classOwner Class owner.
         */
        ConstantFloat(float value, Class* classOwner);

        float value_; ///< Float value.
    };
} // namespace Jvm

#endif // JVM__CONSTANT_FLOAT_H
