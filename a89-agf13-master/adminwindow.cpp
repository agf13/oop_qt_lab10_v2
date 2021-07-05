#include "adminwindow.h"

#include <iostream>

AdminWindow::AdminWindow(QWidget *parent) : QWidget(parent)
{
    initQObjects();
    positionQObjects_admin();
    std::cout<<"Merge \n\n?";
}

void AdminWindow::initQObjects()
{
    this->window = new QWidget();

    //create layouts
    this->content_layout = new QVBoxLayout();
    this->dogDisplay_layout = new QVBoxLayout();
    this->listAndInput_layout = new QHBoxLayout();
    this->inputFields_formLayout = new QFormLayout();
    this->buttons_layout = new QHBoxLayout();
    this->addAndUpdate_layout = new QHBoxLayout();

    //add some spacing in layouts
    this->listAndInput_layout->setSpacing(this->defaultSpace);
    this->inputFields_formLayout->setSpacing(this->defaultSpace);
    this->buttons_layout->setSpacing(this->defaultSpace);

    //create list widget
    this->dogDisplay_widget = new QListWidget();
    this->elementCount_label = new QLabel();

    QObject::connect(this->dogDisplay_widget, &QListWidget::itemClicked, this, &AdminWindow::showDog);


    //create input fields
    this->inputName = new QLineEdit();
    this->inputBreed = new QLineEdit();
    this->inputAge = new QLineEdit();
    this->inputPhoto = new QLineEdit();

    //add the labels for the input fields
    this->labelName = new QLabel("Name ");
    this->labelBreed = new QLabel("Breed ");
    this->labelAge = new QLabel("Age ");
    this->labelPhoto = new QLabel("Photo ");


    //create buttons
    this->clear_button = new QPushButton("Clear");
    this->add_button = new QPushButton("Add");
    this->update_button = new QPushButton("Update");
    this->remove_button = new QPushButton("Remove");

//    QObject::connect(this->clear_button, &QPushButton::clicked, this, &AdminWindow::clearInputFields);
    QObject::connect(this->clear_button, &QPushButton::clicked, this, &AdminWindow::showPopUp);

    QObject::connect(this->add_button, &QPushButton::clicked, this, &AdminWindow::addDog);
    QObject::connect(this->add_button, &QPushButton::clicked, this, &AdminWindow::refreshDogList);
    QObject::connect(this->add_button, &QPushButton::clicked, this, &AdminWindow::updateElementCount);

    QObject::connect(this->update_button, &QPushButton::clicked, this, &AdminWindow::updateDog);
    QObject::connect(this->update_button, &QPushButton::clicked, this, &AdminWindow::refreshDogList);

    QObject::connect(this->remove_button, &QPushButton::clicked, this, &AdminWindow::removeDog);
    QObject::connect(this->remove_button, &QPushButton::clicked, this, &AdminWindow::refreshDogList);
    QObject::connect(this->remove_button, &QPushButton::clicked, this, &AdminWindow::updateElementCount);


    //create system message label
    this->systemMessage_label = new QLabel();

    //create shortcut
    std::cout<<"Shortcuts init...\n";
    this->undo_sequence = new QKeySequence(Qt::CTRL + Qt::Key_Shift + Qt::Key_X);
    this->redo_sequence = new QKeySequence(Qt::CTRL + Qt::Key_Z);
    this->undo_shortCut = new QShortcut(*undo_sequence, this);
    this->redo_shortCut = new QShortcut(*redo_sequence, this);

//    QObject::connect(this->undo_shortCut, &QShortcut::activated, this, &AdminWindow::clearInputFields);
//    QObject::connect(this->undo_shortCut, &QShortcut::activatedAmbiguously, this, &AdminWindow::clearInputFields);
    QObject::connect(this->undo_shortCut, &QShortcut::activated, this, &AdminWindow::showPopUp);
    QObject::connect(this->undo_shortCut, &QShortcut::activatedAmbiguously, this, &AdminWindow::showPopUp);
    std::cout<<"Shortcuts initialized\n";
    std::cout.flush();
}

//void AdminWindow::positionQObjects()
//{
//    //create the list widget and the form
//    this->inputFields_formLayout->addRow(this->labelName, this->inputName);
//    this->inputFields_formLayout->addRow(this->labelBreed, this->inputBreed);
//    this->inputFields_formLayout->addRow(this->labelAge, this->inputAge);
//    this->inputFields_formLayout->addRow(this->labelPhoto, this->inputPhoto);
//    this->inputFields_formLayout->addWidget(this->clear_button);

//    this->dogDisplay_layout->addWidget(this->dogDisplay_widget);
//    this->dogDisplay_layout->addWidget(this->elementCount_label);


//    this->listAndInput_layout->addItem(this->dogDisplay_layout);
//    this->listAndInput_layout->addItem(this->inputFields_formLayout);

//    //create the line of buttons
//    this->buttons_layout->addWidget(this->add_button);
//    this->buttons_layout->addWidget(this->update_button);
//    this->buttons_layout->addWidget(this->remove_button);

//    //add everything to the main layout (which is the content_layout)
//    this->content_layout->addItem(this->listAndInput_layout);
//    this->content_layout->addItem(this->buttons_layout);
//    this->content_layout->addWidget(this->systemMessage_label);

