#include "../Instruction.h"
#include "../InstructionContext.h"
#include "../Factory.h"


class Instr_SPL : public Instruction {
public:
    explicit Instr_SPL(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext& context) override {
        setContext(context);

        context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
        context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("SPL");
    }


    void print() const override {
        std::cout << "SPL";
        Instruction::print();
    }
};

namespace {
    Instruction *create_SPL(const InstructionData &idata) {
        return new Instr_SPL(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("SPL", create_SPL);
}
