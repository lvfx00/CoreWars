#pragma once

#include <QWizard>
#include "../../src/Mars.h"

class GameWizard : public QWizard
{
    Q_OBJECT

public:
    enum {Page_Intro, Page_Game_Setup, Page_War_Setup, Page_Conclusion};

    GameWizard(QWidget *parent = 0);

    GameSettings &&getGameSettings();

private:
    GameSettings gameSettings;

};
