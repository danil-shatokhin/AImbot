#include "actionexecutor.h"

ActionExecutor::ActionExecutor() :
    c(new QCursor())
{
    connect(&m_update_timer, SIGNAL(timeout()), SLOT(UpdatePosition()));
    m_update_timer.setInterval(500);
    m_update_timer.start();
}

//end turn button offset = 0.93, 0.48

//ally board y = 0.56
//enemy board y = 0.43
//[7] = 0.20 + 10
//[6] = 0.25 + 10
//[5] = 0.30 + 10
//[4] = 0.35 + 10
//[3] = 0.40
//[2] = 0.45
//[1] = 0.5

//cards y = 0.94
//[1] = 0.46
//[2] = {0.41 + .09]
//[3] = {0.38 + .09}
//[4] = {0.33 + .09}
//[5] = {0.30 + .09}
//[6] = {0.27 + .07}
//[7] = [0.275 + .06}
//[8] = [0.242 + .055]
//[9] = [0.234 + .051}
//[10] y = 0.95, x = [0.232 + .046}

void ActionExecutor::EndTurn(double w, double h)
{
    int left_offset = 0;
    if (m_window_rect.width() > m_window_rect.height()*1.18)
        left_offset = (m_window_rect.width()-(m_window_rect.height()*1.18));
    left_offset/=2;

    int width_offset = (m_window_rect.width()-(left_offset*2))*w;
    int height_offset = m_window_rect.height()*h;

    QPoint p = m_window_rect.topLeft() + QPoint(left_offset, 0) + QPoint(width_offset, height_offset);
    c->setPos(p);
}

void ActionExecutor::UpdatePosition()
{
    hWindow = FindWindow(NULL, L"Hearthstone");

    if (hWindow == NULL)
    {
        emit Status(false);
        return;
    }
    else
    {
        emit Status(true);
        RECT rect;
        GetWindowRect(hWindow, &rect);
        m_window_rect = QRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
    }
}
