#include "SqlResultPrivate.h"

SqlResultPrivate::SqlResultPrivate(QObject* parent)
    : QObject(parent) {
}

SqlResultPrivate::~SqlResultPrivate() {
}

void SqlResultPrivate::setError(const QSqlError& error) {
    m_error = error;
}
