#include "MainWindow.h"
#include <QtWidgets>
#include "../src/Mars.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    gameWizard = new GameWizard;
    resultDialog = new ResultDialog;

    renderArea = new RenderArea;
    renderScrollArea = new QScrollArea;

//    connect(renderScrollArea, &QScrollArea::widthCha)

    renderScrollArea->setWidget(renderArea);

    setCentralWidget(renderScrollArea);

    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setStatusTip(tr("Start new game"));
    newGameAction->setShortcut(tr("Ctrl+N"));
    connect(newGameAction, SIGNAL(triggered()), this, SLOT(startNewGame()));

    pauseGameAction = new QAction(tr("&Pause Game"), this);
    pauseGameAction->setStatusTip(tr("Pause game"));
    pauseGameAction->setShortcut(tr("Ctrl+P"));
    connect(pauseGameAction, SIGNAL(triggered()), this, SLOT(pauseGame()));
    pauseGameAction->setDisabled(true);

    resumeGameAction = new QAction(tr("&Resume Game"), this);
    resumeGameAction->setStatusTip(tr("Resume game"));
    resumeGameAction->setShortcut(tr("Ctrl+R"));
    connect(resumeGameAction, SIGNAL(triggered()), this, SLOT(resumeGame()));
    resumeGameAction->setDisabled(true);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About game"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    helpAction = new QAction(tr("&Help"), this);
    helpAction->setStatusTip(tr("Show help"));
    helpAction->setShortcut(tr("Ctrl+H"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(showHelp()));
}

void MainWindow::createMenus()
{
    gameMenu = menuBar()->addMenu(tr("Game"));
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(pauseGameAction);
    gameMenu->addAction(resumeGameAction);

    aboutMenu = menuBar()->addMenu(tr("About"));
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(helpAction);

}

void MainWindow::startNewGame()
{
    if(gameWizard->exec())
    {
        mars = new Mars(gameWizard->getGameSettings());
        renderArea->setCorePtr(mars->getCore());
        mars->startGame();
        resumeGame();
    }
}

void MainWindow::startExecTasks()
{
    if(isPaused) {
        return;
    } else {
        if(mars->getStatus() == Mars::In_Process) {
            execTask();
            QTimer::singleShot(10, this, &MainWindow::startExecTasks);
        } else {
            showResult();
        }
    }
}

void MainWindow::execTask()
{
    mars->execTask();
    renderArea->update();
}

void MainWindow::pauseGame()
{
    isPaused = true;
}

void MainWindow::resumeGame()
{
    isPaused = false;
    startExecTasks();
}

void MainWindow::showAbout()
{
}

void MainWindow::showHelp()
{
}

void MainWindow::showResult()
{
    if(mars->getStatus() == Mars::Has_Winner) {
        resultDialog->setResultMessage(tr("The winner is ") +
                                       QString::fromStdString(mars->getWinnerName()));
    } else if(mars->getStatus() == Mars::Tie) {
        resultDialog->setResultMessage(tr("Tie!"));
    }
    resultDialog->exec();
    resultDialog->activateWindow();
}
