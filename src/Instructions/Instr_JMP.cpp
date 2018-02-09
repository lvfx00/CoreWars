#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_JMP : public Instruction {
public:
    explicit Instr_JMP(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext &context) override {
        setContext(context);
        context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("JMP");
    }


    void print() const override {
        std::cout << "JMP";
        Instruction::print();
    }
};


namespace {
    Instruction *create_JMP(const InstructionData &idata) {
        return new Instr_JMP(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("JMP", create_JMP);
}
