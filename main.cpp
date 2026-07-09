#include <QtCore/QtGlobal>
#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "mainwindow/mainwindow.h"
#include "version.h"

#ifdef Q_OS_MAC
#include "cocoainitializer.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("PeonDevelopments");
    QApplication::setOrganizationDomain("peondevelopments.com");
    QApplication::setApplicationName("QBearCave");
    QApplication::setApplicationVersion(QString("%1.%2.%3.%4")
            .arg(QBearCave::Version::RELEASE)
            .arg(QBearCave::Version::MAJOR)
            .arg(QBearCave::Version::MINOR)
            .arg(QBearCave::Version::PATCH));

    QCommandLineParser parser; // See help documentation on this for complex/calling method functionality
    parser.setApplicationDescription(
        QCoreApplication::translate(
            QApplication::applicationName().toStdString().c_str(),
            "Qt-based Precious Metals Organization Application"));
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    QPixmap pixmap(":/icons/Logo");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

#ifdef Q_OS_MAC
    CocoaInitializer initializer;
    Q_UNUSED(initializer)
#endif
    MainWindow w;
    w.show();
    splash->hide();
    return a.exec();
}
