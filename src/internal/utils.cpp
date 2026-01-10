#include "jvm/internal/utils.h"
#include <ostream>
#include <arpa/inet.h>
#include <cstring>

namespace jvm::internal
{
    void Utils::writeBigEndian(std::ostream& os, uint8_t val)
    {
        os.put(static_cast<char>(val));
    }

    void Utils::writeBigEndian(std::ostream& os, uint16_t val)
    {
        const uint16_t be = htons(val);
        os.write(reinterpret_cast<const char*>(&be), sizeof(be));
    }

    void Utils::writeBigEndian(std::ostream& os, uint32_t val)
    {
        const uint32_t be = htonl(val);
        os.write(reinterpret_cast<const char*>(&be), sizeof(be));
    }

    void Utils::writeBigEndian(std::ostream& os, uint64_t val)
    {
        const uint32_t hi = static_cast<uint32_t>(val >> 32);
        const uint32_t lo = static_cast<uint32_t>(val & 0xFFFFFFFFull);

        const uint32_t hi_be = htonl(hi);
        const uint32_t lo_be = htonl(lo);

        os.write(reinterpret_cast<const char*>(&hi_be), sizeof(hi_be));
        os.write(reinterpret_cast<const char*>(&lo_be), sizeof(lo_be));
    }

    void Utils::writeBigEndian(std::ostream& os, int8_t val)
    {
        os.put(static_cast<char>(val));
    }

    void Utils::writeBigEndian(std::ostream& os, int16_t val)
    {
        writeBigEndian(os, static_cast<uint16_t>(val));
    }

    void Utils::writeBigEndian(std::ostream& os, int32_t val)
    {
        writeBigEndian(os, static_cast<uint32_t>(val));
    }

    void Utils::writeBigEndian(std::ostream& os, int64_t val)
    {
        writeBigEndian(os, static_cast<uint64_t>(val));
    }

    void Utils::writeBigEndian(std::ostream& os, float val)
    {
        uint32_t bits = 0;
        static_assert(sizeof(bits) == sizeof(val));
        std::memcpy(&bits, &val, sizeof(bits));
        writeBigEndian(os, bits);
    }

    void Utils::writeBigEndian(std::ostream& os, double val)
    {
        uint64_t bits = 0;
        static_assert(sizeof(bits) == sizeof(val));
        std::memcpy(&bits, &val, sizeof(bits));
        writeBigEndian(os, bits);
    }
} // jvm