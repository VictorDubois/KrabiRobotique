#ifndef REMOTEDEBUG_H
#define REMOTEDEBUG_H

#include <QWidget>

namespace Ui {
class RemoteDebug;
}

class RemoteDebug : public QWidget
{
    Q_OBJECT
    
public:
    explicit RemoteDebug(QWidget *parent = 0);
    ~RemoteDebug();
    
private:
    Ui::RemoteDebug *ui;
};

#endif // REMOTEDEBUG_H
