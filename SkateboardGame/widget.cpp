#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include "sqllitehandler.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(1700,790);

    scene = new Scene(this);
    scene->setSceneRect(0,0,1750,796);

    currentUser = new QString("");

    hiddeCreateButtons();

    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(QPixmap(":/Images/background.png"));
    pixItem->setZValue(-1);
    scene->addItem(pixItem);

    QPixmap iconPixmap(":/Images/start.png");
    QIcon pixmapIcon(iconPixmap);
    ui->startButton->setIcon(pixmapIcon);
    ui->startButton->setIconSize(iconPixmap.rect().size());
    ui->startButton->setFixedSize(iconPixmap.rect().size());


     QPixmap iconPixmap2(":/Images/exit.png");
     QIcon pixmapIcon2(iconPixmap2);
     ui->closeButton->setIcon(pixmapIcon2);
     ui->closeButton->setIconSize(iconPixmap2.rect().size());
     ui->closeButton->setFixedSize(iconPixmap2.rect().size());

      QPixmap iconPixmap3(":/Images/create.png");
      QIcon pixmapIcon3(iconPixmap3);
      ui->CreateButton->setIcon(pixmapIcon3);
      ui->CreateButton->setIconSize(iconPixmap3.rect().size());
      ui->CreateButton->setFixedSize(iconPixmap3.rect().size());

      QPixmap iconPixmap4(":/Images/login.png");
      QIcon pixmapIcon4(iconPixmap4);
      ui->logginButton->setIcon(pixmapIcon4);
      ui->logginButton->setIconSize(iconPixmap4.rect().size());
      ui->logginButton->setFixedSize(iconPixmap4.rect().size());

      QPixmap iconPixmap5(":/Images/Logout.png");
      QIcon pixmapIcon5(iconPixmap5);
      ui->Logout->setIcon(pixmapIcon5);
      ui->Logout->setIconSize(iconPixmap5.rect().size());
      ui->Logout->setFixedSize(iconPixmap5.rect().size());

      QPixmap iconPixmap6(":/Images/clasament.png");
      QIcon pixmapIcon6(iconPixmap6);
      ui->clasamentButton->setIcon(pixmapIcon6);
      ui->clasamentButton->setIconSize(iconPixmap6.rect().size());
      ui->clasamentButton->setFixedSize(iconPixmap6.rect().size());


    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1800,800);

    setupButtonsTimer();
}

Widget::~Widget()
{
    delete buttonsTimer;
    delete scene;
    delete ui;
    delete currentUser;
}

void Widget::hideButtons()
{
    ui->startButton->hide();
    ui->closeButton->hide();
    ui->logginButton->hide();
    ui->clasamentButton->hide();
    ui->CreateButton->hide();
    ui->Logout->hide();
    ui->closeTopScore->hide();
}

void Widget::showButtons()
{
    ui->startButton->show();
    ui->closeButton->show();
    ui->logginButton->show();
    ui->clasamentButton->show();
    ui->CreateButton->show();
    ui->Logout->show();
}

void Widget::setupButtonsTimer()
{
    buttonsTimer = new QTimer();

    connect(buttonsTimer,&QTimer::timeout, [=] () {

        connect(scene,&Scene::showButtons,[=](){
           showButtons();
        });


    });

     buttonsTimer->start(100);
}


void Widget::on_startButton_clicked()
{
    if(*currentUser != ""){
    scene->startGame();
    hideButtons();
    }else{
        ui->labelMesaj->clear();
        ui->labelMesaj->setText("Nu sunteti conectat!");
        ui->labelMesaj->show();

         QTimer::singleShot(3000, ui->labelMesaj, &QLabel::hide);
    }
}

void Widget::on_closeButton_clicked()
{
    this->close();
}

void Widget::on_clasamentButton_clicked()
{
    scene->hideScoreGame();
    scene->hideGameOverGraphics();

    getTopList();
    ui->closeTopScore->show();
}

void Widget::on_CreateButton_clicked()
{
    scene->hideScoreGame();
    scene->hideGameOverGraphics();

    hideButtons();
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->Cancel->show();
    ui->Create->show();
    ui->lineEditPassword->clear();
    ui->lineEditUsername->clear();
    ui->lineEditPassword->show();
    ui->lineEditUsername->show();
    ui->UsernameLabel->show();
    ui->UsernameLabel_2->show();

}

