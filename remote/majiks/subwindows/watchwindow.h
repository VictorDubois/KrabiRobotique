#ifndef WATCHWINDOW_H
#define WATCHWINDOW_H

#include <QWidget>
#include <QMap>
#include <QCheckBox>

#include "krabipacket.h"

namespace Ui {class WatchWindow;}

class BluetoothProxy;

class WatchWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit WatchWindow(BluetoothProxy *bluetoothProxy, QWidget *parent = 0);
        ~WatchWindow();

        bool isWatching(KrabiPacket::W_TABLE w);
        void setWatching(KrabiPacket::W_TABLE w, bool watching);

        void syncFinished(KrabiPacket p);

        static QString getWatchName(KrabiPacket::W_TABLE w);

    private slots:
        void checkBoxChanged();
        void deselectAll();
        void requireSync();

    private:
        QList<KrabiPacket::W_TABLE> excluded;
        QMap<KrabiPacket::W_TABLE, QCheckBox*> watches;
        Ui::WatchWindow *ui;

        BluetoothProxy* m_bluetoothProxy;

        void setWatching(KrabiPacket::W_TABLE w, bool watching, bool transmit, bool force = false);

        void showEvent(QShowEvent* event );
};

#endif // WATCHWINDOW_H
