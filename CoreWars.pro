#-------------------------------------------------
#
# Project created by QtCreator 2018-02-09T16:00:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoreWars
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    qt_gui/GameWizard/ConclusionPage.cpp \
    qt_gui/GameWizard/GameSetupPage.cpp \
    qt_gui/GameWizard/GameWizard.cpp \
    qt_gui/GameWizard/IntroPage.cpp \
    qt_gui/GameWizard/WarSetupPage.cpp \
    qt_gui/MainWindow.cpp \
    qt_gui/RenderArea.cpp \
    qt_gui/ResultDialog.cpp \
    src/Instructions/Instr_ADD.cpp \
    src/Instructions/Instr_CMP.cpp \
    src/Instructions/Instr_DAT.cpp \
    src/Instructions/Instr_DIV.cpp \
    src/Instructions/Instr_DJN.cpp \
    src/Instructions/Instr_JMN.cpp \
    src/Instructions/Instr_JMP.cpp \
    src/Instructions/Instr_JMZ.cpp \
    src/Instructions/Instr_MOD.cpp \
    src/Instructions/Instr_MOV.cpp \
    src/Instructions/Instr_MUL.cpp \
    src/Instructions/Instr_NOP.cpp \
    src/Instructions/Instr_SLT.cpp \
    src/Instructions/Instr_SNE.cpp \
    src/Instructions/Instr_SPL.cpp \
    src/Instructions/Instr_SUB.cpp \
    src/Core.cpp \
    src/Instruction.cpp \
    src/Mars.cpp \
    src/Parser.cpp \
    main.cpp

HEADERS += \
    qt_gui/GameWizard/ConclusionPage.h \
    qt_gui/GameWizard/GameSetupPage.h \
    qt_gui/GameWizard/GameWizard.h \
    qt_gui/GameWizard/IntroPage.h \
    qt_gui/GameWizard/WarSetupPage.h \
    qt_gui/MainWindow.h \
    qt_gui/RenderArea.h \
    qt_gui/ResultDialog.h \
    src/Core.h \
    src/Factory.h \
    src/Instruction.h \
    src/InstructionContext.h \
    src/Mars.h \
    src/MarsInterface.h \
    src/Parser.h \
    src/Warrior.h