void Widget::on_logginButton_clicked()
{
    scene->hideScoreGame();
    scene->hideGameOverGraphics();

    hideButtons();
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->Cancel->show();
    ui->LoginButton->show();
    ui->lineEditPassword->clear();
    ui->lineEditUsername->clear();
    ui->lineEditPassword->show();
    ui->lineEditUsername->show();
    ui->UsernameLabel->show();
    ui->UsernameLabel_2->show();
}

void Widget::hiddeCreateButtons()
{
    ui->Cancel->hide();
    ui->Create->hide();
    ui->lineEditPassword->hide();
    ui->lineEditUsername->hide();
    ui->UsernameLabel->hide();
    ui->UsernameLabel_2->hide();
    ui->labelMesaj->hide();
    ui->LoginButton->hide();
    ui->listWidget->hide();
    ui->closeTopScore->hide();
}

void Widget::on_Cancel_clicked()
{
    hiddeCreateButtons();
    showButtons();
}

void Widget::on_Create_clicked()
{

    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    if(username != "" && password != ""){

    bool test = SqlLiteHandler::createAccount(password,username,0);
    if(!test){
       ui->labelMesaj->clear();
       ui->labelMesaj->setText("Userul exista deja");
        ui->labelMesaj->show();
    }else{
        ui->labelMesaj->clear();
        ui->labelMesaj->setText("Cont creat cu succes");
        ui->labelMesaj->show();
    }

    }else{
        ui->labelMesaj->clear();
        ui->labelMesaj->setText("Nu ati completat toate campurile");
        ui->labelMesaj->show();
    }
}

void Widget::on_LoginButton_clicked()
{

    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

     if(username != "" && password != ""){

         QString dataBaseUser = SqlLiteHandler::selectUsername(username);
        if(dataBaseUser == username){

             QString dataBasePassword = SqlLiteHandler::selectPassword(username);
            if(password == dataBasePassword){
                currentUser = new QString(username);
                scene->updateUser(currentUser);
                ui->labelMesaj->clear();
                ui->labelMesaj->setText("Connectat cu succes!");
                ui->labelMesaj->show();

            }else{
                ui->labelMesaj->clear();
                ui->labelMesaj->setText("Password gresit!");
                ui->labelMesaj->show();
            }

        }else{
            ui->labelMesaj->clear();
            ui->labelMesaj->setText("Usernameul nu exista!");
            ui->labelMesaj->show();
        }

     }else{
         ui->labelMesaj->clear();
         ui->labelMesaj->setText("Nu ati completat toate campurile");
         ui->labelMesaj->show();
     }
}

void Widget::on_Logout_clicked()
{
    scene->hideScoreGame();
    scene->hideGameOverGraphics();

    if(*currentUser != ""){
        currentUser = new QString("");
        scene->updateUser(currentUser);
        ui->labelMesaj->clear();
        ui->labelMesaj->setText("Deconectat!");
        ui->labelMesaj->show();

       QTimer::singleShot(3000, ui->labelMesaj, &QLabel::hide);

    }else{
        currentUser = new QString("");
        ui->labelMesaj->clear();
        ui->labelMesaj->setText("Nu sunteti conectat!");
        ui->labelMesaj->show();

         QTimer::singleShot(3000, ui->labelMesaj, &QLabel::hide);
    }

}

void Widget::getTopList()
{

    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER)){

     QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

      db.setDatabaseName("D:/Teme/C++(QT)/QtGameFinalv2DataBase/SkateboardGame/DataBase/db.sqlite");

      if(!db.open()){
           qWarning() << "ERROR: " << db.lastError();
      }else{

          QSqlQuery query;
          if(!query.exec("SELECT Username, Scor FROM users ORDER BY Scor DESC"))
            qWarning() << "ERROR: " << query.lastError().text();
          else{

             ui->listWidget->clear();
              while (query.next ()) {
                  QString s = query.value (0).toString ();
                  QString item = QString(s + " %1").arg(query.value (1).toInt());
                    ui->listWidget->addItem(item);
                 }
             ui->listWidget->show();
          }
      }

    }

}

void Widget::on_closeTopScore_clicked()
{
    ui->listWidget->hide();
   ui->closeTopScore->hide();
}
