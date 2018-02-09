#pragma once

#include <vector>
#include <list>
#include <sstream>
#include "Instruction.h"
#include "Core.h"
#include "Warrior.h"

struct WarData {
    explicit WarData(unsigned n = 1, const std::string& name = std::string("Untitled"))
        : startingInstructionNumber(n), warName(name) {}

    void print(std::ostringstream& out) const {
        out << "Warrior name: " << warName << "\n";
        out << "Starting instruction number: " << startingInstructionNumber << "\n";
        for (auto &it : instructionList) {
            it->print(out);
        }
    }

    unsigned startingInstructionNumber;
    std::list<std::unique_ptr<PureInstruction>> instructionList;
    std::string warName;
};

struct GameSettings
{
    void print(std::ostringstream& out) const {
        out << "Warrior Number: " << warriorNumber << "\n";
        out << "Max Length: " << maxLength << "\n";
        out << "Max Processes: " << maxProcesses << "\n";
        out << "Max Cycles: " << maxCycles << "\n";
        out << "Min Distance: " << minDistance << "\n";
        out << "Separation: " << ((isRandomSeparation) ? std::string("random") : std::to_string(separation)) << "\n";
        out << "Core Size: " << coreSize << "\n";
        out << "Read Distantion: " << readDistantion << "\n";
        out << "Write Distantion: " << writeDistantion << "\n";
        out << "Default Instruction: ";
        defaultInstriction.print(out);

        out << "\n";

        for(auto &it : warData) {
            it.print(out);
            out << "\n";
        }
    }

    unsigned warriorNumber;
    unsigned maxLength;
    unsigned maxProcesses;
    unsigned maxCycles;
    std::size_t minDistance;
    std::size_t separation;
    bool isRandomSeparation;

    std::size_t coreSize;
    std::size_t readDistantion;
    std::size_t writeDistantion;
    PureInstruction defaultInstriction;

    std::vector<WarData> warData;
};


class Mars {
public:
    enum GameStatus {Not_Started, In_Process, Has_Winner, Tie};

    explicit Mars(const GameSettings& gs) :
            WAR_NUM(gs.warriorNumber),
            MAX_LENGTH(gs.maxLength),
            MAX_PROCESSES(gs.maxProcesses),
            MAX_CYCLES(gs.maxCycles),
            MIN_DISTANCE(gs.minDistance),
            SEPARATION(gs.separation),
            SEP_RAND(gs.isRandomSeparation),
            core(gs.coreSize, gs.readDistantion, gs.writeDistantion, gs.defaultInstriction),
            cyclesPassed(0),
            gameStatus(Not_Started)
    {
        for(unsigned i = 0; i < WAR_NUM; ++i) {
            loadWarrior(gs.warData[i]);
        }
    }

    void loadWarrior(const WarData &warData);

    void startGame();

    void execTask();

    GameStatus getStatus() const;

    std::string getWinnerName() const;

    const Core *getCore() const;

    const unsigned WAR_NUM;
    const unsigned MAX_LENGTH;
    const unsigned MAX_PROCESSES;
    const unsigned MAX_CYCLES;
    const std::size_t MIN_DISTANCE;
    const std::size_t SEPARATION;
    const bool SEP_RAND;

private:
    Core core;
    std::list<Warrior> warList;
    std::list<Warrior>::iterator currentWarrior;
    unsigned cyclesPassed;
    GameStatus gameStatus;
};

