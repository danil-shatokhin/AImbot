#ifndef ACTIONEXECUTOR_H
#define ACTIONEXECUTOR_H
#include <QCursor>
#include <QDebug>
#include <Windows.h>
#include <QRect>
#include <QObject>
#include <QTimer>


class ActionExecutor : public QObject
{
    Q_OBJECT

    HWND hWindow;
    QRect m_window_rect;
    QCursor *c;
    QTimer m_update_timer;

public:
    ActionExecutor();
    void EndTurn(double w, double h);

private slots:
    void UpdatePosition();

signals:
    void Status(bool status);
};

#endif // ACTIONEXECUTOR_H
