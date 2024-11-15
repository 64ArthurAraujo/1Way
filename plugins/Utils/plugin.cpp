/*
 * Copyright (C) 2012-2017 Canonical Ltd.
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
 */

// Qt
#include <QtQml/qqml.h>
#include <QDBusConnection>
#include <QQmlContext>
#include <QtQuick/QQuickWindow>
// self
#include "plugin.h"

// local
#include "activefocuslogger.h"
#include "easingcurve.h"
#include "WindowInputMonitor.h"
#include "inputwatcher.h"
#include "qlimitproxymodelqml.h"
#include "lomirisortfilterproxymodelqml.h"
#include "lomirimenumodelpaths.h"
#include "windowinputfilter.h"
#include "windowstatestorage.h"
#include "constants.h"
#include "timezoneFormatter.h"
#include "applicationsfiltermodel.h"
#include "inputeventgenerator.h"
#include "deviceconfig.h"
#include "globalfunctions.h"
#include "URLDispatcher.h"
#include "appdrawerproxymodel.h"
#include "tabfocusfence.h"
#include "expressionfiltermodel.h"
#include "quicklistproxymodel.h"

static QObject *createWindowStateStorage(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new WindowStateStorage();
}

static QObject *createConstants(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new Constants();
}

static QObject *createGlobalFunctions(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new GlobalFunctions();
}

void UtilsPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Utils"));
    qmlRegisterType<WindowInputMonitor>(uri, 0, 1, "WindowInputMonitor");
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    qmlRegisterAnonymousType<QAbstractItemModel>(uri, 0);
#else
    qmlRegisterType<QAbstractItemModel>();
#endif
    qmlRegisterType<QLimitProxyModelQML>(uri, 0, 1, "LimitProxyModel");
    qmlRegisterType<LomiriSortFilterProxyModelQML>(uri, 0, 1, "LomiriSortFilterProxyModel");
    qmlRegisterType<LomiriMenuModelPaths>(uri, 0, 1, "LomiriMenuModelPaths");
    qmlRegisterType<WindowInputFilter>(uri, 0, 1, "WindowInputFilter");
    qmlRegisterType<EasingCurve>(uri, 0, 1, "EasingCurve");
    qmlRegisterSingletonType<WindowStateStorage>(uri, 0, 1, "WindowStateStorage", createWindowStateStorage);
    qmlRegisterType<InputWatcher>(uri, 0, 1, "InputWatcher");
    qmlRegisterSingletonType<Constants>(uri, 0, 1, "Constants", createConstants);
    qmlRegisterSingletonType<TimezoneFormatter>(uri, 0, 1, "TimezoneFormatter",
                                                [](QQmlEngine*, QJSEngine*) -> QObject* { return new TimezoneFormatter; });
    qmlRegisterType<ActiveFocusLogger>(uri, 0, 1, "ActiveFocusLogger");
    qmlRegisterType<ApplicationsFilterModel>(uri, 0, 1, "ApplicationsFilterModel");
    qmlRegisterType<InputEventGenerator>(uri, 0, 1, "InputEventGenerator");
    qmlRegisterType<DeviceConfig>(uri, 0, 1, "DeviceConfig");
    qmlRegisterSingletonType<GlobalFunctions>(uri, 0, 1, "Functions", createGlobalFunctions);
    qmlRegisterType<URLDispatcher>(uri, 0, 1, "URLDispatcher");
    qmlRegisterType<AppDrawerProxyModel>(uri, 0, 1, "AppDrawerProxyModel");
    qmlRegisterType<TabFocusFenceItem>(uri, 0, 1, "TabFocusFence");
    qmlRegisterType<ExpressionFilterModel>(uri, 0, 1, "ExpressionFilterModel");
    qmlRegisterType<QuickListProxyModel>(uri, 0, 1, "QuickListProxyModel");
}