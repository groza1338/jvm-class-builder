#ifndef JVM__CONSTANT_LONG_H
#define JVM__CONSTANT_LONG_H

#include "constant.h"

namespace Jvm
{
    class ConstantLong : public Constant
    {
        friend class Class;

    public:
        /**
         * @return Long value.
         */
        [[nodiscard]] int64_t getValue() const;

        /**
        * @return the number of slots by the constant
        */
        [[nodiscard]] uint16_t getOccupiedSlots() const override;

    protected:
        void toBinary(std::ostream& os) const override;

    private:
        /**
         * Create long constant.
         * @param value Long value.
         * @param classOwner Class owner.
         */
        ConstantLong(int64_t value, Class* classOwner);

        int64_t value_; ///< Long value.
    };
} // namespace Jvm


#endif // JVM__CONSTANT_LONG_H
