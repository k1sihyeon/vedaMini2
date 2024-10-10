#include "loginwidget.h"

#include <QtGui>
#include <QtWidgets>

LoginWidget::LoginWidget(QWidget *parent) : QWidget{parent}
{
    inputID = new QLineEdit(this);
    inputID->setPlaceholderText(tr("Input ID"));

    inputPW = new QLineEdit(this);
    inputPW->setPlaceholderText(tr("Input PassWord"));

    submitBtn = new QPushButton("Login", this);

    registerBtn = new QPushButton("Create Account", this);

    //connect(inputID, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(inputPW, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));
    connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerAct()));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(inputID);
    mainLayout->addWidget(inputPW);
    mainLayout->addWidget(submitBtn);
    mainLayout->addWidget(registerBtn);


}

void LoginWidget::submit() {

}

void LoginWidget::registerAct() {

}
