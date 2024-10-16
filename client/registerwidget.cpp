#include "registerwidget.h"
#include "loginwidget.h"

#include <QtWidgets>
#include <QLineEdit>
#include <QPushButton>

RegisterWidget::RegisterWidget(QWidget *parent) : QWidget{parent}
{
    inputID = new QLineEdit(this);
    inputID->setPlaceholderText(tr("Input ID"));

    inputPW = new QLineEdit(this);
    inputPW->setPlaceholderText(tr("Input Password"));

    inputName = new QLineEdit(this);
    inputName->setPlaceholderText(tr("Input Name"));

    inputPhonenum = new QLineEdit(this);
    inputPhonenum->setPlaceholderText(tr("Input Phone Number"));

    submitBtn = new QPushButton(tr("submit"), this);
    backBtn = new QPushButton(tr("back to Login"), this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(inputID);
    mainLayout->addWidget(inputPW);
    mainLayout->addWidget(inputName);
    mainLayout->addWidget(inputPhonenum);
    mainLayout->addWidget(submitBtn);
    mainLayout->addWidget(backBtn);

    connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToLogin()));
}

void RegisterWidget::submit() {
    if (inputID->text().isEmpty() || inputPW->text().isEmpty() || inputName->text().isEmpty() || inputPhonenum->text().isEmpty()) {
        QMessageBox::warning(this, tr("Register Error"), tr("something is EMPTY!"));
        return;
    }

    // DB User 삽입

    // DB로 유저 등록 완료 시 backToLogin 호출
}

void RegisterWidget::backToLogin() {
    this->close();

    LoginWidget* lw = new LoginWidget();
    lw->show();
}
