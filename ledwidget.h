#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include "qwidget.h"

class LEDWidget : public QWidget {
    Q_OBJECT

public:
    LEDWidget(int, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;

private slots:
    void setStatus(int);

private:
    int status;    // Состояние светодиода 0, 1
    int mode;       // Режим: 0 - серый - зелёный
                    //        1 - серый - красный
                    //        2 - красный - зелёный

};

#endif // LEDWIDGET_H
