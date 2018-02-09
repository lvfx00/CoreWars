#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_SUB : public Instruction {
public:
    explicit Instr_SUB(const InstructionData &idata) : Instruction(idata) {}


    // TODO MUL нужно не просто брать остаток, может ведь получиться отриц число
    void exec(InstructionContext& context) override {
        setContext(context);

        switch (getModifier()) {
            case A:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getAaddress() - context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                break;

            case B:
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getBaddress() - context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case AB:
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getAaddress() - context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case BA:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getBaddress() - context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                break;

            case F:
            case I:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getAaddress() - context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getBaddress() - context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            case X:
                context.getBPtrForWrite()->setAaddress(
                        (context.getAPtrForRead()->getBaddress() - context.getBPtrForRead()->getAaddress()) %
                        context.getCoreSize());
                context.getBPtrForWrite()->setBaddress(
                        (context.getAPtrForRead()->getAaddress() - context.getBPtrForRead()->getBaddress()) %
                        context.getCoreSize());
                break;

            default:
                throw std::invalid_argument("Invalid modifier!!!");
        }

        context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("SUB");
    }


    void print() const override {
        std::cout << "SUB";
        Instruction::print();
    }
};

namespace {
    Instruction *create_SUB(const InstructionData &idata) {
        return new Instr_SUB(idata);
    }


    bool b = Factory::getInstance()->
            registerFunction("SUB", create_SUB);
}
