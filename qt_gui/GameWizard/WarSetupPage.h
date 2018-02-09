#pragma once

#include <QWizardPage>
#include "../../src/Mars.h"

class QLabel;
class QSpinBox;
class QPushButton;
class QGroupBox;
class QLineEdit;
class QPlainTextEdit;
class QFileDialog;

class WarSetupPage : public QWizardPage
{
    Q_OBJECT

public:
    WarSetupPage(GameSettings *gs, QWidget *parent = 0);
    void initializePage() override;
    bool isComplete() const override;

private slots:
    void setCurrentWarrior(int);
    void setName(const QString&);
    void setProgFile(const QString&);
    void validateCurrentWarrior();
    void showFileDialog();

private:
    QSpinBox *selectorSpinBox;
    QPushButton *selectorPrevPushButton;
    QPushButton *selectorNextPushButton;
    QGroupBox *editMenuGroupBox;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *filePathLabel;
    QLineEdit *filePathLineEdit;
    QPushButton *filePathPushButton;
    QPlainTextEdit *logTextBrowser;
    QFileDialog *warProgFileDialog;

    GameSettings *gameSettings;
    std::vector<std::string> progFiles;
    std::vector<bool> isValidWarData;
    int warNum;
    int currentWarrior;
};
