#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    corePtr = nullptr;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::sizeHint() const
{
    return QSize(800, 400);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    if(corePtr) {
        int width = this->width();
        int height = this->height();
        int cellsNumber = corePtr->CORE_SIZE;

        int cellsInLine = width / cellSize;
        int numberOfLines = cellsNumber / cellsInLine
            + ((cellsNumber % cellsInLine) ? 1 : 0);

        QPainter painter(this);

        for(int i = 0; i <= cellsInLine; ++i) {
            painter.drawLine(i * cellSize, 0, i * cellSize, cellSize * numberOfLines);
        }

        for(int j = 0; j <= numberOfLines; ++j) {
            painter.drawLine(0, j * cellSize, cellsInLine * cellSize, j * cellSize);
        }
    }
}
