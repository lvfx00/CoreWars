#include "ResultDialog.h"

#include <QtWidgets>

ResultDialog::ResultDialog()
{
    resultLabel = new QLabel;
    okButton = new QPushButton("OK");

    connect(okButton, &QPushButton::clicked,
            this, &QDialog::close);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(okButton);
    setLayout(mainLayout);
}

void ResultDialog::setResultMessage(const QString &text)
{
    resultLabel->setText(text);
}
