#pragma once

#include "Instruction.h"
#include "Factory.h"
#include <memory>
#include <vector>

class Core {
public:
    Core(std::size_t coreSize,
         std::size_t readDist,
         std::size_t writeDist,
         const PureInstruction &defaultInstruction);

    Instruction *operator[](std::size_t index);

    void reset(std::size_t index, Instruction *newInstr);

    std::size_t fold(std::size_t offset, std::size_t limit) const;

    Address numberToAddress(Number number) const;

    void loadInstr(const PureInstruction &pureInstr, std::size_t index);

    void print() const;

    const std::size_t CORE_SIZE;
    const std::size_t READ_DISTANCE;
    const std::size_t WRITE_DISTANCE;

private:
    std::vector<std::unique_ptr<Instruction>> coreMemory_;
};
