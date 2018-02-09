#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_JMZ : public Instruction {
public:
    explicit Instr_JMZ(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext &context) override {
        setContext(context);
        switch (getModifier()) {
            case A:
            case BA:
                if (context.getBPtrForRead()->getAaddress() == 0)
                    context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            case B:
            case AB:
                if (context.getBPtrForRead()->getBaddress() == 0)
                    context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            case F:
            case X:
            case I:
                if ((context.getBPtrForRead()->getAaddress() == 0) && (context.getBPtrForRead()->getBaddress() == 0))
                    context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            default:
                throw std::invalid_argument("Invalid modifier!!!");
        }
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("JMZ");
    }


    void print() const override {
        std::cout << "JMZ";
        Instruction::print();
    }
};

namespace {
    Instruction *create_JMZ(const InstructionData &idata) {
        return new Instr_JMZ(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("JMZ", create_JMZ);
}
