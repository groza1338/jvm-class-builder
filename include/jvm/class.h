#ifndef JVM__CLASS_H
#define JVM__CLASS_H

#include <cstdint>
#include <set>
#include <span>
#include <string>
#include <vector>

namespace jvm
{
    class ConstantDouble;
    class ConstantLong;
    class ConstantFloat;
    class ConstantInteger;
    class ConstantString;
    class ConstantInterfaceMethodref;
    class ConstantMethodref;
    class ConstantNameAndType;
    class ConstantFieldref;
    class ConstantUtf8Info;
    class ConstantClass;
    class Constant;
    class Field;
    class Method;
    class Attribute;
    class Descriptor;

    enum MajorVersion:uint16_t
    {
        MAJOR_VERSION_1_0_2 = 45,
        MAJOR_VERSION_1_1 = 45,
        MAJOR_VERSION_1_2 = 46,
        MAJOR_VERSION_1_3 = 47,
        MAJOR_VERSION_1_4 = 48,
        MAJOR_VERSION_5 = 49,
        MAJOR_VERSION_6 = 50,
        MAJOR_VERSION_7 = 51,
        MAJOR_VERSION_8 = 52,
        MAJOR_VERSION_9 = 53,
        MAJOR_VERSION_10 = 54,
        MAJOR_VERSION_11 = 55,
        MAJOR_VERSION_12 = 56,
        MAJOR_VERSION_13 = 57,
        MAJOR_VERSION_14 = 58,
        MAJOR_VERSION_15 = 59,
        MAJOR_VERSION_16 = 60,
    };

    class Class
    {
        static uint16_t minorVersion;
        static MajorVersion majorVersion;

    public:
        enum AccessFlags
        {
            ACC_PUBLIC = 0x0001, // Declared public; may be accessed from outside its package.
            ACC_FINAL = 0x0010, // Declared final; no subclasses allowed.
            ACC_SUPER = 0x0020, // Treat superclass methods specially when invoked by the invokespecial instruction.
            ACC_INTERFACE = 0x0200, // Is an interface, not a class.
            ACC_ABSTRACT = 0x0400, // Declared abstract; must not be instantiated.
            ACC_SYNTHETIC = 0x1000, // Declared synthetic; not present in the source code.
            ACC_ANNOTATION = 0x2000, // Declared as an annotation interface.
            ACC_ENUM = 0x4000, // Declared as an enum class.
            ACC_MODULE = 0x8000, // Is a module, not a class or interface.
        };

        Class(std::string name);

        /* GET OR CREATE CLASS CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantClass "Class constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the class name.
         * @param name Class internal name (e.g. "java/lang/String").
         * @return Class constant.
         */
        ConstantClass* getOrCreateClassConstant(const std::string& name);

        /**
         * @brief Returns an existing @ref ConstantClass "Class constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param name UTF-8 constant containing the class internal name.
         * @return Class constant.
         */
        ConstantClass* getOrCreateClassConstant(ConstantUtf8Info* name);


        /* GET OR CREATE FIELDREF CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantFieldref "Fieldref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Class internal name (e.g. "java/lang/System").
         * @param fieldName Field name.
         * @param fieldDescriptor Field descriptor (e.g. "I", "Ljava/lang/String;", "[I").
         * @return Fieldref constant.
         */
        ConstantFieldref* getOrCreateFieldrefConstant(const std::string& className,
                                                      const std::string& fieldName,
                                                      const std::string& fieldDescriptor);

        /**
         * @brief Returns an existing @ref ConstantFieldref "Fieldref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Class internal name (e.g. "java/lang/System").
         * @param fieldName Field name.
         * @param fieldDescriptor Descriptor object representing a field descriptor.
         * @return Fieldref constant.
         */
        ConstantFieldref* getOrCreateFieldrefConstant(const std::string& className, const std::string& fieldName,
                                                      const Descriptor& fieldDescriptor);

        /**
         * @brief Returns an existing @ref ConstantFieldref "Fieldref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constants must have this @c Class instance as their owner.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Name-and-type constant for the field.
         * @return Fieldref constant.
         */
        ConstantFieldref* getOrCreateFieldrefConstant(ConstantClass* classConstant,
                                                      ConstantNameAndType* nameAndTypeConstant);


