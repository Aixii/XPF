#include "SqlResultPrivate.h"

SqlResultPrivate::SqlResultPrivate(QObject* parent)
    : QObject(parent) {
    m_error = QSqlError::NoError;
}
