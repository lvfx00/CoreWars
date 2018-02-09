#include "Parser.h"

WarData Parser::parseProgramFile(std::ifstream &inputFile) const {
    WarData warData;
    int lineNumber = 1;
    for (std::string line; std::getline(inputFile, line); ++lineNumber) {
        if (line[0] == ';') {
            continue;
        }
        std::string opcodePart = line.substr(0, 3);
        if (opcodePart == "ORG") {
            int startInstr;
            unsigned long semicolonPos;
            if ((semicolonPos = line.find(';')) == std::string::npos) {
                try {
                    startInstr = std::stoi(line.substr(3));
                } catch (const std::invalid_argument &) {
                    throw (std::invalid_argument(
                            "Line " + std::to_string(lineNumber) + ": " + "Invalid starting instruction number!"));
                }
            } else {
                try {
                    startInstr = std::stoi(line.substr(3, semicolonPos - 3));
                } catch (const std::invalid_argument &) {
                    throw (std::invalid_argument(
                            "Line " + std::to_string(lineNumber) + ": " + "Invalid starting instruction number!"));
                }
            }
            if (startInstr < 1)
                throw (std::invalid_argument(
                        "Line " + std::to_string(lineNumber) + ": " + "Starting instruction number < 1!"));
            warData.startingInstructionNumber = static_cast<unsigned>(startInstr);
        } else {
            try {
                warData.instructionList.push_back(parseInstruction(line));
            } catch (const std::invalid_argument &a) {
                throw std::invalid_argument("Line " + std::to_string(lineNumber) + ": " + a.what());
            }
        }
    }
    return warData;
}

std::unique_ptr<PureInstruction> Parser::parseInstruction(const std::string &line) const {
    std::string opcodePart = line.substr(0, 3);
    if (opcodePart != "ADD" &&
        opcodePart != "CMP" &&
        opcodePart != "DAT" &&
        opcodePart != "DIV" &&
        opcodePart != "DJN" &&
        opcodePart != "JMN" &&
        opcodePart != "JMP" &&
        opcodePart != "JMZ" &&
        opcodePart != "MOD" &&
        opcodePart != "MOV" &&
        opcodePart != "MUL" &&
        opcodePart != "NOP" &&
        opcodePart != "SLT" &&
        opcodePart != "SNE" &&
        opcodePart != "SPL" &&
        opcodePart != "SUB")
        throw (std::invalid_argument("Invalid opcode!"));

    if (line[3] != '.')
        throw (std::invalid_argument("Dot after opcode not found!"));

    Modifier modif;
    unsigned long spacePos;
    if ((spacePos = line.find(' ', 0)) == std::string::npos)
        throw (std::invalid_argument("Space after modifier not found!"));
    try {
        modif = str_to_modif(line.substr(4, spacePos - 4));
    } catch (const std::exception &) {
        throw (std::invalid_argument("Invalid modifier!"));
    }

    Mode Amode;
    unsigned long commaPos;
    if ((commaPos = line.find(',')) == std::string::npos)
        throw (std::invalid_argument("Comma after AValue not found!"));
    if (line[commaPos + 1] != ' ')
        throw (std::invalid_argument("Space after AValue not found!"));

    try {
        Amode = str_to_mode(line.substr(spacePos + 1, 1));
    } catch (const std::exception &) {
        throw (std::invalid_argument("Invalid Amode!"));
    }

    Number Anumber;
    try {
        Anumber = std::stoi(line.substr(spacePos + 2, commaPos - (spacePos + 2)));
    } catch (const std::invalid_argument &) {
        throw (std::invalid_argument("Invalid Anumber!"));
    }

    Mode Bmode;
    try {
        Bmode = str_to_mode(line.substr(commaPos + 2, 1));
    } catch (const std::exception &) {
        throw (std::invalid_argument("Invalid Bmode!"));
    }

    Number Bnumber;
    unsigned long semicolonPos;
    if ((semicolonPos = line.find(';')) == std::string::npos) {
        try {
            Bnumber = std::stoi(line.substr(commaPos + 3));
        } catch (const std::invalid_argument &) {
            throw (std::invalid_argument("Invalid Bnumber!"));
        }
    } else {
        try {
            Bnumber = std::stoi(line.substr(commaPos + 3, semicolonPos - (commaPos + 3)));
        } catch (const std::invalid_argument &) {
            throw (std::invalid_argument("Invalid Bnumber!"));
        }
    }

    return std::move(std::unique_ptr<PureInstruction>(
                         new  PureInstruction(opcodePart, modif, Amode, Anumber, Bmode, Bnumber)));
}
