#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <scene.h>
#include "obstacle.h"
#include "clouds.h"
#include "skateitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
   void hideButtons();
   void showButtons();
   void setupButtonsTimer();

private slots:
    void on_startButton_clicked();

    void on_closeButton_clicked();

    void on_clasamentButton_clicked();

    void on_CreateButton_clicked();

    void on_logginButton_clicked();

    void on_Cancel_clicked();

    void on_Create_clicked();

    void on_LoginButton_clicked();

    void on_Logout_clicked();

    void getTopList();
    void on_closeTopScore_clicked();

private:
    Ui::Widget *ui;
    Scene *scene;
    QTimer *buttonsTimer;
    void hiddeCreateButtons();
    QString *currentUser;
};
#endif // WIDGET_H
