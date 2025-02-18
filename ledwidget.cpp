#include "ledwidget.h"
#include "qpainter.h"
#include "qtimer.h"

LEDWidget::LEDWidget(int mode_, QWidget* parent) : QWidget(parent), status(0) {
    mode = mode_;
    setMinimumSize(10, 10);
    // Таймер для переключения состояния светодиода
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&](){
        if(status == 1)
            setStatus(0);
        else
            setStatus(1);
    });
    timer->start(1000); // Меняет состояние каждую секунду
}

void LEDWidget::paintEvent(QPaintEvent*)  {
    QPainter painter(this);
    // Рисуем светодиод
    if (status == 0) {
        if(mode == 2)
            painter.setBrush(QBrush(Qt::red));   // Выключен - красный
        else
            painter.setBrush(QBrush(Qt::lightGray));   // Выключен - красный
    }
    else {
        if(mode == 1)
            painter.setBrush(QBrush(Qt::red));   // Выключен - красный
        else
            painter.setBrush(QBrush(Qt::green));   // Выключен - красный

    }


    // Рисуем круг (светодиод)
    painter.drawEllipse(width() * 0.1, height() * 0.1, width() * 0.8, height() * 0.8);
}


void LEDWidget::setStatus(int s) {
    status = s; // Переключаем состояние
    update(); // Перерисовываем виджет
}

void LEDWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newSize = std::min(width(), height());
    resize(newSize, newSize);
}

