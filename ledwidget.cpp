#include "ledwidget.h"
#include "qpainter.h"
//#include "qtimer.h"

LEDWidget::LEDWidget(int mode_, QWidget* parent) : QWidget(parent), status(0) {
    mode = mode_;
    setMinimumSize(10, 10);
    // Таймер для переключения состояния светодиода
    // QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, [&](){
    //     if(status == 1)
    //         setStatus(0);
    //     else
    //         setStatus(1);
    // });
    // timer->start(1000); // Меняет состояние каждую секунду
}

void LEDWidget::turnOnOff(bool _status)
{
    status = _status;
    update();
}

void LEDWidget::paintEvent(QPaintEvent*)  {
    QPainter painter(this);
    // Рисуем светодиод
    if (!status) {
        if(mode == 0)
            painter.setBrush(QBrush(Qt::red));          // Выключен - красный
        else
            painter.setBrush(QBrush(Qt::lightGray));    // Выключен - серый
    }
    else {
        if(mode == 0)
            painter.setBrush(QBrush(Qt::green));   // Включен - красный
        else
            painter.setBrush(QBrush(Qt::green));   // Включен - зеленый

    }


    // Рисуем круг (светодиод)
    painter.drawEllipse(width() * 0.1, height() * 0.1, width() * 0.8, height() * 0.8);
}

void LEDWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newSize = std::min(width(), height());
    resize(newSize, newSize);
}

