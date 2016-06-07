#include "entitywidget.h"
#include "ui_entitywidget.h"

EntityWidget::EntityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityWidget)
{
    ui->setupUi(this);
}

void EntityWidget::SetText(QString text)
{
    m_text = text;
}

EntityWidget::~EntityWidget()
{
    delete ui;
}

void EntityWidget::on_pushButton_clicked()
{
    QMessageBox::about(0, "INFO", m_text);
}
