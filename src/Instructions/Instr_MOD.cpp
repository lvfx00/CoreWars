#include "../Instruction.h"
#include "../InstructionContext.h"


class Instr_MOD : public Instruction {
public:
    explicit Instr_MOD(const InstructionData &idata) : Instruction(idata) {}

    void exec(InstructionContext &context) override {
        setContext(context);

        bool rem_proc = false;
        switch (getModifier()) {
            case A:
                if (context.getAPtrForRead()->getAaddress() != 0)
                    context.getBPtrForWrite()->setAaddress(
                            context.getBPtrForRead()->getAaddress() % context.getAPtrForRead()->getAaddress());
                else
                    rem_proc = true;
                break;
            case B:
                if (context.getAPtrForRead()->getBaddress() != 0)
                    context.getBPtrForWrite()->setBaddress(
                            context.getBPtrForRead()->getBaddress() % context.getAPtrForRead()->getBaddress());
                else
                    rem_proc = true;
                break;
            case AB:
                if (context.getAPtrForRead()->getAaddress() != 0)
                    context.getBPtrForWrite()->setBaddress(
                            context.getBPtrForRead()->getBaddress() % context.getAPtrForRead()->getAaddress());
                else
                    rem_proc = true;
                break;
            case BA:
                if (context.getAPtrForRead()->getBaddress() != 0)
                    context.getBPtrForWrite()->setAaddress(
                            context.getBPtrForRead()->getAaddress() % context.getAPtrForRead()->getBaddress());
                else
                    rem_proc = true;
                break;
            case F:
            case I:
                if (context.getAPtrForRead()->getAaddress() != 0)
                    context.getBPtrForWrite()->setAaddress(
                            context.getBPtrForRead()->getAaddress() % context.getAPtrForRead()->getAaddress());
                if (context.getAPtrForRead()->getBaddress() != 0)
                    context.getBPtrForWrite()->setBaddress(
                            context.getBPtrForRead()->getBaddress() % context.getAPtrForRead()->getBaddress());

                if (context.getAPtrForRead()->getAaddress() == 0 || context.getAPtrForRead()->getBaddress() == 0)
                    rem_proc = true;
                break;
            case X:
                if (context.getAPtrForRead()->getAaddress() != 0)
                    context.getBPtrForWrite()->setBaddress(
                            context.getBPtrForRead()->getBaddress() % context.getAPtrForRead()->getAaddress());
                if (context.getAPtrForRead()->getBaddress() != 0)
                    context.getBPtrForWrite()->setAaddress(
                            context.getBPtrForRead()->getAaddress() % context.getAPtrForRead()->getBaddress());

                if (context.getAPtrForRead()->getAaddress() == 0 || context.getAPtrForRead()->getBaddress() == 0)
                    rem_proc = true;
                break;

            default:
                throw std::invalid_argument("Invalid modifier!!!");
        }
        if (!rem_proc)
            context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("MOD");
    }


    void print() const override {
        std::cout << "MOD";
        Instruction::print();
    }
};

namespace {
    Instruction *create_MOD(const InstructionData &idata) {
        return new Instr_MOD(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("MOD", create_MOD);
}
