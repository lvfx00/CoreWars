#pragma once

#include "Instruction.h"
#include <queue>

class Warrior {
public:
    Warrior(const std::string &name, Address first) : warName(name), firstInstructionAddress(first) {}

    std::queue<Address> taskQueue;
    std::string warName;
    Address firstInstructionAddress;
};

