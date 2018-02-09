#include "../Instruction.h"
#include "../InstructionContext.h"

class Instr_MUL : public Instruction {
public:
    explicit Instr_MUL(const InstructionData &idata) : Instruction(idata) {}


    void exec(InstructionContext& context) override {
        setContext(context);

        switch (getModifier()) {
            case A:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getAaddress() * context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                break;

            case B:
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getBaddress() * context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case AB:
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getAaddress() * context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case BA:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getBaddress() * context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                break;

            case F:
            case I:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getAaddress() * context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getBaddress() * context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case X:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getBaddress() * context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getAaddress() * context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            default:
                throw std::invalid_argument("Invalid modifier!!!");
        }

        context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("MUL");
    }


    void print() const override {
        std::cout << "MUL";
        Instruction::print();
    }
};

namespace {
    Instruction *create_MUL(const InstructionData &idata) {
        return new Instr_MUL(idata);
    }


    bool b = Factory::getInstance()->
            registerFunction("MUL", create_MUL);
}
