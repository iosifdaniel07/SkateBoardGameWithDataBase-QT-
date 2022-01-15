#ifndef SQLLITEHANDLER_H
#define SQLLITEHANDLER_H
#include <QtSql>
#include <QtDebug>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

class SqlLiteHandler
{

public:
    static bool createAccount(QString password,QString username, int scor ){

        const QString DRIVER("QSQLITE");

        if(QSqlDatabase::isDriverAvailable(DRIVER)){

         QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

          db.setDatabaseName("D:/Teme/C++(QT)/QtGameFinalv2DataBase/SkateboardGame/DataBase/db.sqlite");

                if(!db.open())
                  qWarning() << "ERROR: " << db.lastError();
                else{

                    QSqlQuery queryInsert;

                    QSqlQuery query("CREATE TABLE users (Id INTEGER PRIMARY KEY UNIQUE NOT NULL, Password TEXT NOT NULL, Username TEXT UNIQUE NOT NULL, Scor INTEGER NOT NULL)");
                    if(!query.isActive())
                        qWarning() << "ERROR: " << query.lastError().text();

                    queryInsert.prepare("INSERT INTO users (Password, Username, Scor) VALUES (:password, :username, :scor)");
                    queryInsert.bindValue(":password", password);
                    queryInsert.bindValue(":username", username);
                    queryInsert.bindValue(":scor", scor);

                    if(!queryInsert.exec()){
                      qWarning() << "ERROR: " << queryInsert.lastError().text();
                       db.close();
                    }else{
                        qDebug() << "Inserat cu succes!";
                         db.close();
                        return true;
                    }

                }

        }else{
             qDebug() << "nu exista";
        }

     return false;
   }


    static QString selectUsername(QString username){

         const QString DRIVER("QSQLITE");

         if(QSqlDatabase::isDriverAvailable(DRIVER)){

          QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

           db.setDatabaseName("D:/Teme/C++(QT)/QtGameFinalv2DataBase/SkateboardGame/DataBase/db.sqlite");

            if(!db.open()){
                 qWarning() << "ERROR: " << db.lastError();
            }else{
                QSqlQuery querySelect;
                querySelect.prepare("SELECT Username FROM users WHERE Username = :username");
                querySelect.bindValue(":username", username);

                if(!querySelect.exec())
                  qWarning() << "ERROR: " << querySelect.lastError().text();
                else{

                    if(querySelect.first()){
                        db.close();
                     return querySelect.value(0).toString();
                    }else
                     qDebug() << "account not found";
                }

            }
             db.close();
         }

         return "";
    }


    static QString selectPassword(QString username){

         const QString DRIVER("QSQLITE");

         if(QSqlDatabase::isDriverAvailable(DRIVER)){

          QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

           db.setDatabaseName("D:/Teme/C++(QT)/QtGameFinalv2DataBase/SkateboardGame/DataBase/db.sqlite");

            if(!db.open()){
                 qWarning() << "ERROR: " << db.lastError();
            }else{
                QSqlQuery querySelect;
                querySelect.prepare("SELECT Password FROM users WHERE Username = :username");
                querySelect.bindValue(":username", username);

                if(!querySelect.exec())
                  qWarning() << "ERROR: " << querySelect.lastError().text();
                else{
                    if(querySelect.first()){
                        db.close();
                     return querySelect.value(0).toString();
                    }else
                     qDebug() << "account not found(pass)";
                }

            }

           db.close();
         }
         return "";
    }

    static void updateScore(QString username, int scor){

        const QString DRIVER("QSQLITE");

        if(QSqlDatabase::isDriverAvailable(DRIVER)){

         QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

          db.setDatabaseName("D:/Teme/C++(QT)/QtGameFinalv2DataBase/SkateboardGame/DataBase/db.sqlite");

           if(!db.open()){
                qWarning() << "ERROR: " << db.lastError();
           }else{
               QSqlQuery querySelect;
               querySelect.prepare("UPDATE users SET Scor = :scor WHERE Username = :username");
               querySelect.bindValue(":scor", scor);
               querySelect.bindValue(":username", username);

               if(!querySelect.exec())
                 qWarning() << "ERROR: " << querySelect.lastError().text();
               else{

                    qDebug() << "Scor actualizat";
               }

           }

          db.close();
        }

    }

    static int getScore(QString username){

        const QString DRIVER("QSQLITE");

        if(QSqlDatabase::isDriverAvailable(DRIVER)){

         QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

          db.setDatabaseName("C:/Users/Daniel/Desktop/SkateboardGame/DataBase/db.sqlite");

           if(!db.open()){
                qWarning() << "ERROR: " << db.lastError();
           }else{
               QSqlQuery querySelect;
               querySelect.prepare("SELECT Scor FROM users WHERE Username = :username");
               querySelect.bindValue(":username", username);

               if(!querySelect.exec())
                 qWarning() << "ERROR: " << querySelect.lastError().text();
               else{
                   if(querySelect.first()){
                       db.close();
                    return querySelect.value(0).toInt();
                   }else
                    qDebug() << "account not found";
               }

           }

          db.close();
        }
        return 0;
    }

};



#endif // SQLLITEHANDLER_H
