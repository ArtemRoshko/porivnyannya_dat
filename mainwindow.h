#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextBrowser;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void setFontSize(int size);
    void setStartMonth(int month);
    void setEndMonth(int month);
    void setStartDay(int day);
    void setEndDay(int day);
    void setStartYear(int year);
    void setEndYear(int year);
    void calculateDays();

private:
    void insertCalendar();

    int fontSize;
    QDate selectedStartDate;
    QDate selectedEndDate;
    QTextBrowser *editor;
};

#endif // MAINWINDOW_H
