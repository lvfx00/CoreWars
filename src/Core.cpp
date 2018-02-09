#include "Core.h"

Core::Core(std::size_t coreSize,
           std::size_t readDist,
           std::size_t writeDist,
           const PureInstruction &defaultInstruction) :
        coreMemory_(coreSize),
        CORE_SIZE(coreSize),
        READ_DISTANCE(readDist),
        WRITE_DISTANCE(writeDist) {
    for (std::size_t i = 0; i != CORE_SIZE; ++i) {
        loadInstr(defaultInstruction, i);
    }
}

Instruction *Core::operator[](std::size_t index) {
    return coreMemory_[index % CORE_SIZE].get();
}


std::size_t Core::fold(std::size_t offset, std::size_t limit) const {
    std::size_t result = offset % limit;
    if (result > limit / 2)
        result += CORE_SIZE - limit;
    return result;
}


Address Core::numberToAddress(Number number) const {
    while (number < 0) {
        number += CORE_SIZE;
    }
    number %= CORE_SIZE;
    return (std::size_t) (number);
}


void Core::loadInstr(const PureInstruction &pureInstr, std::size_t index) {
    if (index > CORE_SIZE - 1) {
        throw std::out_of_range("Core overflow");
    }
    coreMemory_[index].reset(Factory::getInstance()->create(
            pureInstr.opcode,
            InstructionData(
                    pureInstr.modifier,
                    pureInstr.Amode,
                    numberToAddress(pureInstr.Anumber),
                    pureInstr.Bmode,
                    numberToAddress(pureInstr.Bnumber))));
}

void Core::reset(std::size_t index, Instruction *ptr) {
    coreMemory_[index % CORE_SIZE].reset(ptr);
}

void Core::print() const {
    for (std::size_t i = 0; i != CORE_SIZE; ++i) {
        std::cout << i << ":   ";
        coreMemory_[i]->print();
    }
}

