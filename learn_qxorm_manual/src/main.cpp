#include <QCoreApplication>
#include <QDebug>
#include <person.hpp>

QString getDBName();

int main(int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "main start!";

    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName(getDBName());
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");
    QSqlError dbError;
    do
    {
        dbError = qx::dao::create_table<Person>();
        if (dbError.isValid())
        {
            qCritical() << "Create table failed:" << dbError.text();
            break;
        }
    } while (false);
    qDebug() << "main stop!";
    // return a.exec();
    return 0;
}

#include <QFile>
#include <mutex>

QString getDBName()
{
    QString dbName;
    std::once_flag once;
    std::call_once(once, [](QString &dbName) {
        dbName = QCoreApplication::applicationDirPath() + "/MyDemo.db";
        qDebug() << "DB name:" << dbName;
        QFile file(dbName);
        if (file.exists())
        {
            qDebug() << "Delete file:" << dbName;
            if (!file.remove())
            {
                qCritical() << "Delete file failed:" << dbName;
            }
        }
    }, dbName);
    return dbName;
}