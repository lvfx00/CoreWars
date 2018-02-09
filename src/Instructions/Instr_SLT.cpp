#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_SLT : public Instruction {
public:
    explicit Instr_SLT(const InstructionData &idata) : Instruction(idata) {}

    void exec(InstructionContext &context) override {
        setContext(context);

        switch (getModifier()) {
            case A:
                if (context.getAPtrForRead()->getAaddress() < context.getBPtrForRead()->getAaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case B:
                if (context.getAPtrForRead()->getBaddress() < context.getBPtrForRead()->getBaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case AB:
                if (context.getAPtrForRead()->getAaddress() < context.getBPtrForRead()->getBaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case BA:
                if (context.getAPtrForRead()->getBaddress() < context.getBPtrForRead()->getAaddress())
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case F:
            case I:
                if ((context.getAPtrForRead()->getAaddress() < context.getBPtrForRead()->getAaddress()) &&
                    (context.getAPtrForRead()->getBaddress() < context.getBPtrForRead()->getBaddress()))
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            case X:
                if ((context.getAPtrForRead()->getBaddress() < context.getBPtrForRead()->getAaddress()) &&
                    (context.getAPtrForRead()->getAaddress() < context.getBPtrForRead()->getBaddress()))
                    context.pushWarriorQueue((context.PC + 2) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;
            default:
                throw std::invalid_argument("Invalid modifier!!!");
                break;
        }
        context.popWarriorQueue();
    }

    std::string get_opc() const override {
        return std::string("SLT");
    }


    void print() const override {
        std::cout << "SLT";
        Instruction::print();
    }
};

namespace {
    Instruction *create_SLT(const InstructionData &idata) {
        return new Instr_SLT(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("SLT", create_SLT);
}
