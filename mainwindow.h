#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <entitymanager.h>
#include <logreader.h>
#include <QDebug>
#include <QTimer>
#include <entitywidget.h>
#include <actionexecutor.h>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    EntityManager m_manager;
    LogReader m_log_reader;
    ActionExecutor m_action_executor;
    QTimer m_log_update_timer;

    QVector <EntityWidget*> m_ally_hand_widgets;
    QVector <EntityWidget*> m_ally_board_widgets;
    QVector <EntityWidget*> m_enemy_hand_widgets;
    QVector <EntityWidget*> m_enemy_board_widgets;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void UpdateUI();
    void InitBoard();
    void ClearBoard();

private slots:
    void CheckLog();
    void OnNewEntity(Entity e);
    void OnEntityUpdate( QString id, QString tag, QString new_value );
    void OnGlobalEntityUpdate( QString name, QString tag, QString value );

    void OnGameOver();
    void OnTurnOver();
    void OnNewTurn(bool ally);

    void OnEndTurn();
    void OnPlayCard();
    void OnAttack();
};

#endif // MAINWINDOW_H
