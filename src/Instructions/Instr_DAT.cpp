#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_DAT : public Instruction {
public:
    explicit Instr_DAT(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext &context) override {
        setContext(context);
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("DAT");
    }


    void print() const override {
        std::cout << "DAT";
        Instruction::print();
    }
};

namespace {
    Instruction *create_DAT(const InstructionData &idata) {
        return new Instr_DAT(idata);
    }


    bool b = Factory::getInstance()->
            registerFunction("DAT", create_DAT);
}
