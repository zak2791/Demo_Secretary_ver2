#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include "qwidget.h"

class LEDWidget : public QWidget {
    Q_OBJECT

public:
    LEDWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

private slots:
    void toggleLED(void);

private:
    bool m_ledOn; // Состояние светодиода (включен/выключен)

};

#endif // LEDWIDGET_H
