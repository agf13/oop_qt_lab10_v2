#include "mainwindow.h"

#include <QApplication>

#include "adminwindow.h"
#include "clientwindow.h"
#include "repository.h"
#include "service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow *main = new MainWindow();
//    main->show();

    //init repo and service
    Repository<Dog> *repo = new Repository<Dog>();
    Service *serv = new Service(repo);

    AdminWindow *aw = new AdminWindow();
    aw->setService(serv);
    aw->show();

    ClientWindow *cw = new ClientWindow();
    Repository<Dog> *clientRepo = new Repository<Dog>();
    Service *clientService = new Service(clientRepo);
    cw->setMainService(serv);
    cw->setAdoptService(clientService);
    cw->show();

    QObject::connect(aw, &AdminWindow::widgetUpdated, cw, &ClientWindow::refreshStore);

    return a.exec();
}
