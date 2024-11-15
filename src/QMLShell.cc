#include "QMLShell.h"

#include <QLibrary>
#include <QProcess>
#include <QScreen>
#include <QtGui/qguiapplication.h>
#include <QtQml/QQmlExtensionPlugin>
#include <paths.h>
#include <QDesktopServices>

QMLShell::QMLShell(int &argc, char **argv) : QGuiApplication(argc, argv)
{
    setApplicationName(QStringLiteral("1Way"));
    setApplicationDisplayName(QStringLiteral("1Way"));

    connect(this, &QGuiApplication::screenAdded, this, &QMLShell::onScreenAdded);
    connect(this, &QGuiApplication::screenRemoved, this, &QMLShell::onScreenRemoved);

    setupQmlEngine();

    m_shellView = new ShellView(m_qmlEngine);

    m_shellView->showFullScreen();
}

QMLShell::~QMLShell()
{
    destroyResources();
}

void QMLShell::destroyResources()
{
    delete m_shellView;
    m_shellView = nullptr;

    delete m_qmlEngine;
    m_qmlEngine = nullptr;
}

void QMLShell::setupQmlEngine()
{
    m_qmlEngine = new QQmlEngine(this);

    m_qmlEngine->setBaseUrl(QUrl::fromLocalFile("/home/arthur/src/1Way/qml/"));
    m_qmlEngine->addImportPath(QStringLiteral("/home/arthur/src/1Way/build/plugins"));

    QObject::connect(m_qmlEngine, &QQmlEngine::quit, this, &QGuiApplication::quit);
}

void QMLShell::onScreenAdded(QScreen *)
{
}

void QMLShell::onScreenRemoved(QScreen *)
{
}
