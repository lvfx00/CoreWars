#include "IntroPage.h"
#include "GameWizard.h"
#include <QtWidgets>

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    introLabel = new QLabel(tr("This wizard will help you create new game. "
                               "Choose your setup way:"));
    introLabel->setWordWrap(true);

    defaultSetupRadioButton = new QRadioButton(tr("Cuick Setup (using ICWS86 Standart variable set)"));
    advancedSetupRadioButton = new QRadioButton(tr("Advanced Setup (using your own variable set)"));
    defaultSetupRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(introLabel);
    layout->addWidget(defaultSetupRadioButton);
    layout->addWidget(advancedSetupRadioButton);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    if (defaultSetupRadioButton->isChecked()) {
        return GameWizard::Page_War_Setup;
    } else {
        return GameWizard::Page_Game_Setup;
    }
} 
