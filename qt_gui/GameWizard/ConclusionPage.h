#pragma once

#include <QWizardPage>
#include "../../src/Mars.h"

class QLabel;
class QPlainTextEdit;

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(GameSettings *gs, QWidget *parent = 0);
    void initializePage() override;

private:
    QLabel *conclusionLabel;
    QPlainTextEdit *conclusionTextBrowser;

    GameSettings *gameSettings;
};
 
