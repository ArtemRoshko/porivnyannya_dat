#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    selectedStartDate = QDate::currentDate();
    selectedEndDate = QDate::currentDate();

    QWidget *centralWidget = new QWidget;

    QLabel *startDateLabel = new QLabel(tr("First date:"));
    QLabel *endDateLabel = new QLabel(tr("Second date:"));

    QComboBox *startMonthCombo = new QComboBox;
    QComboBox *endMonthCombo = new QComboBox;
    QSpinBox *startDaySpinBox = new QSpinBox;
    QSpinBox *endDaySpinBox = new QSpinBox;
    QSpinBox *startYearSpinBox = new QSpinBox;
    QSpinBox *endYearSpinBox = new QSpinBox;

    for (int month = 1; month <= 12; ++month) {
        startMonthCombo->addItem(QLocale::system().monthName(month));
        endMonthCombo->addItem(QLocale::system().monthName(month));
    }

    startMonthCombo->setCurrentIndex(selectedStartDate.month() - 1);
    endMonthCombo->setCurrentIndex(selectedEndDate.month() - 1);

    startDaySpinBox->setRange(1, selectedStartDate.daysInMonth());
    endDaySpinBox->setRange(1, selectedEndDate.daysInMonth());

    startDaySpinBox->setValue(selectedStartDate.day());
    endDaySpinBox->setValue(selectedEndDate.day());

    startYearSpinBox->setRange(1, 8000);
    endYearSpinBox->setRange(1, 8000);

    startYearSpinBox->setValue(selectedStartDate.year());
    endYearSpinBox->setValue(selectedEndDate.year());

    editor = new QTextBrowser;
    insertCalendar();

    connect(startMonthCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::setStartMonth);
    connect(endMonthCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::setEndMonth);
    connect(startDaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setStartDay);
    connect(endDaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setEndDay);
    connect(startYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setStartYear);
    connect(endYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setEndYear);

    QHBoxLayout *startDateLayout = new QHBoxLayout;
    startDateLayout->addWidget(startDateLabel);
    startDateLayout->addWidget(startMonthCombo);
    startDateLayout->addWidget(startDaySpinBox);
    startDateLayout->addWidget(startYearSpinBox);

    QHBoxLayout *endDateLayout = new QHBoxLayout;
    endDateLayout->addWidget(endDateLabel);
    endDateLayout->addWidget(endMonthCombo);
    endDateLayout->addWidget(endDaySpinBox);
    endDateLayout->addWidget(endYearSpinBox);

    QVBoxLayout *controlsLayout = new QVBoxLayout;
    controlsLayout->addLayout(startDateLayout);
    controlsLayout->addLayout(endDateLayout);
    controlsLayout->addStretch(1);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(editor, 1);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);

    calculateDays();

    connect(startMonthCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::calculateDays);
    connect(endMonthCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::calculateDays);
    connect(startDaySpinBox,QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculateDays);
    connect(startYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculateDays);
    connect(endYearSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::calculateDays);
}

void MainWindow::insertCalendar()
{
    editor->clear();
    QTextDocument *document = editor->document();

    QTextCursor cursor(document);
    cursor.beginEditBlock();

    QDate startDate(selectedStartDate.year(), selectedStartDate.month(), selectedStartDate.day());
    QDate endDate(selectedEndDate.year(), selectedEndDate.month(), selectedEndDate.day());

    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);

    QTextCharFormat regularFormat;
    regularFormat.setFontWeight(QFont::Normal);

    int days = startDate.daysTo(endDate);
    cursor.insertText(QString("%1 days have passed").arg(qAbs(days)), regularFormat);

    cursor.endEditBlock();
}

void MainWindow::setFontSize(int size)
{
    fontSize = size;
    insertCalendar();
}

void MainWindow::setStartMonth(int month)
{
    selectedStartDate = QDate(selectedStartDate.year(), month + 1, selectedStartDate.day());
    insertCalendar();
}

void MainWindow::setEndMonth(int month)
{
    selectedEndDate = QDate(selectedEndDate.year(), month + 1, selectedEndDate.day());
    insertCalendar();
}

void MainWindow::setStartDay(int day)
{
    selectedStartDate = QDate(selectedStartDate.year(), selectedStartDate.month(), day);
    insertCalendar();
}

void MainWindow::setEndDay(int day)
{
    selectedEndDate = QDate(selectedEndDate.year(), selectedEndDate.month(), day);
    insertCalendar();
}

void MainWindow::setStartYear(int year)
{
    selectedStartDate = QDate(year, selectedStartDate.month(), selectedStartDate.day());
    insertCalendar();
}

void MainWindow::setEndYear(int year)
{
    selectedEndDate = QDate(year, selectedEndDate.month(), selectedEndDate.day());
    insertCalendar();
}

void MainWindow::calculateDays()
{
    insertCalendar();
}
