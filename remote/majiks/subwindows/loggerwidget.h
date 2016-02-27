#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QWidget>
#include <QString>

class QTextEdit;

class LoggerWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit LoggerWidget(QWidget *parent = nullptr);

        void log(const QString& text, bool isDebug = false);

        QString getLogs() const;

    private:

        QTextEdit* m_log;
};

#endif // LOGGERWIDGET_H
