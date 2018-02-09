#pragma once

#include <QWizardPage>
#include "../../src/Mars.h"
#include "../../src/Parser.h"

class QLabel;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QGroupBox;
class QString;
class QPlainTextEdit;

class GameSetupPage : public QWizardPage
{
    Q_OBJECT

public:
    GameSetupPage(GameSettings *gs, QWidget *parent = 0);
    bool isComplete() const override;

private slots:
    void validateInput();

    void setWarNum(int n) {gameSettings->warriorNumber = n;}
    void setMaxLength(int n) {gameSettings->maxLength = n;}
    void setMaxProc(int n) {gameSettings->maxProcesses = n;}
    void setMaxCycles(int n) {gameSettings->maxCycles = n;}
    void setMinDist(int n) {gameSettings->minDistance = n;}
    void setSeparation(int n) {gameSettings->separation = n;}
    void setRandomSep(bool b) {gameSettings->isRandomSeparation = b;}
    void setCoreSize(int n) {gameSettings->coreSize = n;}
    void setReadDist(int n) {gameSettings->readDistantion = n;}
    void setWriteDist(int n) {gameSettings->writeDistantion = n;}
    void setDefInstr(const PureInstruction& pi) {
            gameSettings->defaultInstriction = pi;
    }

private:
    QLabel *warNumberLabel;
    QLabel *maxLengthLabel;
    QLabel *maxProcLabel;
    QLabel *maxCyclesLabel;
    QLabel *minDistanceLabel;
    QLabel *separationLabel;
    QLabel *coreSizeLabel;
    QLabel *writeDistantionLabel;
    QLabel *readDistantionLabel;
    QLabel *defaultInstructionLabel;
    QSpinBox *warNumberSpinBox;
    QSpinBox *maxLengthSpinBox;
    QSpinBox *maxProcSpinBox;
    QSpinBox *maxCyclesSpinBox;
    QSpinBox *minDistanceSpinBox;
    QSpinBox *separationSpinBox;
    QCheckBox *randomSeparationCheckBox;
    QSpinBox *coreSizeSpinBox;
    QSpinBox *writeDistantionSpinBox;
    QSpinBox *readDistantionSpinBox;
    QLineEdit *defaultInstructionLineEdit;
    QGroupBox *marsSettingsGroupBox;
    QGroupBox *coreSettingsGroupBox;
    QPlainTextEdit *logTextBrowser;

    const int warNumMin = 2;
    const int warNumMax = 1000;
    const int warNumDef = 2;
    const int maxLenMin = 1;
    const int maxLenMax = 10000;
    const int maxLenDef = 300;
    const int maxProcMin = 1;
    const int maxProcMax = 1000;
    const int maxProcDef = 64;
    const int maxCyclesMin = 1;
    const int maxCyclesMax = 1000000;
    const int maxCyclesDef = 100000;
    const int minDistanceMin = 0;
    const int minDistanceMax = 1000000;
    const int minDistanceDef = 300;
    const int separationMin = 0;
    const int separationMax = 1000000;
    const int separationDef = 0;
    const int coreSizeMin = 2;
    const int coreSizeMax = 1000000;
    const int coreSizeDef = 8192;
    const int readDistMin = 1;
    const int readDistMax  = 1000000;
    const int readDistDef  = 8192;
    const int writeDistMin = 1;
    const int writeDistMax  = 1000000;
    const int writeDistDef  = 8192;
    const QString defaultInstructionStringDef = "DAT.F #0, #0";

    GameSettings *gameSettings;
    bool isValidInput;
};
