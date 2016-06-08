#include "entitywidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_log_reader("C:/Games/Hearthstone/Hearthstone_Data/output_log.txt")
{
    ui->setupUi(this);

    m_log_update_timer.setInterval(15000);

    connect(&m_log_update_timer, SIGNAL(timeout()), SLOT(CheckLog()));
    connect(&m_log_reader, SIGNAL(NewEntity(Entity)), SLOT(OnNewEntity(Entity)));
    connect(&m_log_reader, SIGNAL(EntityUpdate(QString,QString,QString)), SLOT(OnEntityUpdate(QString,QString,QString)));
    connect(&m_log_reader, SIGNAL(GlobalEntityUpdate(QString,QString,QString)), SLOT(OnGlobalEntityUpdate(QString,QString,QString)));

    CheckLog();
    m_log_update_timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckLog()
{
    m_log_reader.Update();
    UpdateUI();
}

void MainWindow::UpdateUI()
{
    qDebug() << "UI update!";
    QList<QWidget*> lst = ui->ally_board_widget->findChildren<QWidget*>();
    foreach(QWidget* w, lst)
        w->deleteLater();

    QVector<Entity> ally_board = m_manager.GetAllyBoard();
    int i=0;
    foreach(Entity e, ally_board)
    {
        EntityWidget *w = new EntityWidget(ui->ally_board_widget);
        w->SetEntity(e);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();
        i++;
    }

    //-----------------------------------------------------------

    lst = ui->ally_hand_widget->findChildren<QWidget*>();
    foreach(QWidget* w, lst)
        w->deleteLater();

    QVector<Entity> ally_hand = m_manager.GetAllyHand();
    i = 0;
    foreach(Entity e, ally_hand)
    {
        EntityWidget *w = new EntityWidget(ui->ally_hand_widget);
        w->SetEntity(e);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();
        i++;
    }

    //-----------------------------------------------------------

    lst = ui->enemy_board_widget->findChildren<QWidget*>();
    foreach(QWidget* w, lst)
        w->deleteLater();

    QVector<Entity> enemy_board = m_manager.GetEnemyBoard();
    i = 0;
    foreach(Entity e, enemy_board)
    {
        EntityWidget *w = new EntityWidget(ui->enemy_board_widget);
        w->SetEntity(e);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();
        i++;
    }

    //-----------------------------------------------------------

    lst = ui->enemy_hand_widget->findChildren<QWidget*>();
    foreach(QWidget* w, lst)
        w->deleteLater();

    QVector<Entity> enemy_hand = m_manager.GetEnemyHand();
    i = 0;
    foreach(Entity e, enemy_hand)
    {
        EntityWidget *w = new EntityWidget(ui->enemy_hand_widget);
        w->SetEntity(e);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();
        i++;
    }

    //-----------------------------------------------------------

    qDebug() << ally_hand.size() << ally_board.size() << enemy_board.size() << enemy_board.size();

    ui->ally_hero_widget->SetEntity(m_manager.GetAllyHero());
    ui->enemy_hero_widget->SetEntity(m_manager.GetEnemyHero());
    ui->game_widget->SetEntity(m_manager.GetGameEntity());
}

void MainWindow::OnNewEntity(Entity e)
{
    //qDebug() << "MainWindow::OnNewEntity: " << e.GetTag("entity_id");
    m_manager.NewEntity(e);
}

void MainWindow::OnEntityUpdate(QString id, QString tag, QString new_value)
{
    //qDebug() << "Entity update: " << id << tag << new_value;
    m_manager.EntityUpdate(id, tag, new_value);
}

void MainWindow::OnGlobalEntityUpdate(QString name, QString tag, QString value)
{
    //qDebug() << "Entity update: " << name << tag << value;
    m_manager.GlobalEntityUpdate(name, tag, value);
}
