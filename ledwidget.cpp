#include "ledwidget.h"
#include "qpainter.h"
#include "qtimer.h"

LEDWidget::LEDWidget(QWidget* parent) : QWidget(parent), m_ledOn(false) {
    //setFixedSize(100, 100);
    setMinimumSize(10, 10);
    // Таймер для переключения состояния светодиода
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LEDWidget::toggleLED);
    timer->start(1000); // Меняет состояние каждую секунду
}

void LEDWidget::paintEvent(QPaintEvent* event)  {
    QPainter painter(this);
    // Рисуем светодиод
    if (m_ledOn) {
        painter.setBrush(QBrush(Qt::green)); // Включен - зеленый
    } else {
        painter.setBrush(QBrush(Qt::red));   // Выключен - красный
    }

    // Рисуем круг (светодиод)
    painter.drawEllipse(width() * 0.1, height() * 0.1, width() * 0.8, height() * 0.8);
}


void LEDWidget::toggleLED() {
    m_ledOn = !m_ledOn; // Переключаем состояние
    update(); // Перерисовываем виджет
}

void LEDWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newSize = std::min(width(), height());
    resize(newSize, newSize);
}

