#include "sur.h"
#include"menupage.h"
#include"player1_menu.h"
#include"player2_menu.h"
#include <QtWidgets/QApplication>
#include"battle.h"
#include"store.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sur w;
    w.show();
    return a.exec();
}
