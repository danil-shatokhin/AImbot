#include "entitywidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_log_reader("C:/Program Files (x86)/Hearthstone/Hearthstone_Data/output_log.txt")

{
    ui->setupUi(this);
    InitBoard();

    m_log_update_timer.setInterval(3000);

    connect(&m_log_update_timer, SIGNAL(timeout()), SLOT(CheckLog()));
    connect(&m_log_reader, SIGNAL(NewEntity(Entity)), SLOT(OnNewEntity(Entity)));
    connect(&m_log_reader, SIGNAL(EntityUpdate(QString,QString,QString)), SLOT(OnEntityUpdate(QString,QString,QString)));
    connect(&m_log_reader, SIGNAL(GlobalEntityUpdate(QString,QString,QString)), SLOT(OnGlobalEntityUpdate(QString,QString,QString)));

    connect(&m_manager, SIGNAL(GameOver()), SLOT(OnGameOver()) );
    connect(&m_manager, SIGNAL(TurnOver()), SLOT(OnTurnOver()) );
    connect(&m_manager, SIGNAL(TurnStart(bool)), SLOT(OnNewTurn(bool)) );

    connect(ui->end_turn_btn, SIGNAL(clicked(bool)), SLOT(OnEndTurn()) );
    connect(ui->atk_btn, SIGNAL(clicked(bool)), SLOT(OnAttack()) );
    connect(ui->play_card_btn, SIGNAL(clicked(bool)), SLOT(OnPlayCard()) );

    CheckLog();
    //m_log_update_timer.start();
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

    ClearBoard();

    QVector<Entity> ally_board = m_manager.GetAllyBoard();
    int i=0;
    foreach(Entity e, ally_board)
    {
        m_ally_board_widgets[i]->SetEntity(e);
        i++;

        if (i==10)
            break;
    }

    //-----------------------------------------------------------

    QVector<Entity> ally_hand = m_manager.GetAllyHand();
    i = 0;
    foreach(Entity e, ally_hand)
    {
        m_ally_hand_widgets[i]->SetEntity(e);
        i++;

        if (i==10)
            break;
    }

    //-----------------------------------------------------------

    QVector<Entity> enemy_board = m_manager.GetEnemyBoard();
    i = 0;
    foreach(Entity e, enemy_board)
    {
        m_enemy_board_widgets[i]->SetEntity(e);
        i++;

        if (i==10)
            break;
    }

    //-----------------------------------------------------------

    QVector<Entity> enemy_hand = m_manager.GetEnemyHand();
    i = 0;
    foreach(Entity e, enemy_hand)
    {
        m_enemy_hand_widgets[i]->SetEntity(e);
        i++;

        if (i==10)
            break;
    }

    //-----------------------------------------------------------

    qDebug() << ally_hand.size() << ally_board.size() << enemy_board.size() << enemy_hand.size();

    ui->ally_hero_widget->SetEntity(m_manager.GetAllyHero());
    ui->enemy_hero_widget->SetEntity(m_manager.GetEnemyHero());
    ui->game_widget->SetEntity(m_manager.GetGameEntity());
}

void MainWindow::InitBoard()
{
    for (int i=0; i<10; i++)
    {
        EntityWidget *w = new EntityWidget(ui->ally_hand_widget);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();

        m_ally_hand_widgets.push_back(w);
    }

    for (int i=0; i<10; i++)
    {
        EntityWidget *w = new EntityWidget(ui->ally_board_widget);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();

        m_ally_board_widgets.push_back(w);
    }

    for (int i=0; i<10; i++)
    {
        EntityWidget *w = new EntityWidget(ui->enemy_board_widget);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();

        m_enemy_board_widgets.push_back(w);
    }

    for (int i=0; i<10; i++)
    {
        EntityWidget *w = new EntityWidget(ui->enemy_hand_widget);
        w->setGeometry(i*50, 0, 50, 75 );
        w->show();

        m_enemy_hand_widgets.push_back(w);
    }
}

void MainWindow::ClearBoard()
{
    for (int i=0; i<10; i++)
    {
        m_ally_hand_widgets[i]->SetEntity(Entity());
    }

    for (int i=0; i<10; i++)
    {
        m_ally_board_widgets[i]->SetEntity(Entity());
    }

    for (int i=0; i<10; i++)
    {
        m_enemy_board_widgets[i]->SetEntity(Entity());
    }

    for (int i=0; i<10; i++)
    {
        m_enemy_hand_widgets[i]->SetEntity(Entity());
    }
}

void MainWindow::OnNewEntity(Entity e)
{
    //qDebug() << "MainWindow::OnNewEntity: " << e.GetTag("entity_id");
    m_manager.NewEntity(e);
}

void MainWindow::OnEntityUpdate(QString id, QString tag, QString new_value)
{
    //qDebug() << "Entity update: " << id << tag << new_value;
    m_manager.EntityUpdate(id, tag.toLower(), new_value.toLower());
}

void MainWindow::OnGlobalEntityUpdate(QString name, QString tag, QString value)
{
    //qDebug() << "Entity update: " << name << tag << value;
    m_manager.GlobalEntityUpdate(name, tag.toLower(), value.toLower());
}

void MainWindow::OnGameOver()
{
    ui->log->append("GAME OVER");
    ui->log->append("______________________");
}

void MainWindow::OnTurnOver()
{
    ui->log->append("TURN OVER");
    ui->log->append("");
}

void MainWindow::OnNewTurn(bool ally)
{
    qDebug() << "LOG" << ally;
    if (ally)
        ui->log->append("MY TURN");
    else
        ui->log->append("ENEMY TURN");
    ui->log->append("");
}

void MainWindow::OnEndTurn()
{
    double w = ui->atk_from_lbl->text().toDouble();
    double h = ui->atk_to_lbl->text().toDouble();
    m_action_executor.EndTurn(w, h);
}

void MainWindow::OnPlayCard()
{

}

void MainWindow::OnAttack()
{

}
