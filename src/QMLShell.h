#ifndef QMLSHELL_H
#define QMLSHELL_H

#include "ShellView.h"

#include <QtQml/qqmlengine.h>
#include <QtGui/qguiapplication.h>
#include <QQuickView>
#include <QScopedPointer>

class QMLShell : public QGuiApplication
{
    Q_OBJECT
public:
    QMLShell(int &argc, char **argv);
    virtual ~QMLShell();

    void destroyResources();

private Q_SLOTS:
    void onScreenAdded(QScreen *);
    void onScreenRemoved(QScreen *);

private:
    ShellView *m_shellView{nullptr};
    void setupQmlEngine();
    QQmlEngine *m_qmlEngine{nullptr};
};

#endif // QMLSHELL_H