        /* GET OR CREATE METHODREF CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantMethodref "Methodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Class internal name (e.g. "java/lang/String").
         * @param methodName Method name (e.g. "hashCode", "&lt;init&gt;", "&lt;clinit&gt;").
         * @param methodDescriptor Method descriptor (e.g. "()I", "(I)Ljava/lang/String;").
         * @return Methodref constant.
         */
        ConstantMethodref* getOrCreateMethodrefConstant(const std::string& className,
                                                        const std::string& methodName,
                                                        const std::string& methodDescriptor);

        /**
         * @brief Returns an existing @ref ConstantMethodref "Methodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Class internal name (e.g. "java/lang/String").
         * @param methodName Method name (e.g. "hashCode", "&lt;init&gt;", "&lt;clinit&gt;").
         * @param methodDescriptor Descriptor object representing a method descriptor.
         * @return Methodref constant.
         */
        ConstantMethodref* getOrCreateMethodrefConstant(const std::string& className, const std::string& methodName,
                                                        const Descriptor& methodDescriptor);

        /**
         * @brief Returns an existing @ref ConstantMethodref "Methodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constants must have this @c Class instance as their owner.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Name-and-type constant for the method.
         * @return Methodref constant.
         */
        ConstantMethodref* getOrCreateMethodrefConstant(ConstantClass* classConstant,
                                                        ConstantNameAndType* nameAndTypeConstant);


        /* GET OR CREATE INTERFACE METHODREF CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantInterfaceMethodref "InterfaceMethodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Interface internal name (e.g. "java/lang/Runnable").
         * @param methodName Interface method name.
         * @param methodDescriptor Method descriptor (e.g. "()V").
         * @return Interface methodref constant.
         */
        ConstantInterfaceMethodref* getOrCreateInterfaceMethodrefConstant(const std::string& className,
                                                                          const std::string& methodName,
                                                                          const std::string& methodDescriptor);

        /**
         * @brief Returns an existing @ref ConstantInterfaceMethodref "InterfaceMethodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create @ref ConstantClass and @ref ConstantNameAndType entries as needed.
         * @param className Interface internal name (e.g. "java/lang/Runnable").
         * @param methodName Interface method name.
         * @param methodDescriptor Descriptor object representing a method descriptor.
         * @return Interface methodref constant.
         */
        ConstantInterfaceMethodref* getOrCreateInterfaceMethodrefConstant(
            const std::string& className, const std::string& methodName, const Descriptor& methodDescriptor);

        /**
         * @brief Returns an existing @ref ConstantInterfaceMethodref "InterfaceMethodref constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constants must have this @c Class instance as their owner.
         * @param classConstant Class constant.
         * @param nameAndTypeConstant Name-and-type constant for the interface method.
         * @return Interface methodref constant.
         */
        ConstantInterfaceMethodref* getOrCreateInterfaceMethodrefConstant(ConstantClass* classConstant,
                                                                          ConstantNameAndType* nameAndTypeConstant);


        /* GET OR CREATE STRING CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantString "String constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the string contents.
         * @param value String contents.
         * @return String constant.
         */
        ConstantString* getOrCreateStringConstant(const std::string& value);

        /**
         * @brief Returns an existing @ref ConstantString "String constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param utf8Constant UTF-8 constant containing the string contents.
         * @return String constant.
         */
        ConstantString* getOrCreateStringConstant(ConstantUtf8Info* utf8Constant);


        /* GET OR CREATE INTEGER CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantInteger "Integer constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @param value Integer value.
         * @return Integer constant.
         */
        ConstantInteger* getOrCreateIntegerConstant(int32_t value);


        /* GET OR CREATE FLOAT CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantFloat "Float constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @param value Float value.
         * @return Float constant.
         */
        ConstantFloat* getOrCreateFloatConstant(float value);


        /* GET OR CREATE LONG CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantLong "Long constant" from this class's constant pool,
         *        or creates and returns a new one.
         *
         * @param value Long value.
         * @return Long constant.
         */
        ConstantLong* getOrCreateLongConstant(int64_t value);