//    this->window->setLayout(this->content_layout);
//}
void AdminWindow::positionQObjects_admin()
{
    //create the list widget and the form
    //<inputFields_formLayout>
    this->inputFields_formLayout->addRow(this->labelName, this->inputName);
    this->inputFields_formLayout->addRow(this->labelBreed, this->inputBreed);
    this->inputFields_formLayout->addRow(this->labelAge, this->inputAge);
    this->inputFields_formLayout->addRow(this->labelPhoto, this->inputPhoto);
    this->inputFields_formLayout->addWidget(this->clear_button);

    this->addAndUpdate_layout->addWidget(this->add_button);
    this->addAndUpdate_layout->addWidget(this->update_button);
    this->inputFields_formLayout->addItem(this->addAndUpdate_layout);

    //</inputFields_formLayout>

    //<dogDisplay_layout>
    this->dogDisplay_layout->addWidget(this->dogDisplay_widget);
    this->dogDisplay_layout->addWidget(this->elementCount_label);
    this->dogDisplay_layout->addWidget(this->remove_button);
    //<dogDisplay_layout>

    //<listAndInput_layout>
    this->listAndInput_layout->addItem(this->dogDisplay_layout);
    this->listAndInput_layout->addItem(this->inputFields_formLayout);
    //</listAndInput_layout>


    //create the line of buttons
    //<buttons_layout>
//    this->buttons_layout->addWidget(this->add_button);
//    this->buttons_layout->addWidget(this->update_button);
//    this->buttons_layout->addWidget(this->remove_button);
    //<buttons_layout>

    //add everything to the main layout (which is the content_layout)
    //<content>
    this->content_layout->addItem(this->listAndInput_layout);
    this->content_layout->addItem(this->buttons_layout);
    this->content_layout->addWidget(this->systemMessage_label);
    //</content>

    this->window->setLayout(this->content_layout);
}

void AdminWindow::show()
{
    this->window->show();
}

void AdminWindow::hide()
{
    this->window->hide();
}

void AdminWindow::setService(Service *service)
{
    this->service = service;
    this->service->initRepositoryFromFile();
    this->refreshDogList();
    this->updateElementCount();
}

void AdminWindow::refreshDogList()
{
    this->dogDisplay_widget->clear();

    for(Dog* dog : this->service->getAll())
    {
        std::string csvLine = dog->toCsvLine();
        QString line = QString::fromStdString(csvLine);
        this->dogDisplay_widget->addItem(line);
    }
}

void AdminWindow::clearSystemMessage()
{
    this->systemMessage_label->clear();
}

void AdminWindow::writeDog_systemMessage()
{
    QString output = this->inputName->text() + ",";
    output += this->inputBreed->text() + ",";
    output += this->inputAge->text() + ",";
    output += this->inputPhoto->text();

    this->systemMessage_label->setText(output);
}

void AdminWindow::addDog()
{
    this->clearSystemMessage();

    std::string name = this->inputName->text().toStdString();
    std::string breed = this->inputBreed->text().toStdString();
    int age = this->inputAge->text().toInt();
    std::string photograph = this->inputPhoto->text().toStdString();

    try
    {
        ValidatorDog::validate(name, breed, age, photograph);
        Dog* newDog = new Dog(name, breed, age, photograph);
        this->service->add(newDog);
        emit(widgetUpdated());
    }
    catch(ValidatorError e)
    {
        this->systemMessage_label->setText("Invalid dog parameters");
    }
    catch(DuplicateError e)
    {
        this->systemMessage_label->setText("Dublicate found. Name already taken");
    }
}

void AdminWindow::updateDog()
{
    this->clearSystemMessage();

    std::string name = this->inputName->text().toStdString();
    std::string breed = this->inputBreed->text().toStdString();
    int age = this->inputAge->text().toInt();
    std::string photograph = this->inputPhoto->text().toStdString();

    try
    {
        ValidatorDog::validate(name, breed, age, photograph);
        Dog* newDog = new Dog(name, breed, age, photograph);
        this->service->update(newDog);
        emit(widgetUpdated());
    }
    catch(ValidatorError e)
    {
        this->systemMessage_label->setText("Invalid dog parameters");
    }
    catch(DuplicateError e)
    {
        this->systemMessage_label->setText("Dublicate found. Name already taken");
    }
    catch(UnexistingElement e)
    {
        this->systemMessage_label->setText("No dog found with the given name");
    }

}

void AdminWindow::removeDog()
{
    this->clearSystemMessage();

    std::string name = this->inputName->text().toStdString();
    try
    {
        this->service->remove(name);
        emit(widgetUpdated());
    }
    catch(UnexistingElement e)
    {
        this->systemMessage_label->setText("No dog found with the given name");
    }
}

void AdminWindow::showDog(QListWidgetItem *currentItem)
{
    std::string text = currentItem->text().toStdString();
    Dog dog(text);

    this->inputName->setText(QString::fromStdString(dog.getName()));
    this->inputBreed->setText(QString::fromStdString(dog.getBreed()));
    this->inputAge->setText(QString::number(dog.getAge()));
    this->inputPhoto->setText(QString::fromStdString(dog.getPhotograph()));
}

void AdminWindow::clearInputFields()
{
    this->inputName->clear();
    this->inputBreed->clear();
    this->inputAge->clear();
    this->inputPhoto->clear();

    this->systemMessage_label->clear();
}

void AdminWindow::updateElementCount()
{
    int numberElements = this->dogDisplay_widget->count();
    std::string message = std::to_string(numberElements) + " elements";

    this->elementCount_label->setText(QString::fromStdString(message));
}

void AdminWindow::showPopUp()
{
    QWidget *newWindow = new QWidget();
    newWindow->show();
}


void AdminWindow::setupButtons()
{
    QObject::connect(this->add_button, &QAbstractButton::clicked, this, &AdminWindow::addDog);
}


