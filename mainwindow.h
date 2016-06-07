#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <entitymanager.h>
#include <logreader.h>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    EntityManager m_manager;
    LogReader m_log_reader;
    QTimer m_log_update_timer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void UpdateUI();

private slots:
    void CheckLog();
    void OnNewEntity(Entity e);
    void OnEntityUpdate( QString id, QString tag, QString new_value );
    void OnGlobalEntityUpdate( QString name, QString tag, QString value );
};

#endif // MAINWINDOW_H
