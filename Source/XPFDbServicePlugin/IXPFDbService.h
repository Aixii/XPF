#ifndef IXPFDBSERVICE_H
#define IXPFDBSERVICE_H

#include "IXPFService.h"
#include "SqlResult.h"
#include <QSqlDriver>
#include <QString>

class IXPFDbService : public QObject
    , public IXPFService {
    Q_OBJECT
public:
    IXPFDbService()
        : QObject() { }
    ~IXPFDbService() { }

    /***
    Driver Type         Description
    QDB2                IBM DB2
    QIBASE              Borland InterBase Driver
    QMYSQL              MySQL Driver
    QOCI                Oracle Call Interface Driver
    QODBC               ODBC Driver (includes Microsoft SQL Server)
    QPSQL               PostgreSQL Driver
    QSQLITES            QLite version 3 or above
    QSQLITE2            SQLite version 2
    QTDS                Sybase Adaptive Server
    ***/
    //    virtual bool addDataBase(const QString& type, const QString& connectName) = 0;

    //    virtual bool transaction() = 0;
    //    virtual bool rollback()    = 0;
    /**
     * @brief exec 执行 sql
     * @param sql 被执行的 sql
     * @param result 执行的结果指针
     * @return sql 是否提交的结果
     */
    virtual int  exec(const QString& sql)                                   = 0;
    virtual bool execSync(const QString& sql, SqlResult** result = nullptr) = 0;

    /**
     * @brief insert 插入一行数据
     * @param tb_name 表名
     * @param valueMap 值的键值对
     * @param result 插入执行的结果
     * @return sql 是否提交的结果
     */
    virtual int  insert(const QString& tb_name, const QVariantMap& valueMap)                                   = 0;
    virtual bool insertSync(const QString& tb_name, const QVariantMap& valueMap, SqlResult** result = nullptr) = 0;

    /**
     * @brief update 更新数据
     * @param tb_name 表名
     * @param valueMap 值的键值对
     * @param conditional 条件
     * @param result 更新执行的结果
     * @return  sql 是否提交的结果
     */
    virtual int  update(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional)                                   = 0;
    virtual bool updateSync(const QString& tb_name, const QVariantMap& valueMap, const QString& conditional, SqlResult** result = nullptr) = 0;

    /**
     * @brief remove 删除数据
     * @param tb_name 表名
     * @param conditional 删除的条件
     * @param result 更新执行的结果
     * @return  sql 是否提交的结果
     */
    virtual int  remove(const QString& tb_name, const QString& conditional)                                   = 0;
    virtual bool removeSync(const QString& tb_name, const QString& conditional, SqlResult** result = nullptr) = 0;

    /**
     * @brief select 查询数据
     * @param tb_name 表名
     * @param fileds 字段列表
     * @param conditional 查询条件
     * @param result 查询执行的结果
     * @return  sql 是否提交的结果
     */
    virtual int  select(const QString& tb_name, const QStringList& fields, const QString& conditional = QString())                       = 0;
    virtual bool selectSync(const QString& tb_name, const QStringList& fields, const QString& conditional, SqlResult** result = nullptr) = 0;

signals:
    void sigSqlExecuteResult(int seq, SqlResult* result);
};

#endif // IXPFDBSERVICE_H
