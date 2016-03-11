#include "loggerwidget.h"

#include <QTextEdit>
#include <QTime>
#include <QVBoxLayout>
#include <QDebug>

LoggerWidget::LoggerWidget(QWidget *parent): QWidget(parent)
{
    m_log = new QTextEdit(this);
    m_log->setReadOnly(true);
    m_log->setAcceptRichText(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_log);

    log("System start", true);
}

void LoggerWidget::log(const QString& text, bool debug)
{
    QString time = QTime::currentTime().toString("HH:mm:ss:zzz");
    m_log->append(QString("<b>%1:</b>%3 %2%4<br/>").arg(time, text, debug?"<i>":"", debug?"</i>":""));

    qDebug() << QString("%1 %2: %3").arg(time, debug?"[D]":"", text);
}

QString LoggerWidget::getLogs() const
{
    return m_log->toHtml();
}

