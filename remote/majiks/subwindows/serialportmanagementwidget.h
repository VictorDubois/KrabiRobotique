#ifndef SERIALPORTMANAGEMENTWIDGET_H
#define SERIALPORTMANAGEMENTWIDGET_H

#include "serialmanagementwidget.h"

class SerialProxy;
class QPushButton;
class QLabel;
class QComboBox;

class SerialPortManagementWidget : public SerialManagementWidget
{
    public:
        SerialPortManagementWidget(SerialProxy* serialProxy = nullptr, QWidget *parent = nullptr);

    private:
        void on_connectButton_clicked();

        void updateConnectionStatus();
        void updateAvailablePorts();

        QString getSelectedPort() const;

        SerialProxy* m_serialProxy;

        QPushButton*    m_refreshButton;
        QPushButton*    m_connectButton;
        QLabel*         m_statusLabel;
        QComboBox*      m_portsCB;
};

#endif // SERIALPORTMANAGEMENTWIDGET_H
