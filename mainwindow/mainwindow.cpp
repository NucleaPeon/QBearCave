#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->aboutWindow = new About();
    this->preferencesWindow = new Preferences();

    this->menugen = new QtMenuGen(":/menus/mainwindow.json");
    this->menugen->setup(this, this);
    qDebug() << this->menugen->menus();

   this->_undo_group = new QUndoGroup(this);
   this->_undo_action = this->menugen->actionByName("undo");
   this->_redo_action = this->menugen->actionByName("redo");
   this->_edit_menu = this->menugen->menuByName("Edit");

   connect(this->_edit_menu, SIGNAL(aboutToShow()),
               this, SLOT(editMenuAboutToShow()));
   connect(this->_edit_menu, SIGNAL(aboutToHide()),
           this, SLOT(editMenuAboutToHide()));

   this->statusBar = new QStatusBar();
   this->setStatusBar(this->statusBar);
   this->statusBar->showMessage("Ready.");
}


void MainWindow::editMenuAboutToShow()
{
    qDebug() << Q_FUNC_INFO;
   if (this->_undo_group->stacks().count() == 0) {
       this->_undo_action->setText("Undo");
       this->_undo_action->setEnabled(false);
       this->_redo_action->setText("Redo");
       this->_redo_action->setEnabled(false);
       return;
   }
   if (this->_undo_group->canUndo()) {
       this->_undo_action->setText(QString("Undo %1").arg(this->_undo_group->undoText()));
   } else {
       this->_undo_action->setText("Undo");
   }
   this->_undo_action->setEnabled(this->_undo_group->canUndo());
   if (this->_undo_group->canRedo()) {
       this->_redo_action->setText(QString("Redo %1").arg(this->_undo_group->redoText()));
   } else {
       this->_redo_action->setText("Redo");
   }
   this->_redo_action->setEnabled(this->_undo_group->canRedo());
}

void MainWindow::editMenuAboutToHide()
{
    qDebug() << Q_FUNC_INFO;
}

int MainWindow::aboutToClose()
{
    qDebug() << Q_FUNC_INFO;
    // Put closing checks in this function
    return QDialog::Accepted;
}

void MainWindow::closeRequest()
{
    this->close();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    int code = this->aboutToClose();
    if (code == QDialog::Accepted)
        event->accept();
    else
        event->ignore();
}

MainWindow::~MainWindow()
{
    delete ui;
}
