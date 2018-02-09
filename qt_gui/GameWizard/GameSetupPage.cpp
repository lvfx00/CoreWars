#include "GameSetupPage.h"

#include <QtWidgets>

GameSetupPage::GameSetupPage(GameSettings *gs, QWidget *parent)
    : QWizardPage(parent), gameSettings(gs)
{
    setTitle(tr("Game Setup"));

    marsSettingsGroupBox = new QGroupBox(tr("MARS settings"));

    warNumberLabel = new QLabel(tr("Warriors:"));
    warNumberSpinBox = new QSpinBox;
    warNumberSpinBox->setRange(warNumMin, warNumMax);
    warNumberLabel->setBuddy(warNumberSpinBox);
    connect(warNumberSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setWarNum);
    warNumberSpinBox->setValue(warNumDef);

    maxLengthLabel = new QLabel(tr("Max length:"));
    maxLengthSpinBox = new QSpinBox;
    maxLengthSpinBox->setRange(maxLenMin, maxLenMax);
    maxLengthLabel->setBuddy(maxLengthSpinBox);
    connect(maxLengthSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setMaxLength);
    maxLengthSpinBox->setValue(maxLenDef);

    maxProcLabel = new QLabel(tr("Max processes:"));
    maxProcSpinBox = new QSpinBox;
    maxProcSpinBox->setRange(maxProcMin, maxProcMax);
    maxProcLabel->setBuddy(maxProcSpinBox);
    connect(maxProcSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setMaxProc);
    maxProcSpinBox->setValue(maxProcDef);

    maxCyclesLabel = new QLabel(tr("Max cycles:"));
    maxCyclesSpinBox = new QSpinBox;
    maxCyclesSpinBox->setRange(maxCyclesMin, maxCyclesMax);
    maxCyclesLabel->setBuddy(maxCyclesSpinBox);
    connect(maxCyclesSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setMaxCycles);
    maxCyclesSpinBox->setValue(maxCyclesDef);

    minDistanceLabel = new QLabel(tr("Min distance:"));
    minDistanceSpinBox = new QSpinBox;
    minDistanceSpinBox->setRange(minDistanceMin, minDistanceMax);
    minDistanceLabel->setBuddy(minDistanceSpinBox);
    connect(minDistanceSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setMinDist);
    minDistanceSpinBox->setValue(minDistanceDef);

    separationLabel = new QLabel(tr("Separation:"));
    separationSpinBox = new QSpinBox;
    separationLabel->setBuddy(separationSpinBox);
    separationSpinBox->setRange(separationMin, separationMax);
    connect(separationSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setSeparation);
    separationSpinBox->setValue(separationDef);

    randomSeparationCheckBox = new QCheckBox(tr("Random"));
    connect(randomSeparationCheckBox, &QCheckBox::clicked,
            separationSpinBox, &QSpinBox::setDisabled);
    connect(randomSeparationCheckBox, &QCheckBox::clicked,
            this, &GameSetupPage::setRandomSep);
    randomSeparationCheckBox->click();

    QGridLayout *marsSettingsLayout = new QGridLayout;
    marsSettingsLayout->addWidget(warNumberLabel, 0, 0);
    marsSettingsLayout->addWidget(warNumberSpinBox, 0, 1);
    marsSettingsLayout->addWidget(maxLengthLabel, 1, 0);
    marsSettingsLayout->addWidget(maxLengthSpinBox, 1, 1);
    marsSettingsLayout->addWidget(maxProcLabel, 2, 0);
    marsSettingsLayout->addWidget(maxProcSpinBox, 2, 1);
    marsSettingsLayout->addWidget(maxCyclesLabel, 3, 0);
    marsSettingsLayout->addWidget(maxCyclesSpinBox, 3, 1);
    marsSettingsLayout->addWidget(minDistanceLabel, 4, 0);
    marsSettingsLayout->addWidget(minDistanceSpinBox, 4, 1);
    marsSettingsLayout->addWidget(separationLabel, 5, 0);
    marsSettingsLayout->addWidget(separationSpinBox, 5, 1);
    marsSettingsLayout->addWidget(randomSeparationCheckBox, 6, 0);
    marsSettingsGroupBox->setLayout(marsSettingsLayout);

    coreSettingsGroupBox = new QGroupBox(tr("Core settings"));

    coreSizeLabel = new QLabel(tr("Core size:"));
    coreSizeSpinBox = new QSpinBox;
    coreSizeSpinBox->setRange(coreSizeMin, coreSizeMax);
    coreSizeLabel->setBuddy(coreSizeSpinBox);
    connect(coreSizeSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setCoreSize);
    coreSizeSpinBox->setValue(coreSizeDef);

    writeDistantionLabel = new QLabel(tr("Write Distance:"));
    writeDistantionSpinBox = new QSpinBox;
    writeDistantionSpinBox->setRange(readDistMin, readDistMax);
    writeDistantionLabel->setBuddy(writeDistantionSpinBox);
    connect(writeDistantionSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setWriteDist);
    writeDistantionSpinBox->setValue(readDistDef);

    readDistantionLabel = new QLabel(tr("Read Distance:"));
    readDistantionSpinBox = new QSpinBox;
    readDistantionSpinBox->setRange(writeDistMin, writeDistMax);
    readDistantionLabel->setBuddy(readDistantionSpinBox);
    connect(readDistantionSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::setReadDist);
    readDistantionSpinBox->setValue(writeDistDef);

    defaultInstructionLabel = new QLabel(tr("Default:"));
    defaultInstructionLineEdit = new QLineEdit;
    defaultInstructionLabel->setBuddy(defaultInstructionLineEdit);
    defaultInstructionLineEdit->setText(defaultInstructionStringDef);

    QGridLayout *coreSettingsLayout = new QGridLayout;
    coreSettingsLayout->addWidget(coreSizeLabel, 0, 0);
    coreSettingsLayout->addWidget(coreSizeSpinBox, 0, 1);
    coreSettingsLayout->addWidget(writeDistantionLabel, 1, 0);
    coreSettingsLayout->addWidget(writeDistantionSpinBox, 1, 1);
    coreSettingsLayout->addWidget(readDistantionLabel, 2, 0);
    coreSettingsLayout->addWidget(readDistantionSpinBox, 2, 1);
    coreSettingsLayout->addWidget(defaultInstructionLabel, 3, 0);
    coreSettingsLayout->addWidget(defaultInstructionLineEdit, 3, 1);
    coreSettingsGroupBox->setLayout(coreSettingsLayout);

    logTextBrowser = new QPlainTextEdit;
    logTextBrowser->setReadOnly(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(marsSettingsGroupBox, 0, 0);
    mainLayout->addWidget(coreSettingsGroupBox, 0, 1);
    mainLayout->addWidget(logTextBrowser, 1, 0, 1, 2);
    setLayout(mainLayout);

    connect(warNumberSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::validateInput);
    connect(maxLengthSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::validateInput);
    connect(minDistanceSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::validateInput);
    connect(separationSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::validateInput);
    connect(coreSizeSpinBox, qOverload<int>(&QSpinBox::valueChanged),
            this, &GameSetupPage::validateInput);
    connect(defaultInstructionLineEdit, &QLineEdit::textChanged,
            this, &GameSetupPage::validateInput);
    connect(randomSeparationCheckBox, &QCheckBox::clicked,
            this, &GameSetupPage::validateInput);

    validateInput();
}

bool GameSetupPage::isComplete() const {
    return isValidInput;
}

void GameSetupPage::validateInput() {
    logTextBrowser->clear();

    if(maxLengthSpinBox->value() > minDistanceSpinBox->value()) {
        logTextBrowser->insertPlainText(tr("Minimum distance between warriors must be more or equal to maximum warrior's program length!"));
        isValidInput = false;
    }

    if(randomSeparationCheckBox->isChecked()) {
        if (warNumberSpinBox->value() * minDistanceSpinBox->value() > coreSizeSpinBox->value()) {
            logTextBrowser->insertPlainText(tr("Can't emplace this amount of warriors - there is not enough empty space for them!"));
            isValidInput = false;
        }
    } else {
        if (warNumberSpinBox->value() * separationSpinBox->value() > coreSizeSpinBox->value()) {
            logTextBrowser->insertPlainText(tr("Can't emplace this amount of warriors - there is not enough empty space for them!"));
            isValidInput = false;
        }

        if(minDistanceSpinBox->value() > separationSpinBox->value()) {
            logTextBrowser->insertPlainText(tr("Separation distance must be more or equal to minimum distance between warriors!"));
            isValidInput = false;
        }
    }

    try {
        PureInstruction pi = *Parser::getInstance()->parseInstruction(defaultInstructionLineEdit->text().toStdString());
        setDefInstr(pi);
        logTextBrowser->insertPlainText(tr("Correct settings!"));
        isValidInput = true;
    } catch (const std::invalid_argument &a) {
        logTextBrowser->insertPlainText(tr("Invalid default instruction!\n") + QString::fromStdString(a.what()));
        isValidInput = false;
    }

    completeChanged();
}
