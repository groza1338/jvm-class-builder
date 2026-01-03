#ifndef JVM__CONSTANT_DOUBLE_H
#define JVM__CONSTANT_DOUBLE_H

#include "constant.h"

namespace Jvm
{
    class ConstantDouble : public Constant
    {
    public:
        /**
         * Looks up and returns an existing constant from constant pool of classOwner or create a new one.
         * @param value double value.
         * @param classOwner Class owner.
         * @return Double constant.
         */
        static ConstantDouble* getOrCreate(double value, Class* classOwner);

        /**
         * @return Double value.
         */
        [[nodiscard]] double getValue() const;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create double constant.
         * @param value Double value.
         * @param classOwner Class owner.
         */
        ConstantDouble(double value, Class* classOwner);

        double value_; ///< Double value.
    };
} // namespace Jvm


#endif // JVM__CONSTANT_DOUBLE_H