#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

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
#include <QShortcut>
#include <QKeySequence>

#include "service.h"


class AdminWindow : public QWidget
{
    Q_OBJECT
public:
    QWidget *window;

    QVBoxLayout *content_layout, *dogDisplay_layout;
    QHBoxLayout *listAndInput_layout;
    QFormLayout *inputFields_formLayout;
    QHBoxLayout *buttons_layout, *addAndUpdate_layout;

    QListWidget *dogDisplay_widget;

    QLineEdit *inputName, *inputBreed, *inputAge, *inputPhoto;
    QLabel *labelName, *labelBreed, *labelAge, *labelPhoto;

    QPushButton *clear_button;
    QPushButton *add_button, *update_button, *remove_button;

    QLabel *systemMessage_label, *elementCount_label;

    QShortcut *undo_shortCut, *redo_shortCut;
    QKeySequence *undo_sequence, *redo_sequence;

    explicit AdminWindow(QWidget *parent = nullptr);
    void show();
    void hide();

    //sets the service that manages the dogs
    void setService(Service* service);

    //refreshes the list of dogs presented in the listWidget
    void refreshDogList();

    //erases the system message at the bottom of the gui
    void clearSystemMessage();

public slots:
    //writes the dog as the system message
    void writeDog_systemMessage();

    void addDog();
    void updateDog();
    void removeDog();

    //put the informations of the dog into the input fields
    void showDog(QListWidgetItem* currentItem);

    //clear the text input fields
    void clearInputFields();

    //update the label underneath the table which shows how many elements are
    void updateElementCount();

    void showPopUp();

signals:
    void widgetUpdated();
    void listUpdated();

private:
    Service *service = nullptr;
    int defaultSpace = 10;

    void initQObjects();

    //makes the connections
    void setupButtons();

    //put the objects in layouts
    void positionQObjects_admin();

};

#endif // ADMINWINDOW_H
