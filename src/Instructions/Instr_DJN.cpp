#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_DJN : public Instruction {
public:
    explicit Instr_DJN(const InstructionData &idata) : Instruction(idata) {}

    void exec(InstructionContext &context) override {
        setContext(context);
        switch (getModifier()) {
            case A:
            case BA:
                context.getBPtrForWrite()->setAaddress(
                        (context.getBPtrForWrite()->getAaddress() + context.getCoreSize() - 1) % context.getCoreSize());

                if (context.getBPtrForWrite()->getAaddress() != 0)
                    context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case B:
            case AB:
                context.getBPtrForWrite()->setBaddress(
                        (context.getBPtrForWrite()->getBaddress() + context.getCoreSize() - 1) % context.getCoreSize());

                if (context.getBPtrForWrite()->getBaddress() != 0)
                    context.pushWarriorQueue((context.PC + context.RPA) % context.getCoreSize());
                else
                    context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
                break;

            case F:
            case X:
            case I:
                context.getBPtrForWrite()->setAaddress(
                        (context.getBPtrForWrite()->getAaddress() + context.getCoreSize() - 1) % context.getCoreSize());
                context.getBPtrForWrite()->setBaddress(
                        (context.getBPtrForWrite()->getBaddress() + context.getCoreSize() - 1) % context.getCoreSize());

                if (context.getBPtrForWrite()->getAaddress() != 0 || context.getBPtrForWrite()->getBaddress() != 0)
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
        return std::string("DJN");
    }


    void print() const override {
        std::cout << "DJN";
        Instruction::print();
    }
};

namespace {
    Instruction *create_DJN(const InstructionData &idata) {
        return new Instr_DJN(idata);
    }


    bool b = Factory::getInstance()->
            registerFunction("DJN", create_DJN);
}

