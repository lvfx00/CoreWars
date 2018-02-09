#include "Instruction.h"
#include "InstructionContext.h"

void Instruction::setContext(InstructionContext &context) const {
    Instruction* PIP;

    if (data.Amode == IMMEDIATE) {
        context.RPA = 0;
        context.WPA = 0;
    } else {
        context.RPA = data.Aaddress;
        context.WPA = data.Aaddress;

        if (data.Amode == A_INDIRECT
            || data.Amode == A_DECREMENT
            || data.Amode == A_INCREMENT) {

            if (data.Amode == A_DECREMENT)
                context.getAPtrForWrite()->data.Aaddress =
                        (context.getAPtrForWrite()->data.Aaddress + context.getCoreSize() - 1) % context.getCoreSize();

            if (data.Amode == A_INCREMENT)
                PIP = context.getAPtrForWrite();

            context.RPA = context.RPA + context.getAPtrForRead()->data.Aaddress;
            context.WPA = context.WPA + context.getAPtrForWrite()->data.Aaddress;
        }

        if (data.Amode == B_INDIRECT
            || data.Amode == B_DECREMENT
            || data.Amode == B_INCREMENT) {

            if (data.Amode == B_DECREMENT)
                context.getAPtrForWrite()->data.Baddress =
                        (context.getAPtrForWrite()->data.Baddress + context.getCoreSize() - 1) % context.getCoreSize();

            if (data.Amode == B_INCREMENT)
                PIP = context.getAPtrForWrite();

            context.RPA = context.RPA + context.getAPtrForRead()->data.Baddress;
            context.WPA = context.WPA + context.getAPtrForWrite()->data.Baddress;
        }

        if (data.Amode == A_INCREMENT)
            PIP->data.Aaddress = (PIP->data.Aaddress + 1) % context.getCoreSize();
        else if (data.Amode == B_INCREMENT)
            PIP->data.Baddress = (PIP->data.Baddress + 1) % context.getCoreSize();
    }

    if (data.Bmode == IMMEDIATE) {
        context.RPB = 0;
        context.WPB = 0;
    } else {
        context.RPB = data.Baddress;
        context.WPB = data.Baddress;

        if (data.Bmode == A_INDIRECT
            || data.Bmode == A_DECREMENT
            || data.Bmode == A_INCREMENT) {

            if (data.Bmode == A_DECREMENT)
                context.getBPtrForWrite()->data.Aaddress =
                        (context.getBPtrForWrite()->data.Aaddress + context.getCoreSize() - 1) % context.getCoreSize();

            if (data.Bmode == A_INCREMENT)
                PIP = context.getBPtrForWrite();

            context.RPB = context.RPB + context.getBPtrForRead()->data.Aaddress;
            context.WPB = context.WPB + context.getBPtrForWrite()->data.Aaddress;
        }

        if (data.Bmode == B_INDIRECT
            || data.Bmode == B_DECREMENT
            || data.Bmode == B_INCREMENT) {

            if (data.Bmode == B_DECREMENT)
                context.getBPtrForWrite()->data.Baddress =
                        (context.getBPtrForWrite()->data.Baddress + context.getCoreSize() - 1) % context.getCoreSize();

            if (data.Bmode == B_INCREMENT)
                PIP = context.getBPtrForWrite();

            context.RPB = context.RPB + context.getBPtrForRead()->data.Baddress;
            context.WPB = context.WPB + context.getBPtrForWrite()->data.Baddress;
        }

        if (data.Bmode == A_INCREMENT)
            PIP->data.Aaddress = (PIP->data.Aaddress + 1) % context.getCoreSize();
        else if (data.Bmode == B_INCREMENT)
            PIP->data.Baddress = (PIP->data.Baddress + 1) % context.getCoreSize();
    }
}


void Instruction::print() const {
    std::cout << "." << modif_to_str(data.modifier) << " "
              << mode_to_str(data.Amode) << data.Aaddress << " "
              << mode_to_str(data.Bmode) << data.Baddress << std::endl;

}


Modifier str_to_modif(const std::string &str) {
    if (str == "A") {
        return A;
    } else if (str == "B") {
        return B;
    } else if (str == "AB") {
        return AB;
    } else if (str == "BA") {
        return BA;
    } else if (str == "F") {
        return F;
    } else if (str == "X") {
        return X;
    } else if (str == "I") {
        return I;
    } else {
        throw std::exception();
    }
}


std::string modif_to_str(Modifier modif) {
    switch (modif) {
        case A:
            return std::string("A");
        case B:
            return std::string("B");
        case AB:
            return std::string("AB");
        case BA:
            return std::string("BA");
        case F:
            return std::string("F");
        case X:
            return std::string("X");
        case I:
            return std::string("I");
        default:
            throw std::exception();
    }
}


Mode str_to_mode(const std::string &str) {
    if (str == "#") {
        return IMMEDIATE;
    } else if (str == "$") {
        return DIRECT;
    } else if (str == "@") {
        return A_INDIRECT;
    } else if (str == "*") {
        return B_INDIRECT;
    } else if (str == "<") {
        return A_DECREMENT;
    } else if (str == "{") {
        return B_DECREMENT;
    } else if (str == ">") {
        return A_INCREMENT;
    } else if (str == "}") {
        return B_INCREMENT;
    } else {
        throw std::exception();
    }
}

std::string mode_to_str(Mode mode) {
    switch (mode) {
        case IMMEDIATE:
            return std::string("#");
        case DIRECT:
            return std::string("$");
        case A_INDIRECT:
            return std::string("@");
        case B_INDIRECT:
            return std::string("*");
        case A_DECREMENT:
            return std::string("<");
        case B_DECREMENT:
            return std::string("{");
        case A_INCREMENT:
            return std::string(">");
        case B_INCREMENT:
            return std::string("}");
        default:
            throw std::exception();
    }
}
