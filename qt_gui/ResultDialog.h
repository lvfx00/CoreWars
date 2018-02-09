#pragma once

#include <QDialog>

class QLabel;
class QPushButton;

class ResultDialog : public QDialog
{

Q_OBJECT

public:
    ResultDialog();
    void setResultMessage(const QString&);

private:
    QLabel *resultLabel;
    QPushButton *okButton;
};
