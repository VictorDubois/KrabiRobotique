#ifndef MAGIKS_H
#define MAGIKS_H

#include <QWidget>

class BluetoothProxy;
class PacketProcessor;
class OdometrieWindow;
class WatchWindow;
class AsservWindow;
class GraphWindow;
class BluetoothManagementWidget;
class LoggerWidget;
class PlotWidget;
class TableWidget;

class QTabWidget;

class Magiks: public QWidget
{
    Q_OBJECT

    public:
        explicit Magiks(QWidget *parent = nullptr);

    private:
        void connected();

        BluetoothProxy* m_bluetoothProxy;

        PacketProcessor*            m_packetProcessor;
        OdometrieWindow*            m_odometrie;
        WatchWindow*                m_watches;
        AsservWindow*               m_asserv;
        GraphWindow*                m_graphs;
        BluetoothManagementWidget*  m_bluetoothManagement;
        LoggerWidget*               m_logger;
        PlotWidget*                 m_plots;
        TableWidget*                m_table;

        QTabWidget*  m_tabs;

};

#endif // MAGIKS_H
