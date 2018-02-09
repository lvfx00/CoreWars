#pragma once

#include <string>
#include <sstream>
#include <iostream>

class InstructionContext;

using Number = int;
using Address = std::size_t;

enum Modifier {
    A,
    B,
    AB,
    BA,
    F,
    X,
    I
};

Modifier str_to_modif(const std::string &);

std::string modif_to_str(Modifier);

enum Mode {
    IMMEDIATE,
    DIRECT,
    A_INDIRECT,
    B_INDIRECT,
    A_DECREMENT,
    B_DECREMENT,
    A_INCREMENT,
    B_INCREMENT,
};

Mode str_to_mode(const std::string &);

std::string mode_to_str(Mode);


struct InstructionData {
    InstructionData(Modifier modif,
                    Mode amod,
                    Address aadr,
                    Mode bmod,
                    Address badr) :
            modifier(modif),
            Amode(amod),
            Aaddress(aadr),
            Bmode(bmod),
            Baddress(badr) {}

    Modifier modifier;
    Mode Amode;
    Address Aaddress; // absolute address for certain core
    Mode Bmode;
    Address Baddress;
};


class Instruction {
public:
    explicit Instruction(const InstructionData &instr_data) : data(instr_data) {}

    void setContext(InstructionContext &context) const;

    virtual void exec(InstructionContext &context) = 0;

    virtual std::string get_opc() const = 0;

    virtual void print() const;

    Modifier getModifier() const { return data.modifier; }

    Mode getAMode() const { return data.Amode; }

    Mode getBMode() const { return data.Bmode; }

    Address getAaddress() const { return data.Aaddress; }

    Address getBaddress() const { return data.Baddress; }

    InstructionData getData() const {return data;}

    void setModifier(Modifier m) { data.modifier = m; }

    void setAmode(Mode m) { data.Amode = m; }

    void setBmode(Mode m) { data.Bmode = m; }

    void setAaddress(Address a) { data.Aaddress = a; }

    void setBaddress(Address a) { data.Baddress = a; }

    void setData(const InstructionData& d) {data = d;}


private:
    InstructionData data;
};

struct PureInstruction {
    explicit PureInstruction(
            const std::string &opc = "DAT",
            Modifier modif = F,
            Mode amod = IMMEDIATE,
            Number anum = 0,
            Mode bmod = IMMEDIATE,
            Number bnum = 0) :
            opcode(opc),
            modifier(modif),
            Amode(amod),
            Anumber(anum),
            Bmode(bmod),
            Bnumber(bnum) {}

    void print(std::ostringstream& out) const {
        out << opcode + "." << modif_to_str(modifier) + " "
            << mode_to_str(Amode) << std::to_string(Anumber)
            << " " + mode_to_str(Bmode) << std::to_string(Bnumber) << "\n";
    }

    std::string opcode;
    Modifier modifier;
    Mode Amode;
    Number Anumber; // relative address for any core
    Mode Bmode;
    Number Bnumber;
};
