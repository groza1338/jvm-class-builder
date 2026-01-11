#ifndef JVM__CLASS_FILE_ELEMENT_H
#define JVM__CLASS_FILE_ELEMENT_H

#include <cassert>
#include <cstddef>
#include <iosfwd>

#include "serializable.h"

namespace jvm
{
    /**
     * @brief Base class for elements of a JVM class file with explicit ownership.
     *
     * @tparam Owner Type of the logical owner of this element.
     *
     * This class represents a structural element of a class file that:
     * - belongs to a specific owner object,
     * - participates in binary serialization,
     * - enforces a strict ownership relationship.
     *
     * The owner pointer is stored explicitly and must be non-null.
     * Copying is disabled to preserve unique ownership semantics.
     *
     * @note The owner type is declared as a friend to allow controlled construction
     *       and internal modification.
     */
    template <class Owner>
    class ClassFileElement : protected Serializable
    {
        friend Owner;

    public:
        /**
         * @brief Construct a class file element bound to an owner.
         *
         * @param owner Pointer to the owning object.
         * @pre @p owner must not be null.
         */
        explicit ClassFileElement(Owner* owner);

        /// Copying is disabled to preserve ownership semantics.
        ClassFileElement(const ClassFileElement&) = delete;
        ClassFileElement& operator=(const ClassFileElement&) = delete;

        /// Move operations are allowed.
        ClassFileElement(ClassFileElement&&) = default;
        ClassFileElement& operator=(ClassFileElement&&) = default;

        /**
         * @return Pointer to the owning object.
         */
        [[nodiscard]] Owner* getOwner() const;

    private:
        Owner* owner_;
    };


    /**
     * @brief Specialization for root class-file elements without an owner.
     *
     * Used for top-level structures that do not belong to any parent element
     * and are responsible for serializing other elements.
     *
     * This specialization exposes the @ref Serializable interface publicly,
     * allowing external serialization of the root object.
     */
    template <>
    class ClassFileElement<void> : public Serializable
    {
    public:
        ClassFileElement(const ClassFileElement&) = delete;
        ClassFileElement& operator=(const ClassFileElement&) = delete;

        ClassFileElement(ClassFileElement&&) = default;
        ClassFileElement& operator=(ClassFileElement&&) = default;
    };

} // jvm

#endif //JVM__CLASS_FILE_ELEMENT_H
