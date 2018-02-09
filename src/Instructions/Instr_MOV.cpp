#include "../Instruction.h"
#include "../InstructionContext.h"

class Instr_MOV : public Instruction {
public:
    explicit Instr_MOV(const InstructionData &idata) : Instruction(idata) {}

    void exec(InstructionContext &context) override {
        setContext(context);

        switch (getModifier()) {
            case A:
                context.getBPtrForWrite()->setAaddress(context.getAPtrForRead()->getAaddress());
                break;
            case B:
                context.getBPtrForWrite()->setBaddress(context.getAPtrForRead()->getBaddress());
                break;
            case AB:
                context.getBPtrForWrite()->setBaddress(context.getAPtrForRead()->getAaddress());
                break;
            case BA:
                context.getBPtrForWrite()->setAaddress(context.getAPtrForRead()->getBaddress());
                break;
            case F:
                context.getBPtrForWrite()->setAaddress(context.getAPtrForRead()->getAaddress());
                context.getBPtrForWrite()->setBaddress(context.getAPtrForRead()->getBaddress());
                break;
            case X:
                context.getBPtrForWrite()->setBaddress(context.getAPtrForRead()->getAaddress());
                context.getBPtrForWrite()->setAaddress(context.getAPtrForRead()->getBaddress());
                break;
            case I: {
                context.reset(context.PC + context.WPB,
                              Factory::getInstance()->create(context.getAPtrForRead()->get_opc(),
                                                              context.getAPtrForRead()->getData()));
                break;
            }
            default:
                throw std::invalid_argument("Invalid modifier!!!");
                break;
        }
        context.pushWarriorQueue((context.PC + 1) % context.getCoreSize());
        context.popWarriorQueue();
    }


    std::string get_opc() const override {
        return std::string("MOV");
    }


    void print() const override {
        std::cout << "MOV";
        Instruction::print();
    }
};

namespace {
    Instruction *create_MOV(const InstructionData &idata) {
        return new Instr_MOV(idata);
    }

    bool b = Factory::getInstance()->
            registerFunction("MOV", create_MOV);
}
