#include "watchwindow.h"
#include "ui_watchwindow.h"

#include "debugwindow.h"

WatchWindow::WatchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchWindow)
{
    ui->setupUi(this);

    excluded.append(KrabiPacket::W_WATCHES);
    excluded.append(KrabiPacket::W_PID_LIN);
    excluded.append(KrabiPacket::W_PID_ANG);

    for(int i(1); i < KrabiPacket::MAX_WATCHES; ++i)
    {
        KrabiPacket::W_TABLE w = (KrabiPacket::W_TABLE) i;
        if (!excluded.contains(w))
        {
            watches[w] = new QCheckBox(getWatchName(w));
            ui->watchList->addWidget(watches[w]);
            connect(watches[w], SIGNAL(clicked(bool)), this, SLOT(checkBoxChanged()));
        }
    }

    connect(ui->refreshButton, SIGNAL(clicked(bool)), this, SLOT(requireSync()));
    connect(ui->noneButton, SIGNAL(clicked(bool)), this, SLOT(deselectAll()));
}

WatchWindow::~WatchWindow()
{
    delete ui;
}

QString WatchWindow::getWatchName(KrabiPacket::W_TABLE w)
{
    switch(w)
    {
    case KrabiPacket::W_NULL:
        return "NULL";
    case KrabiPacket::W_ODOMETRIE:
        return "Odométrie";
    case KrabiPacket::W_PID_ANG:
        return "PID Angular";
    case KrabiPacket::W_PID_LIN:
        return "PID Linear";
    case KrabiPacket::W_POSITION:
        return "Position";
    case KrabiPacket::W_SPEED:
        return "Speed";
    case KrabiPacket::W_SPEED_TARGET:
        return "Speed Target";
    case KrabiPacket::W_SHARPS:
        return "Sharps";
    default:
        return "Unknown";
    }
}

void WatchWindow::checkBoxChanged()
{
    for(QMap<KrabiPacket::W_TABLE, QCheckBox*>::iterator it = watches.begin(); it != watches.end(); ++it)
        if (it.value() == sender())
            setWatching(it.key(), it.value()->isChecked(), true, true);
}

bool WatchWindow::isWatching(KrabiPacket::W_TABLE w)
{
    if (!watches.contains(w))
        return false;
    return watches[w];
}

void WatchWindow::setWatching(KrabiPacket::W_TABLE w, bool watching)
{
    setWatching(w, watching, true);
}

void WatchWindow::setWatching(KrabiPacket::W_TABLE w, bool watching, bool transmit, bool force)
{
    if (!watches.contains(w))
        return;

    if (!force && watches[w]->isChecked() == watching)
        return;

    watches[w]->setChecked(watching);

    if (transmit)
    {
        KrabiPacket p(watching ? KrabiPacket::WATCH_SET : KrabiPacket::WATCH_RESET, w);
        DebugWindow::getInstance()->getBluetoothWindow()->send(p);
    }

    DebugWindow::getInstance()->getSharpWindow()->setWatchChecked(watches[KrabiPacket::W_SHARPS]->isChecked());
}

void WatchWindow::deselectAll()
{
    for(QMap<KrabiPacket::W_TABLE, QCheckBox*>::iterator it = watches.begin(); it != watches.end(); ++it)
        setWatching(it.key(), false, false);

    KrabiPacket p(KrabiPacket::WATCH_DESELECT_ALL);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void WatchWindow::requireSync()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_WATCHES);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void WatchWindow::syncFinished(KrabiPacket p)
{
    while(p.isReadable<uint16_t>())
    {
        KrabiPacket::W_TABLE w = (KrabiPacket::W_TABLE) p.get<uint8_t>();
        bool checked = p.get<bool>();

        if (watches.contains(w))
            setWatching(w, checked, false);
    }
}
