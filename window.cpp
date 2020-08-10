#include "window.h"
#include <QtWidgets>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>


using namespace std;

Gui::Gui() {
    fontSize = 10;

    QWidget *centralWidget = new QWidget;

    QLabel *fontSizeLabel = new QLabel(tr("Font size:"));
    QSpinBox *fontSizeSpinBox = new QSpinBox;
    fontSizeSpinBox->setRange(1, 64);

    editor = new QTextBrowser;
    insertCalendar();

    connect(fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &Gui::setFontSize);

    fontSizeSpinBox->setValue(10);

    QHBoxLayout *controlsLayout = new QHBoxLayout;
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


void Gui::insertCalendar() {
    editor->clear();
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();


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


    QTextTable *table = cursor.insertTable(1, 6, tableFormat);


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
    highlightedFormat.setForeground(Qt::black);


    for (int weekDay = 2; weekDay <= 6; ++weekDay) {
        QTextTableCell cell = table->cellAt(0, weekDay - 1);

        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(QLocale::system().dayName(weekDay - 1), boldFormat);
    }

    int rows = 12;
    int rowIndex = 1;
    std::vector<QString> hours{"8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
    while (rows >= 0) {
        table->insertRows(table->rows(), 1);

        QTextTableCell cell = table->cellAt(rowIndex, 0);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(hours[rowIndex - 1], boldFormat);
        rows--;
        rowIndex++;
    }

    std::unordered_map<string, int> hourToRow = {
            {"08:00", 1},
            {"08:15", 1},
            {"08:30", 1},
            {"08:45", 1},
            {"09:00", 2},
            {"09:15", 2},
            {"09:30", 2},
            {"09:45", 2},
            {"10:00", 3},
            {"10:15", 3},
            {"10:30", 3},
            {"10:45", 3},
            {"11:15", 4},
            {"11:30", 4},
            {"11:45", 4},
            {"11:00", 4},
            {"12:00", 5},
            {"12:15", 5},
            {"12:30", 5},
            {"12:45", 5},
            {"13:00", 6},
            {"13:15", 6},
            {"13:30", 6},
            {"13:45", 6},
            {"14:00", 7},
            {"14:15", 7},
            {"14:30", 7},
            {"14:45", 7},
            {"15:00", 8},
            {"15:15", 8},
            {"15:30", 8},
            {"15:45", 8},
            {"16:00", 9},
            {"16:15", 9},
            {"16:30", 9},
            {"16:45", 9},
            {"17:00", 10},
            {"17:15", 10},
            {"17:30", 10},
            {"17:45", 10},
            {"18:00", 11},
            {"18:15", 11},
            {"18:30", 11},
            {"18:45", 11},
            {"19:00", 12},
            {"19:15", 12},
            {"19:30", 12},
            {"19:45", 12},
            {"20:00", 12},
            {"20:15", 12},
            {"20:30", 12},
            {"20:45", 12}
    };

    string line;
    string filepath = "/Users/ioneliabuzatu/CLionProjects/kisssBusySchedule/scraped_data.txt";
    ifstream myfile;
    int col;
    std::ifstream infile(filepath);

    while (std::getline(infile, line)) {
        int ROW;
        vector<string> row_values;
        vector<string> dayDatetime;
        vector<string> startHourDatetime;


        split(line, ',', row_values);
        split(row_values[2], '.', dayDatetime);
        string day = dayDatetime[0];
        split(row_values[2], ' ', startHourDatetime);
        day.erase(remove(day.begin(), day.end(), ' '), day.end());
        for (auto v:startHourDatetime)
            cout << v << " ";
        cout << startHourDatetime[3] << endl;
        string startHour = startHourDatetime[3];
        if (day == "Mon") {
            col = 1;
        } else if (day == "Tue") {
            col = 2;
        } else if (day == "Wed") {
            col = 3;
        } else if (day == "Thu") {
            col = 4;
        } else if (day == "Fri") {
            col = 5;
        }

        ROW = hourToRow[startHour];

        QTextTableCell cell = table->cellAt(ROW, col);

        QTextCursor cellCursor = cell.firstCursorPosition();
        QString dataToInsert = QString::fromStdString(row_values[0]);
        cellCursor.insertText(dataToInsert, highlightedFormat);
        cellCursor.insertText("\n", boldFormat);
        col++;
    }

    cursor.endEditBlock();

    setWindowTitle(tr("My weekly preregistration courses"));

}

void Gui::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

void Gui::setFontSize(int size) {
    fontSize = size;
    insertCalendar();
}

