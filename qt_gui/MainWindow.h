#pragma once

#include <QMainWindow>
#include "RenderArea.h"
#include "ResultDialog.h"
#include "GameWizard/GameWizard.h"

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void startNewGame();
    void pauseGame();
    void resumeGame();
    void execTask();

    void showAbout();
    void showHelp();
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    void startExecTasks();
    void showResult();

    RenderArea *renderArea;
    QScrollArea *renderScrollArea;

    GameWizard *gameWizard;
    ResultDialog *resultDialog;

    QAction *newGameAction;
    QAction *pauseGameAction;
    QAction *resumeGameAction;
    QAction *aboutAction;
    QAction *helpAction;

    QMenu *gameMenu;
    QMenu *aboutMenu;


    bool isPaused;

    Mars *mars;
};
