#pragma once

#include <QtWidgets>
#include "../src/Core.h"

class RenderArea : public QWidget
{

Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setCorePtr(const Core *cp) {corePtr = cp;}

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen pen;
    QBrush brush;

    const Core *corePtr;

    const int cellSize = 12;
};

