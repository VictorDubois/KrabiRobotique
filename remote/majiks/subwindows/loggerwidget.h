#ifndef LOGGERWIDGET_H
#define LOGGERWIDGET_H

#include <QWidget>
#include <QString>

class QTextEdit;

/**
 * @brief A simple widget to display logs.
 */
class LoggerWidget : public QWidget
{
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param parent The parent widget
         */
        explicit LoggerWidget(QWidget *parent = nullptr);

        /**
         * @brief Add a line to the log
         * @param text The text to add
         * @param isDebug If set, this line will be displayed as 'debug'
         */
        void log(const QString& text, bool isDebug = false);

        /**
         * @return The entierety of the logs
         */
        QString getLogs() const;

    private:

        QTextEdit* m_log;
};

#endif // LOGGERWIDGET_H
