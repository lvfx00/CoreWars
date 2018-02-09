#pragma once

#include "Warrior.h"
#include "Core.h"
#include "Instruction.h"

class InstructionContext {
public:
    InstructionContext(Core *c, Warrior *w) :
            currentWarrior_(w),
            core_(c),
            PC(w->taskQueue.front()) {}

    Instruction *getAPtrForRead() {
        return (*core_)[PC + core_->fold(RPA, core_->READ_DISTANCE)];
    }

    Instruction *getAPtrForWrite() {
        return (*core_)[PC + core_->fold(WPA, core_->WRITE_DISTANCE)];
    }

    Instruction *getBPtrForRead() {
        return (*core_)[PC + core_->fold(RPB, core_->READ_DISTANCE)];
    }

    Instruction *getBPtrForWrite() {
        return (*core_)[PC + core_->fold(WPB, core_->WRITE_DISTANCE)];
    }

    void pushWarriorQueue(Address a) {
        currentWarrior_->taskQueue.push(a % core_->CORE_SIZE);
    }

    void popWarriorQueue() {
        currentWarrior_->taskQueue.pop();
    }

    std::size_t getCoreSize() const {
        return core_->CORE_SIZE;
    }

    void reset(std::size_t index, Instruction *ptr) {
        core_->reset(index, ptr);
    }

    Address PC;
    Address WPA;
    Address RPA;
    Address WPB;
    Address RPB;

private:
    Warrior *currentWarrior_;
    Core *core_;
};

