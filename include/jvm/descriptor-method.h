#ifndef JVM__DESCRIPTOR_METHOD_H
#define JVM__DESCRIPTOR_METHOD_H

#include <optional>
#include <vector>

#include "descriptor.h"
#include "descriptor-field.h"

namespace Jvm
{
    class DescriptorMethod: public Descriptor
    {
        public:

        /**
         * @brief Creates a method descriptor.
         *
         * Builds a JVM method descriptor from the given parameter types and
         * an optional return type.
         *
         * Each element of @p params represents a method parameter and must be a valid
         * field descriptor. If @p ret is not provided, the method return type is
         * considered {@code void}.
         *
         * Examples:
         *   - params = { int, int }, ret = int   -> "(II)I"
         *   - params = { }, ret = void           -> "()V"
         *   - params = { String[] }, ret = void  -> "([Ljava/lang/String;)V"
         *
         * @param params Vector of method parameter descriptors.
         * @param ret Optional return type descriptor; {@code std::nullopt} represents {@code void}.
         *
         * @return A fully constructed {@link DescriptorMethod} instance.
         *
         * @throws std::logic_error If the descriptor cannot be constructed due to
         *         an invalid parameter or return type.
         */
        static DescriptorMethod of(std::vector<DescriptorField> params, std::optional<DescriptorField> ret = std::nullopt);

        /**
         * @return JVM method descriptor string (e.g. "(II)I", "()V")
         */
        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] const std::vector<DescriptorField>& getParams() const { return params_; }
        [[nodiscard]] const std::optional<DescriptorField>& getRet() const { return ret_; }

        private:
        DescriptorMethod(std::vector<DescriptorField> params,
                 std::optional<DescriptorField> ret)
        : params_(std::move(params)), ret_(std::move(ret)) {}

        std::vector<DescriptorField> params_;
        std::optional<DescriptorField> ret_;
    };
}

#endif //JVM__DESCRIPTOR_METHOD_H