        /* GET OR CREATE DOUBLE CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantDouble "Double constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @param value Double value.
         * @return Double constant.
         */
        ConstantDouble* getOrCreateDoubleConstant(double value);


        /* GET OR CREATE NAME AND TYPE CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create new @ref ConstantUtf8Info entries for the name and descriptor.
         * @param name Name.
         * @param descriptor Descriptor (field descriptor like "I", or method descriptor like "(I)V").
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(const std::string& name, const std::string& descriptor);

        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the name.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param name Name.
         * @param descriptorConstant UTF-8 constant containing the descriptor.
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(const std::string& name,
                                                            ConstantUtf8Info* descriptorConstant);

        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the name.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param name Name.
         * @param descriptor Descriptor object representing a field or method descriptor.
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(const std::string& name, const Descriptor& descriptor);

        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the name.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param nameConstant UTF-8 constant containing the name.
         * @param descriptor Descriptor object representing a field or method descriptor.
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                            const Descriptor& descriptor);


        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note May create a new @ref ConstantUtf8Info entry for the descriptor.
         * @note The provided constant must have this @c Class instance as its owner.
         * @param nameConstant UTF-8 constant containing the name.
         * @param descriptor Descriptor (field descriptor like "I", or method descriptor like "(I)V").
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                            const std::string& descriptor);

        /**
         * @brief Returns an existing @ref ConstantNameAndType "Name-and-type constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @note The provided constants must have this @c Class instance as their owner.
         * @param nameConstant UTF-8 constant containing the name.
         * @param descriptorConstant UTF-8 constant containing the descriptor.
         * @return Name-and-type constant.
         */
        ConstantNameAndType* getOrCreateNameAndTypeConstant(ConstantUtf8Info* nameConstant,
                                                            ConstantUtf8Info* descriptorConstant);


        /* GET OR CREATE UTF-8 CONSTANT */

        /**
         * @brief Returns an existing @ref ConstantUtf8Info "UTF-8 constant" from this class's constant pool,
         *        or creates and returns a new one.
         * @param value UTF-8 string value (stored using the class-file UTF-8 format).
         * @return UTF-8 constant.
         */
        ConstantUtf8Info* getOrCreateUtf8Constant(const std::string& value);

        /* GET OR CREATE METHOD */

        /**
         * @brief Returns an existing @ref Method "method" with the specified name and descriptor,
         *        or creates and returns a new one.
         *
         * The method is identified by its name and descriptor within this class.
         *
         * @param name Method name (e.g. "run", "main", "&lt;init&gt;", "&lt;clinit&gt;").
         * @param descriptor Method descriptor (e.g. "()V", "([Ljava/lang/String;)V", "(I)Ljava/lang/String;").
         * @return Method instance owned by this class.
         */
        Method* getOrCreateMethod(const std::string& name, const std::string& descriptor);

        /**
         * @brief Returns an existing @ref Method "method" with the specified name and descriptor,
         *        or creates and returns a new one.
         *
         * The method is identified by its name and descriptor within this class.
         *
         * @note The provided constants must have this @c Class instance as their owner.
         * @param name UTF-8 constant containing the method name.
         * @param descriptor UTF-8 constant containing the method descriptor.
         * @return Method instance owned by this class.
         */
        Method* getOrCreateMethod(ConstantUtf8Info* name, ConstantUtf8Info* descriptor);

        std::span<Constant*> constants();

    private:
        /**
         * @brief Add a constant to the constant pool.
         * Add a constant to constant pool and set index to the constant.
         * @param constant New constant.
         */
        void addNewConstant(Constant* constant);

        void toBinary(std::ostream& os) const;

        std::vector<Constant*> constants_{};
        uint16_t nextCpIndex = 1; // 0 index is not available for writing
        std::set<AccessFlags> accessFlags_{};
        Constant* thisClassConstant_ = nullptr;
        Constant* superClassConstant_ = nullptr;
        std::set<Constant*> interfacesConstant_{};
        std::set<Field*> fields_;
        std::set<Method*> methods_;
        std::set<Attribute*> attributes_;
    };
}
#endif //JVM__CLASS_H
