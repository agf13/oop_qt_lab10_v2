#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QWidget>
#include <QSpacerItem>

#include "service.h"

class ClientWindow : public QWidget
{
    Q_OBJECT
public:
    QWidget *window;

    QHBoxLayout *storeAndAdoption_layout, *inputFields_layout;
    QVBoxLayout *allContent_layout, *storeList_layout;

    QListWidget *store_listWidget, *adoption_listWidget;

    QPushButton *adopt_button, *filter_button, *clearFilter_button;

    QLabel *filterDespription_label, *breed_label, *age_label, *systemMessage_label;

    QLineEdit *breed_input, *age_input;


    explicit ClientWindow(QWidget *parent = nullptr);
    void initQObjects();
    void positionQOBjects();
    void show();
    void hide();

    void refreshStore();
    void refreshAdoptionList();
    void populateStore(int age, std::string breed);

    void setMainService(Service *serv);
    void setAdoptService(Service *serv);

    void clearSystemMessage();

public slots:
    void filterStore();
    void adopt();

signals:
    void filterEvent();

private:
    Service *service, *adoptService;

};

#endif // CLIENTWINDOW_H
