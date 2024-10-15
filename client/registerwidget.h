#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);

private:
    QLineEdit* inputID;
    QLineEdit* inputPW;
    QLineEdit* inputName;
    QLineEdit* inputPhonenum;

    QPushButton* submitBtn;
    QPushButton* backBtn;

private slots:
    void submit();
    void backToLogin();

signals:
};

#endif // REGISTERWIDGET_H