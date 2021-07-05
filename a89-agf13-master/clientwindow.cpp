#include "clientwindow.h"



ClientWindow::ClientWindow(QWidget *parent) : QWidget(parent)
{
    this->initQObjects();
    this->positionQOBjects();
}

void ClientWindow::initQObjects()
{
    this->window = new QWidget();

    this->allContent_layout = new QVBoxLayout();
    this->storeAndAdoption_layout = new QHBoxLayout();
    this->inputFields_layout = new QHBoxLayout();
    this->storeList_layout = new QVBoxLayout();

    this->store_listWidget = new QListWidget();
    this->adoption_listWidget = new QListWidget();

    this->adopt_button = new QPushButton("adopt >>");
    this->filter_button = new QPushButton("filter");
    this->clearFilter_button = new QPushButton("clear filter");

    QObject::connect(adopt_button, &QPushButton::clicked, this, &ClientWindow::adopt);

    this->filterDespription_label = new QLabel("Filter the animals from the store by using the fields below");
    this->breed_label = new QLabel("breed: ");
    this->age_label = new QLabel("age: ");
    this->systemMessage_label = new QLabel();

    this->breed_input = new QLineEdit();
    this->age_input = new QLineEdit();
}

void ClientWindow::positionQOBjects()
{
    inputFields_layout->addWidget(breed_label);
    inputFields_layout->addSpacing(10);
    inputFields_layout->addWidget(breed_input);
    inputFields_layout->addSpacing(10);
    inputFields_layout->addWidget(age_label);
    inputFields_layout->addSpacing(10);
    inputFields_layout->addWidget(age_input);

    storeList_layout->addWidget(store_listWidget);
    storeList_layout->addSpacing(10);
    storeList_layout->addWidget(filterDespription_label);
    storeList_layout->addSpacing(10);
    storeList_layout->addItem(inputFields_layout);
    storeList_layout->addSpacing(10);
    storeList_layout->addWidget(filter_button);
    storeList_layout->addSpacing(10);
    storeList_layout->addWidget(clearFilter_button);

    QObject::connect(filter_button, &QPushButton::clicked, this, &ClientWindow::filterStore);
    QObject::connect(clearFilter_button, &QPushButton::clicked, this, &ClientWindow::refreshStore);

    storeAndAdoption_layout->addItem(storeList_layout);
    storeAndAdoption_layout->addWidget(adopt_button);
    storeAndAdoption_layout->addWidget(adoption_listWidget);


    allContent_layout->addItem(storeAndAdoption_layout);
    allContent_layout->addWidget(systemMessage_label);

    window->setLayout(allContent_layout);
}

void ClientWindow::show()
{
    this->window->show();
}

void ClientWindow::hide()
{
    this->window->hide();
}

void ClientWindow::refreshStore()
{
    this->store_listWidget->clear();
    this->breed_input->clear();
    this->age_input->clear();

    for(Dog* dog : this->service->getAll())
    {
        std::string csvLine = dog->toCsvLine();
        QString line = QString::fromStdString(csvLine);
        this->store_listWidget->addItem(line);
    }
}

void ClientWindow::refreshAdoptionList()
{
    this->adoption_listWidget->clear();

    for(Dog* dog : this->adoptService->getAll())
    {
        std::string csvLine = dog->toCsvLine();
        QString line = QString::fromStdString(csvLine);
        this->adoption_listWidget->addItem(line);
    }
}

void ClientWindow::populateStore(int age, std::string breed)
{
    this->store_listWidget->clear();
    std::vector<Dog*> list = this->service->filter(age, breed);

    for(Dog* dog : this->service->filter(age, breed))
    {
        if(dog != nullptr)
        {
            std::string csvLine = dog->toCsvLine();
            QString line = QString::fromStdString(csvLine);
            this->store_listWidget->addItem(line);
        }
    }

}


void ClientWindow::setMainService(Service *serv)
{
    this->service = serv;
    this->refreshStore();
}

void ClientWindow::setAdoptService(Service *serv)
{
    this->adoptService = serv;
    refreshAdoptionList();
}

void ClientWindow::clearSystemMessage()
{
    this->systemMessage_label->clear();
}

void ClientWindow::filterStore()
{
    QString age_qString = age_input->text();
    int age = 0;

    std::string breed = breed_input->text().toStdString();

    if(!age_qString.isNull() && !(age_qString.size() == 0))
    {
        age = age_qString.toInt();
    }

    populateStore(age, breed);
}

void ClientWindow::adopt()
{
    clearSystemMessage();
    std::string text = store_listWidget->currentItem()->text().toStdString();
    Dog *dog = new Dog(text);
    try
    {
        adoptService->add(dog);
    }
    catch(DuplicateError e)
    {
        this->systemMessage_label->setText("Already adopted");
    }

    refreshAdoptionList();
}
