#include "jvm/instruction.h"

#include <ostream>

using namespace jvm;

Instruction::Command Instruction::getCommandCode() const
{
    return command_;
}

uint8_t Instruction::getByteSize() const
{
    return sizeof(command_);
}

void Instruction::toBinary(std::ostream& os) const
{
    const auto byte = static_cast<char>(command_);
    os.put(byte);

    if (!os)
    {
        throw std::runtime_error("Failed to write instruction opcode to stream");
    }
}

void Instruction::setIndex(uint16_t index)
{
    index_ = index;
    isIndexSet_ = true;
}

void Instruction::resetIndex()
{
    isIndexSet_ = false;
}

AttributeCode* Instruction::getAttributeCodeOwner() const
{
    return attributeCodeOwner_;
}

Instruction::Instruction(AttributeCode* attributeCode, Command command) : command_(command),
                                                                          attributeCodeOwner_(attributeCode)
{
}

void Instruction::setCommand(Command newCommand)
{
    command_ = newCommand;
}

uint16_t Instruction::calculateShift(Instruction* target) const
{
    if (!isIndexSet()) { throw std::logic_error("Index for source instruction not set yet."); }
    if (!target->isIndexSet()) { throw std::logic_error("Index for target instruction not set yet."); }

    uint16_t from = getIndex();
    uint16_t to = target->getIndex();

    return to - from;
}

bool Instruction::isIndexSet() const
{
    return isIndexSet_;
}

uint16_t Instruction::getIndex() const
{
    return index_;
}


std::ostream& operator<<(std::ostream& os, const Instruction& instruction)
{
    instruction.toBinary(os);
    return os;
}
