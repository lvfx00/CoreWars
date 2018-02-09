#pragma once

#include <QWizardPage>

class QLabel;
class QRadioButton;

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);
    int nextId() const override;

private:
    QLabel *introLabel;
    QRadioButton *defaultSetupRadioButton;
    QRadioButton *advancedSetupRadioButton;
}; 
