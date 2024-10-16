#include "loginwidget.h"
#include "registerwidget.h"
#include "widget.h"

#include <QMessageBox>
#include <QtGui>
#include <QtWidgets>

LoginWidget::LoginWidget(QWidget *parent) : QWidget{parent} {
    inputID = new QLineEdit(this);
    inputID->setPlaceholderText(tr("Input ID"));

    inputPW = new QLineEdit(this);
    inputPW->setPlaceholderText(tr("Input Password"));

    submitBtn = new QPushButton("Login", this);

    registerBtn = new QPushButton("Create Account", this);

    // connect(inputID, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(inputPW, SIGNAL(returnPressed()), this, SLOT(submit()));
    connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));
    connect(registerBtn, SIGNAL(clicked()), this, SLOT(registerAct()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(inputID);
    mainLayout->addWidget(inputPW);
    mainLayout->addWidget(submitBtn);
    mainLayout->addWidget(registerBtn);
}

void LoginWidget::submit() {
    if (inputID->text().isEmpty() || inputPW->text().isEmpty()) {
        // 오류 메시지 및 lineinput 삭제
        QMessageBox::warning(this, tr("Login Error"), tr("ID or PW is empty!"));
        return;
    }

    bool isSuccess = false;

    // inputID->text();
    // inputPW->text();
    // 를 서버 통해서 로그인 작업
    // 로그인 성공 시 isSuccess는 true로 변경

    // 임시
    if (inputID->text() == "aaa" && inputPW->text() == "aaa")
        isSuccess = true;

    if (isSuccess) { // 로그인 성공인 경우
        Widget* w = new Widget();
        w->show();

        this->close();
    }
    else { // 로그인 에러인 경우
        // 오류 메시지 및 lineinput 삭제
        inputID->clear();
        inputPW->clear();

        QMessageBox::warning(this, tr("Login Error"), tr("Check ID and PW!"));
        return;
    }
}

void LoginWidget::registerAct() {
    RegisterWidget* rw = new RegisterWidget();
    rw->show();

    this->close();
    //this->deleteLater();
}
