#include <iostream>
#include <fstream>
#include "src/Mars.h"
#include "src/Parser.h"

int main() {
    std::string filename("dwarf.redcode");

    std::ifstream ifs;
    WarData warData1;
    WarData warData2;

    ifs.open(filename);
    try {
        warData1 = Parser::getInstance()->parseProgramFile(ifs);
        warData1.warName = "111";
        warData1.print(std::cout);
    } catch (const std::invalid_argument& a) {
        std::cout << "Unable to parse file: " << std::endl;
        std::cout <<  a.what();
    }
    ifs.close();

    ifs.open(filename);
    try {
        warData2 = Parser::getInstance()->parseProgramFile(ifs);
        warData2.warName = "222";
        warData2.print(std::cout);
    } catch (const std::invalid_argument& a) {
        std::cout << "Unable to parse file: " << std::endl;
        std::cout <<  a.what();
    }
    ifs.close();

    GameSettings a;

    a.warriorNumber = 2;
    a.maxLength = 300;
    a.maxProcesses = 64;
    a.maxCycles = 100000;
    a.minDistance = 300;
    a.separation = 301;
    a.isRandomSeparation = false;

    a.coreSize = 8192;
    a.readDistantion = 8192;
    a.writeDistantion = 8192;
    a.defaultInstriction = PureInstruction("DAT", F, IMMEDIATE, 0, IMMEDIATE, 0);

    a.warData.emplace_back(std::move(warData1));
    a.warData.emplace_back(std::move(warData2));


    Mars m(a);
    m.startGame();
    while(m.getStatus() == Mars::In_Process) {
        m.execTask();
    }
    if(m.getStatus() == Mars::Has_Winner) {
        std::cout << "The winner is: " << m.getWinnerName() << std::endl;
    } else {
        std::cout << "Tie!" << std::endl;
    }
    m.getCore().print();
    return 0;
}
