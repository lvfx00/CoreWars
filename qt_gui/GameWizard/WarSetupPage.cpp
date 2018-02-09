#include "WarSetupPage.h"
#include <QtWidgets>
#include "../../src/Parser.h"
#include <sstream>
#include <ostream>

WarSetupPage::WarSetupPage(GameSettings *gs, QWidget *parent)
    : QWizardPage(parent), gameSettings(gs)
{
    setTitle(tr("Warriors Setup"));

    selectorSpinBox = new QSpinBox;
    selectorSpinBox->setButtonSymbols(QSpinBox::NoButtons);
    selectorPrevPushButton = new QPushButton("<<");
    connect(selectorPrevPushButton, &QPushButton::clicked,
            selectorSpinBox, &QSpinBox::stepDown);
    selectorNextPushButton = new QPushButton(">>");
    connect(selectorNextPushButton, &QPushButton::clicked,
            selectorSpinBox, &QSpinBox::stepUp);

    editMenuGroupBox = new QGroupBox(tr("Warrior Settings"));

    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);

    filePathLabel = new QLabel(tr("File path:"));
    filePathLineEdit = new QLineEdit;
    filePathLabel->setBuddy(filePathLineEdit);
    filePathPushButton = new QPushButton(tr("Browse"));

    logTextBrowser = new QPlainTextEdit;
    logTextBrowser->setReadOnly(true);

    QGridLayout *editMenuLayout = new QGridLayout;
    editMenuLayout->addWidget(nameLabel, 0, 0);
    editMenuLayout->addWidget(nameLineEdit, 0, 1, 1, 2);
    editMenuLayout->addWidget(filePathLabel, 1, 0);
    editMenuLayout->addWidget(filePathLineEdit, 1, 1);
    editMenuLayout->addWidget(filePathPushButton, 1, 2);
    editMenuLayout->addWidget(logTextBrowser, 2, 0, 1, 3);

    editMenuGroupBox->setLayout(editMenuLayout);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(selectorPrevPushButton, 0, 0);
    mainLayout->addWidget(selectorSpinBox, 0, 1);
    mainLayout->addWidget(selectorNextPushButton, 0, 2);
    mainLayout->addWidget(editMenuGroupBox, 1, 0, 1, 3);

    setLayout(mainLayout);

    connect(selectorSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &WarSetupPage::setCurrentWarrior);

    connect(nameLineEdit, &QLineEdit::textChanged,
            this, &WarSetupPage::setName);
    connect(filePathLineEdit, &QLineEdit::textChanged,
            this, &WarSetupPage::setProgFile);

    warProgFileDialog = new QFileDialog;
    connect(filePathPushButton, &QPushButton::clicked,
            this, &WarSetupPage::showFileDialog);
    connect(warProgFileDialog, &QFileDialog::fileSelected,
            filePathLineEdit, &QLineEdit::setText);
}

void WarSetupPage::initializePage()
{
    warNum = gameSettings->warriorNumber;

    isValidWarData.resize(warNum);
    progFiles.resize(warNum);
    gameSettings->warData.resize(warNum);

    isValidWarData.assign(warNum, false);


    selectorSpinBox->setRange(1, warNum);
    selectorSpinBox->setValue(1);
    setCurrentWarrior(1);
}

void WarSetupPage::setCurrentWarrior(int n)
{
    if(n > warNum){
        throw(std::invalid_argument("Number of warriors exceeded!"));
    }
    currentWarrior = n;
    nameLineEdit->setText(QString::fromStdString(gameSettings->warData[currentWarrior - 1].warName));
    filePathLineEdit->setText(QString::fromStdString(progFiles[currentWarrior - 1]));
    validateCurrentWarrior();
}

void WarSetupPage::setProgFile(const QString& str) {
    progFiles[currentWarrior - 1] = str.toStdString();
    validateCurrentWarrior();
}

void WarSetupPage::setName(const QString& str) {
    gameSettings->warData[currentWarrior - 1].warName = str.toStdString();
    validateCurrentWarrior();
}

void WarSetupPage::validateCurrentWarrior()
{
    std::string filename(progFiles[currentWarrior - 1]);
    std::ifstream ifs(filename);

    logTextBrowser->clear();

    if (!ifs.is_open()) {
        logTextBrowser->insertPlainText(tr("Error!\n") + QString::fromStdString(
                                    std::string("file \"") + filename + "\" doesn't exists!"));
        isValidWarData[currentWarrior - 1] = false;
    } else {
        try {
            std::string name = gameSettings->warData[currentWarrior - 1].warName;
            gameSettings->warData[currentWarrior - 1] = std::move(Parser::getInstance()->parseProgramFile(ifs));
            gameSettings->warData[currentWarrior - 1].warName = name;

            std::ostringstream ss;
            gameSettings->warData[currentWarrior - 1].print(ss);
            std::string plainString = ss.str();
            logTextBrowser->insertPlainText(tr("Valid warrior program loaded!\n") + QString::fromStdString(plainString));

            isValidWarData[currentWarrior - 1] = true;
        } catch (const std::invalid_argument& e) {
            logTextBrowser->insertPlainText(tr("Parsing file error!\n") + e.what());
            isValidWarData[currentWarrior - 1] = false;
        }
    }

    emit completeChanged();
}

bool WarSetupPage::isComplete() const {
    for(int i = 0; i < warNum; ++i) {
        if(!isValidWarData[i])
            return false;
    }
    return true;
}

void WarSetupPage::showFileDialog()
{
    warProgFileDialog->exec();
    warProgFileDialog->activateWindow();
}
