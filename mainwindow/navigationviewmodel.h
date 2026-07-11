#ifndef NAVIGATIONVIEWMODEL_H
#define NAVIGATIONVIEWMODEL_H

#include <QStandardItemModel>

class NavigationViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit NavigationViewModel(QObject *parent = nullptr);


private:
};

#endif // NAVIGATIONVIEWMODEL_H
