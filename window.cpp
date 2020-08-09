#include "window.h"

#include <QtWidgets>


MainWindow::MainWindow() {
    selectedDate = QDate::currentDate();
    fontSize = 10;

    QWidget *centralWidget = new QWidget;


    QLabel *dateLabel = new QLabel(tr("Date:"));
    QComboBox *monthCombo = new QComboBox;

    for (int month = 1; month <= 12; ++month)
        monthCombo->addItem(QLocale::system().monthName(month));

    QDateTimeEdit *yearEdit = new QDateTimeEdit;
    yearEdit->setDisplayFormat("yyyy");
    yearEdit->setDateRange(QDate(1753, 1, 1), QDate(8000, 1, 1));


    monthCombo->setCurrentIndex(selectedDate.month() - 1);
    yearEdit->setDate(selectedDate);


    QLabel *fontSizeLabel = new QLabel(tr("Font size:"));
    QSpinBox *fontSizeSpinBox = new QSpinBox;
    fontSizeSpinBox->setRange(1, 64);

    editor = new QTextBrowser;
    insertCalendar();


    connect(monthCombo, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::setMonth);
    connect(yearEdit, &QDateTimeEdit::dateChanged,
            this, &MainWindow::setYear);
    connect(fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::setFontSize);


    fontSizeSpinBox->setValue(10);


    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(dateLabel);
    controlsLayout->addWidget(monthCombo);
    controlsLayout->addWidget(yearEdit);
    controlsLayout->addSpacing(24);
    controlsLayout->addWidget(fontSizeLabel);
    controlsLayout->addWidget(fontSizeSpinBox);
    controlsLayout->addStretch(1);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(controlsLayout);
    centralLayout->addWidget(editor, 1);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);

}


void MainWindow::insertCalendar() {
    editor->clear();
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();

    QDate date(selectedDate.year(), selectedDate.month(), 1);


    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setBackground(QColor("#e0e0e0"));
    tableFormat.setCellPadding(2);
    tableFormat.setCellSpacing(4);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14)
                << QTextLength(QTextLength::PercentageLength, 14);
    tableFormat.setColumnWidthConstraints(constraints);


    QTextTable *table = cursor.insertTable(1, 7, tableFormat);


    QTextFrame *frame = cursor.currentFrame();
    QTextFrameFormat frameFormat = frame->frameFormat();
    frameFormat.setBorder(1);
    frame->setFrameFormat(frameFormat);


    QTextCharFormat format = cursor.charFormat();
    format.setFontPointSize(fontSize);

    QTextCharFormat boldFormat = format;
    boldFormat.setFontWeight(QFont::Bold);

    QTextCharFormat highlightedFormat = boldFormat;
    highlightedFormat.setBackground(Qt::yellow);


    for (int weekDay = 1; weekDay <= 7; ++weekDay) {
        QTextTableCell cell = table->cellAt(0, weekDay - 1);

        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(QLocale::system().dayName(weekDay), boldFormat);
    }


    table->insertRows(table->rows(), 1);


    while (date.month() == selectedDate.month()) {
        int weekDay = date.dayOfWeek();
        QTextTableCell cell = table->cellAt(table->rows() - 1, weekDay - 1);
        QTextCursor cellCursor = cell.firstCursorPosition();

        if (date == QDate::currentDate())
            cellCursor.insertText(QString("%1").arg(date.day()), highlightedFormat);
        else
            cellCursor.insertText(QString("%1").arg(date.day()), format);

        date = date.addDays(1);
        if (weekDay == 7 && date.month() == selectedDate.month())
            table->insertRows(table->rows(), 1);
    }

    cursor.endEditBlock();

    setWindowTitle(tr("Calendar for %1 %2"
    ).arg(QLocale::system().monthName(selectedDate.month())
    ).arg(selectedDate.year()));
}


void MainWindow::setFontSize(int size) {
    fontSize = size;
    insertCalendar();
}


void MainWindow::setMonth(int month) {
    selectedDate = QDate(selectedDate.year(), month + 1, selectedDate.day());
    insertCalendar();
}


void MainWindow::setYear(QDate date) {
    selectedDate = QDate(date.year(), selectedDate.month(), selectedDate.day());
    insertCalendar();
}