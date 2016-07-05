#include "entitywidget.h"
#include "ui_entitywidget.h"

EntityWidget::EntityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityWidget)
{
    ui->setupUi(this);

    m_entity = Entity();
    ui->pushButton->setEnabled(false);
}

void EntityWidget::SetEntity(Entity entity)
{
    m_entity = entity;

    if (m_entity.GetTag("cardtype") == "minion")
    {
        ui->atk_lbl->setText(m_entity.GetTag("atk"));
        ui->hp_lbl->setText(m_entity.GetTag("health"));
        ui->name_lbl->setText(m_entity.GetTag("cardid"));
    }
    else if (m_entity.GetTag("cardtype") == "SPELL")
    {
        ui->atk_lbl->setText("SP");
        ui->hp_lbl->setText("ELL");
        ui->name_lbl->setText(m_entity.GetTag("cardid"));
    }
    else
    {
        ui->atk_lbl->setText("");
        ui->hp_lbl->setText("");
        ui->name_lbl->setText(m_entity.GetTag("cardtype"));
    }

    ui->pushButton->setEnabled(true);
}

EntityWidget::~EntityWidget()
{
    delete ui;
}

void EntityWidget::on_pushButton_clicked()
{
    QMessageBox::about(0, "INFO", m_entity.GetInfo());
}
