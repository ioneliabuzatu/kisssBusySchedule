#ifndef WINDOW_H
#define WINDOW_H

#include <QDate>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QTextBrowser;

QT_END_NAMESPACE


class Gui : public QMainWindow {
Q_OBJECT

public:
    Gui();

public slots:

    void split(const std::string &s, char delim, std::vector<std::string> &elems);

    void setFontSize(int size);

private:
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;
};


#endif