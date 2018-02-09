#include "ConclusionPage.h"

#include <QtWidgets>

ConclusionPage::ConclusionPage(GameSettings *gs, QWidget *parent)
    : QWizardPage(parent), gameSettings(gs)

{
    setTitle(tr("Conclusion"));

    conclusionLabel = new QLabel(tr("All game settings and warriors programs was properly configuried. Have fun!"));
    conclusionLabel->setWordWrap(true);
    conclusionTextBrowser = new QPlainTextEdit;
    conclusionTextBrowser->setReadOnly(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(conclusionLabel);
    mainLayout->addWidget(conclusionTextBrowser);
    setLayout(mainLayout);
}

void ConclusionPage::initializePage()
{
    std::ostringstream ss;
    gameSettings->print(ss);
    std::string plainString = ss.str();
    conclusionTextBrowser->clear();
    conclusionTextBrowser->insertPlainText(QString::fromStdString(plainString));
}

