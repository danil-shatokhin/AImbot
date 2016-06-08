#ifndef ENTITYWIDGET_H
#define ENTITYWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <entity.h>

namespace Ui {
class EntityWidget;
}

class EntityWidget : public QWidget
{
    Q_OBJECT
    Entity m_entity;

public:
    explicit EntityWidget(QWidget *parent = 0);
    void SetEntity(Entity entity);
    ~EntityWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EntityWidget *ui;
};

#endif // ENTITYWIDGET_H
