#include "GameWizard.h"

#include <QtWidgets>
#include <iostream>
#include "src/Parser.h"
#include "IntroPage.h"
#include "GameSetupPage.h"
#include "WarSetupPage.h"
#include "ConclusionPage.h"

GameWizard::GameWizard(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_Game_Setup, new GameSetupPage(&gameSettings));
    setPage(Page_War_Setup, new WarSetupPage(&gameSettings));
    setPage(Page_Conclusion, new ConclusionPage(&gameSettings));

    setStartId(Page_Intro);

    setWindowTitle(tr("New Game Wizard"));

    setOption(IndependentPages, false);
}

GameSettings &&GameWizard::getGameSettings()
{
    return std::move(gameSettings);
}
