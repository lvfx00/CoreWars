#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_NOP : public Instruction {
public:
    explicit Instr_NOP(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext &context) override {
        setContext(context);

        context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("NOP");
    }


    void print() const override {
        std::cout << "NOP";
        Instruction::print();
    }
};

namespace {
    Instruction *create_NOP(const InstructionData &idata) {
        return new Instr_NOP(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("NOP", create_NOP);
}
