/*
 *    Deepak Krishnaa Govindarajan
 *    Marcus Naess
 *    Soobin Rho
 *    November 6, 2022
 *    COSC 226: C++ Programming
 *
 *    Hw6: Code walkthrough
 */

#include <QApplication>
#include <QPainter>
#include <QTime>
#include <QTimer>

#include "analog-clock.h"

int main(int argc,char *argv[]) {
    // This initialization is required for all .cpp files in Qt.
    // Source:
    //   https://wiki.qt.io/Qt_for_Beginners
    QApplication app(argc,argv);

    // -------------------------------------------------------------
    // 1. Make an instance of the AnalogClock class
    // -------------------------------------------------------------
    AnalogClock clock;
    clock.show();

    // Again, this statement is required for all .cpp files in Qt
    return app.exec();
}

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent) {
    /*
     *    Definition for the AnalogClock class constructor
     */

    // ------------------------------------------------------------------------
    // 2. Keep track of the time by using a `QTimer`. Timer ticks
    //    every 1 second. This, in turn, updates the clock.
    //
    //    Redrawing the clock every 1 seconds is done by calling the
    //    `AnalogClock::update()` function. Every QWidget instance has
    //    `update()` function. Also, there's another function called
    //    `repaint()`, but the official documentation recommends `update()`.
    //
    //    Source:
    //      https://doc.qt.io/qt-6/qwidget.html#update
    // ------------------------------------------------------------------------
    QTimer *timer = new QTimer(this);

    // Connect the `timer` signal to AnalogClock's `update` slot
    // and call the `AnalogClock::update()` function.
    // Documentation on Signals & Slots:
    //   https://doc.qt.io/qt-6/signalsandslots.html
    connect(timer,&QTimer::timeout,this,QOverload<>::of(&AnalogClock::update));
    timer->start(1000);  // 1000ms = 1s

    setWindowTitle(tr("Analog Clock"));
    resize(200,200);
}

void AnalogClock::paintEvent(QPaintEvent *) {
    /*
     *    Drawing the clock with the QPainter class.
     */

    // -------------------------------------------------------------
    // 2. Keep track of the time by using a `QTimer`. Timer ticks
    //    every 1 second. This, in turn, updates the clock.
    // -------------------------------------------------------------

    static const QPoint hourHand[3] = {
        QPoint(7,8),
        QPoint(-7,8),
        QPoint(0,-40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7,8),
        QPoint(-7,8),
        QPoint(0,-70)
    };

    QColor hourColor(127,0,127);
    QColor minuteColor(0,127,127,191);

    int side = qMin(width(),height());
    QTime time = QTime::currentTime();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2,height()/2);
    painter.scale(side/200.0,side/200.0);

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0*((time.hour()+time.minute()/60.0)));
    painter.drawConvexPolygon(hourHand,3);
    painter.restore();

    painter.setPen(hourColor);

    for (int i=0; i<12; ++i) {
        painter.drawLine(88,0,96,0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0*(time.minute()+time.second()/60.0));
    painter.drawConvexPolygon(minuteHand,3);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j=0; j<60; ++j) {
        if ((j%5)!=0)
            painter.drawLine(92,0,96,0);
        painter.rotate(6.0);
    }
}
