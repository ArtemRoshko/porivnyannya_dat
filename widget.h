#ifndef WIDGET_H
#define WIDGET_H




#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        // Створення текстових полів
        QLineEdit *lineEdit1 = new QLineEdit(this);
        QLineEdit *lineEdit2 = new QLineEdit(this);

        // Створення кнопки
        QPushButton *button = new QPushButton("Show Difference", this);

        // Створення мітки для відображення різниці
        QLabel *label = new QLabel(this);
        label->setAlignment(Qt::AlignCenter);

        // Розміщення елементів у вертикальному лейауті
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(lineEdit1);
        layout->addWidget(lineEdit2);
        layout->addWidget(button);
        layout->addWidget(label);
        setLayout(layout);

        // Підключення слоту до події натискання на кнопку
        connect(button, &QPushButton::clicked, this, [lineEdit1, lineEdit2, label]() {
            // Отримання значень з текстових полів
            QString text1 = lineEdit1->text();
            QString text2 = lineEdit2->text();

            // Обчислення різниці значень
            int difference = text1.toInt() - text2.toInt();

            // Відображення різниці на мітці
            label->setText(QString("Difference: %1").arg(difference));
        });
    }
};







#endif // WIDGET_H
