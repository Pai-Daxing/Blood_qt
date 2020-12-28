#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit SqlQueryModel(QObject *parent = nullptr);
    ~SqlQueryModel();

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void refresh();


};
#endif // SIMPLEQUERYMODEL_H
//#pragma once
//#include <QSqlQueryModel>
//#include <QTimer>
//#include <QObject>

//class SqlQueryModel : public QSqlQueryModel
//{
//    Q_OBJECT

//public:
//    explicit SqlQueryModel(QObject *parent = 0);

//    void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
//    void setQuery(const QSqlQuery &query);
//    Q_INVOKABLE void refresh();
//    QVariant data(const QModelIndex &index, int role) const;
//    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

//private:
//    void generateRoleNames();
//    QHash<int, QByteArray> m_roleNames;
//};

