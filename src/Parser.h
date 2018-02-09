#pragma once

#include <fstream>
#include "Mars.h"


class Parser {
public:
    static Parser* getInstance() {
        static  Parser p;
        return &p;
    }

    WarData parseProgramFile(std::ifstream &input_file) const;

    std::unique_ptr<PureInstruction> parseInstruction(const std::string &line) const;

private:
    Parser() = default;
};
