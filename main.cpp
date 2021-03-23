#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QQmlContext>
#include <QFontDatabase>
#include <QDebug>
#include "gestiondyna.h"
#include "GestionSequence/gestionactions.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Titi");
    app.setOrganizationDomain("Titi");

    GestionDyna gestDyna;
    GestionActions gestActions;

    QQuickView viewer;
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
    //QFontDatabase::addApplicationFont(QUrl("qrc:/fonts/icomoon.ttf").toString());
    QFontDatabase::addApplicationFont(":/fonts/icomoon.ttf");

    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                                       QString::fromLatin1("qml")));
    viewer.setTitle(QStringLiteral("Project Spider"));
    viewer.engine()->rootContext()->setContextProperty("gestDyna", &gestDyna);
    viewer.engine()->rootContext()->setContextProperty("gestActions", &gestActions);


#ifdef Q_OS_LINUX
    viewer.engine()->rootContext()->setContextProperty("fileRoot", "file://");

#elif defined(Q_OS_WIN)
    viewer.engine()->rootContext()->setContextProperty("fileRoot", "file:///");
#endif
    viewer.engine()->rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    gestActions.init(&gestDyna);
    return app.exec();
}
