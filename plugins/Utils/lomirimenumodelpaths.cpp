/*
 * Copyright (C) 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Nick Dedekind <nick.dedekind@canonical.com>
 */


#include "lomirimenumodelpaths.h"
#include <QDBusArgument>

static QVariant parseVariantData(const QVariant& var);

const QDBusArgument &operator>>(const QDBusArgument &arg, QVariantMap &map)
{
    arg.beginMap();
    map.clear();
    while (!arg.atEnd()) {
        QString key;
        QVariant value;
        arg.beginMapEntry();

        arg >> key >> value;
        map.insertMulti(key, parseVariantData(value)); // re-parse for qdbusargument

        arg.endMapEntry();
    }
    arg.endMap();
    return arg;
}

static QVariant parseVariantData(const QVariant& var) {
    if ((int)var.type() == QMetaType::User && var.userType() == qMetaTypeId<QDBusArgument>()) {
        QDBusArgument arg(var.value<QDBusArgument>());
        if (arg.currentType() == QDBusArgument::MapType) {
            QVariantMap map;
            arg >> map;
            return map;
        }
        return arg.asVariant();
    }

    return var;
}

LomiriMenuModelPaths::LomiriMenuModelPaths(QObject *parent)
    : QObject(parent)
{
}

QVariant LomiriMenuModelPaths::source() const
{
    return m_sourceData;
}

void LomiriMenuModelPaths::setSource(const QVariant& data)
{
    if (m_sourceData != data) {
        m_sourceData = data;
        Q_EMIT sourceChanged();

        updateData();
    }
}

void LomiriMenuModelPaths::updateData()
{
    QVariantMap dataMap = parseVariantData(m_sourceData).toMap();

    if (!m_busNameHint.isEmpty() && dataMap.contains(m_busNameHint)) {
        setBusName(dataMap[m_busNameHint].toByteArray());
    } else {
        setBusName("");
    }

    if (!m_menuObjectPathHint.isEmpty() && dataMap.contains(m_menuObjectPathHint)) {
        setMenuObjectPath(dataMap[m_menuObjectPathHint].toByteArray());
    } else {
        setMenuObjectPath("");
    }

    if (!m_actionsHint.isEmpty() && dataMap.contains(m_actionsHint)) {
        setActions(dataMap[m_actionsHint].toMap());
    } else {
        setActions(QVariantMap());
    }
}

QByteArray LomiriMenuModelPaths::busName() const
{
    return m_busName;
}

void LomiriMenuModelPaths::setBusName(const QByteArray &name)
{
    if (m_busName != name) {
        m_busName = name;
        Q_EMIT busNameChanged();
    }
}

QVariantMap LomiriMenuModelPaths::actions() const
{
    return m_actions;
}

void LomiriMenuModelPaths::setActions(const QVariantMap &actions)
{
    if (m_actions != actions) {
        m_actions = actions;
        Q_EMIT actionsChanged();
    }
}

QByteArray LomiriMenuModelPaths::menuObjectPath() const
{
    return m_menuObjectPath;
}

void LomiriMenuModelPaths::setMenuObjectPath(const QByteArray &path)
{
    if (m_menuObjectPath != path) {
        m_menuObjectPath = path;
        Q_EMIT menuObjectPathChanged();
    }
}

QByteArray LomiriMenuModelPaths::busNameHint() const
{
    return m_busNameHint;
}

void LomiriMenuModelPaths::setBusNameHint(const QByteArray &nameHint)
{
    if (m_busNameHint != nameHint) {
        m_busNameHint = nameHint;
        Q_EMIT busNameHintChanged();

        updateData();
    }
}

QByteArray LomiriMenuModelPaths::actionsHint() const
{
    return m_actionsHint;
}

void LomiriMenuModelPaths::setActionsHint(const QByteArray &actionsHint)
{
    if (m_actionsHint != actionsHint) {
        m_actionsHint = actionsHint;
        Q_EMIT actionsHintChanged();

        updateData();
    }
}

QByteArray LomiriMenuModelPaths::menuObjectPathHint() const
{
    return m_menuObjectPathHint;
}

void LomiriMenuModelPaths::setMenuObjectPathHint(const QByteArray &pathHint)
{
    if (m_menuObjectPathHint != pathHint) {
        m_menuObjectPathHint = pathHint;
        Q_EMIT menuObjectPathHintChanged();

        updateData();
    }
}