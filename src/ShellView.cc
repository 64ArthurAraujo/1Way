#include "ShellView.h"

#include <QQmlContext>
#include <QQuickItem>
#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickrectangle_p.h>
#include <QtQuick/private/qquicktext_p.h>

#include <paths.h>

ShellView::ShellView(QQmlEngine *engine) : QQuickView(engine, nullptr)
{
    setResizeMode(QQuickView::SizeRootObjectToView);
    setColor("black");
    setTitle(QStringLiteral("1Way Desktop"));

    connect(this, &QQuickView::statusChanged, this, [this]
            {
            if (status() == QQuickView::Error) {
                QQuickRectangle *rect = new QQuickRectangle(contentItem());
                rect->setColor(Qt::white);
                QQuickItemPrivate::get(rect)->anchors()->setFill(contentItem());

                QString errorsString;
                for(const QQmlError &e: errors()) {
                    errorsString += e.toString() + "\n";
                }
                QQuickText *text = new QQuickText(rect);
                text->setColor(Qt::black);
                text->setWrapMode(QQuickText::Wrap);
                text->setText(QString("Failed to run 1Way:\n%1").arg(errorsString));
                QQuickItemPrivate::get(text)->anchors()->setFill(rect);
            } });

    QUrl source("/home/arthur/src/1Way/qml/Shell.qml");
    setSource(source);

    connect(this, &QWindow::widthChanged, this, &ShellView::onWidthChanged);
    connect(this, &QWindow::heightChanged, this, &ShellView::onHeightChanged);
}

void ShellView::onWidthChanged(int w)
{
    if (rootObject())
    {
        rootObject()->setWidth(w);
    }
}

void ShellView::onHeightChanged(int h)
{
    if (rootObject())
    {
        rootObject()->setHeight(h);
    }
}