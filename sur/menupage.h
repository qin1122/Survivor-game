#pragma once

#include <QWidget>
#include "ui_menupage.h"
#include"player1_menu.h"
#include"player2_menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class menupageClass; };
QT_END_NAMESPACE

class menupage : public QWidget
{
	Q_OBJECT

public:
	menupage(QWidget *parent = nullptr);
	~menupage();

private:
	Ui::menupageClass *ui;
	player1_menu flag1;
	player2_menu flag2;

signals:
	void mysignal();

private slots:
	void changeslots();
	void toplayer1_menu();
	void toplayer2_menu();
	void tomenupage1();
	void tomenupage2();
};
