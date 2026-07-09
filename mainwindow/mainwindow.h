#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore/QtGlobal>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStatusBar>

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QtWidgets/QAction>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QUndoGroup>
#else
#include <QtGui/QAction>
#include <QtGui/QUndoStack>
#include <QtGui/QUndoGroup>
#endif

#include "about.h"
#include "preferences.h"

#include <qt5menugen.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu *mainMenu;
    QMenuBar *mainMenuBar;
    QAction *aboutAction;
    QAction *preferencesAction;
    About *aboutWindow;
    Preferences *preferencesWindow;
    QStatusBar *statusBar;
};

#endif // MAINWINDOW_H
