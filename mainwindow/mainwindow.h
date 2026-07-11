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

#include <QtCore/QItemSelectionModel>
#include <QtCore/QAbstractItemModel>

#include <QtWidgets/QUndoView>
#include <QtWidgets/QSplashScreen>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtGui/QCloseEvent>

#include "about.h"
#include "preferences.h"
#include "navigationviewmodel.h"

#include <QtCore/QDebug>

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

public slots:
    void editMenuAboutToShow();
    void editMenuAboutToHide();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    int aboutToClose();
    void currentRowChange(const QModelIndex &current, const QModelIndex &previous);
    /*!
     * \brief closeRequest explicit call to close the QApplication
     *
     * Runs through \sa aboutToClose() before closing or ignoring.
     */
    void closeRequest();

private:

    void setup();

    Ui::MainWindow *ui;
    About *aboutWindow;
    Preferences *preferencesWindow;
    NavigationViewModel* _nav_model;
    QItemSelectionModel* _select_model;
    QStatusBar *statusBar;
    QtMenuGen* menugen;

    QUndoGroup* _undo_group;
    QAction* _undo_action;
    QAction* _redo_action;
    QMenu* _edit_menu;
};

#endif // MAINWINDOW_H
