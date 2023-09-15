#ifndef SHELL_VIEW_H
#define SHELL_VIEW_H

#include <QQuickView>

class ShellView : public QQuickView
{
    Q_OBJECT

public:
    ShellView(QQmlEngine *engine);

private Q_SLOTS:
    void onWidthChanged(int);
    void onHeightChanged(int);
};

#endif // SHELL_VIEW_H