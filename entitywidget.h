#ifndef ENTITYWIDGET_H
#define ENTITYWIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class EntityWidget;
}

class EntityWidget : public QWidget
{
    Q_OBJECT
    QString m_text;

public:
    explicit EntityWidget(QWidget *parent = 0);
    void SetText(QString text);
    ~EntityWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EntityWidget *ui;
};

#endif // ENTITYWIDGET_H
