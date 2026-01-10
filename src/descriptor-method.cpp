#include "jvm/descriptor-method.h"

#include <stdexcept>

using namespace Jvm;

DescriptorMethod DescriptorMethod::of(std::vector<DescriptorField> params, std::optional<DescriptorField> ret)
{
    for (const auto& p : params)
    {
        if (p.getPrimitiveFieldType() == PrimitiveFieldType::UNKNOWN)
        {
            throw std::logic_error(
                "Parameter has UNKNOWN type"
            );
        }
    }

    if (ret && ret->getPrimitiveFieldType() == PrimitiveFieldType::UNKNOWN)
    {
        throw std::logic_error(
            "Return type has UNKNOWN type"
        );
    }

    return {std::move(params), std::move(ret)};
}

std::string DescriptorMethod::toString() const
{
    std::string result;
    result.push_back('(');

    for (const auto& param : params_)
    {
        result += param.toString();
    }

    result.push_back(')');

    if (ret_)
    {
        result += ret_->toString();
    }
    else
    {
        result.push_back('V');
    }

    return result;
}
