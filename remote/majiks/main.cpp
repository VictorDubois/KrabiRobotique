#include <QApplication>
#include <QDebug>

#include "magiks.h"

#include "krabipacket.h"

int main(int a, char** b)
{
    QApplication app(a, b);

    Magiks magiks;
    magiks.show();

    return app.exec();
}
