#include <random>
#include "Mars.h"
#include "InstructionContext.h"

void Mars::loadWarrior(const WarData &warData) {
    if (warList.size() == WAR_NUM) {
        throw std::length_error("Maximum warrior number already loaded!!!");
    }

    static const std::size_t sectorSize = core.CORE_SIZE / WAR_NUM;
    std::size_t positionToPlace;

    if (SEP_RAND) {
        std::random_device rd;
        std::mt19937_64 gen(rd());

        std::size_t firstFreePosition = ( (warList.empty()) ? 0 : (warList.back().firstInstructionAddress + MIN_DISTANCE) );

        std::uniform_int_distribution<std::size_t> dis(firstFreePosition,
                           sectorSize * (warList.size() + 1) - warData.instructionList.size());
        positionToPlace = dis(gen);

    } else {
        positionToPlace = ( (warList.empty()) ? 0 : (warList.back().firstInstructionAddress + SEPARATION) );
    }

    std::size_t i = positionToPlace;
    for (auto &it : warData.instructionList) {
        core.loadInstr(*it, i++);
    }

    warList.emplace_back(Warrior(warData.warName, positionToPlace));
    warList.back().taskQueue.emplace(positionToPlace + warData.startingInstructionNumber);
    return;
}

void Mars::execTask() {
    if(gameStatus != In_Process) {
        throw std::logic_error("Game isn't in process!");
    }

    if(warList.size() == 1) {
        gameStatus = Has_Winner;
        return; // the winner is last warrior in warList
    }

    if(cyclesPassed == MAX_CYCLES) {
        gameStatus = Tie;
        return; // tie
    }

    if(currentWarrior == warList.end()){
        ++cyclesPassed;
        currentWarrior = warList.begin();
        execTask();
        return; // 0 - nothing important happened
    }

    if(currentWarrior->taskQueue.empty()) {
        currentWarrior = warList.erase(currentWarrior); // returns next element iterator
        execTask();
        return;
    }

    Address currTask = currentWarrior->taskQueue.front();

    InstructionContext context(&core, &(*currentWarrior));
    core[currTask]->exec(context);

    currentWarrior++;
}

void Mars::startGame() {
    if (warList.size() != WAR_NUM) {
        throw std::runtime_error("You have to load WAR_NUM warriors!!!");
    }
    currentWarrior = warList.begin();
    gameStatus = In_Process;
}

Mars::GameStatus Mars::getStatus() const {return gameStatus;}

std::string Mars::getWinnerName() const {
    return (gameStatus == Has_Winner) ? warList.front().warName : std::string("");
}

const Core *Mars::getCore() const {return &core;}



