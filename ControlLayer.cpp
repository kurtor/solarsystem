/**
*公司：杭州图华科技有限公司
*版权信息：图华所有
*任务：太阳系模拟构建实习作业
*描述：控制层实现
*
*版本：1.1
*作者：叶广平
*日期：2019/4/25
**/

#include "ControlLayer.h"
#include<qdebug.h>


ControlLayer::ControlLayer()
{
	//initial the mainwindow <- mainwidget <-  openglwidget
	mainwindow = new MainWindow();
	mainwidget = new MainWidget(mainwindow);
	openglwin = new OpenglWidget(mainwidget);

	//set their size
	mainwindow->setMinimumWidth(1530);
	mainwindow->setMinimumHeight(900);
	mainwidget->setMinimumSize(1430, 900);
	openglwin->setMinimumSize(1300, 900);

	//set their layout
	mainwindow->set_window_layout(mainwidget);	
	mainwidget->set_widget_layout(openglwin);
	mainwindow->set_window_dock();

	//set the signal and slot
	set_connect();

	now_time = new QDateTimeEdit(QDateTime::currentDateTime());
	initial_time();
}


ControlLayer::~ControlLayer()
{
}

MainWindow* ControlLayer::get_mainwindow()
{
	return mainwindow;
}

void ControlLayer::set_connect()
{
	QObject::connect(mainwindow->button1, &QPushButton::clicked, openglwin, &OpenglWidget::sun);
	QObject::connect(mainwindow->button2, &QPushButton::clicked, openglwin, &OpenglWidget::mercury);
	QObject::connect(mainwindow->button3, &QPushButton::clicked, openglwin, &OpenglWidget::venus);
	QObject::connect(mainwindow->button4, &QPushButton::clicked, openglwin, &OpenglWidget::earth);
	QObject::connect(mainwindow->button5, &QPushButton::clicked, openglwin, &OpenglWidget::mars);
	QObject::connect(mainwindow->button6, &QPushButton::clicked, openglwin, &OpenglWidget::jupiter);
	QObject::connect(mainwindow->button7, &QPushButton::clicked, openglwin, &OpenglWidget::saturn);
	QObject::connect(mainwindow->button8, &QPushButton::clicked, openglwin, &OpenglWidget::uranus);
	QObject::connect(mainwindow->button9, &QPushButton::clicked, openglwin, &OpenglWidget::neptune);

	QObject::connect(mainwidget->button_pause, &QPushButton::clicked, openglwin, &OpenglWidget::set_pause);
	QObject::connect(mainwidget->button_start, &QPushButton::clicked, openglwin, &OpenglWidget::set_start);
	QObject::connect(mainwidget->button_lighton, &QPushButton::clicked, openglwin, &OpenglWidget::set_light_switch_on);
	QObject::connect(mainwidget->button_lightoff, &QPushButton::clicked, openglwin, &OpenglWidget::set_light_switch_off);
	QObject::connect(mainwidget->button_starmode1, &QPushButton::clicked, openglwin, &OpenglWidget::set_star_mode1);
	QObject::connect(mainwidget->button_starmode2, &QPushButton::clicked, openglwin, &OpenglWidget::set_star_mode2);

	QObject::connect(mainwidget->date_time, &QDateTimeEdit::dateChanged, this, &ControlLayer::set_times);
	QObject::connect(mainwidget->slider, &QSlider::valueChanged, this, &ControlLayer::set_speed);

	QObject::connect(openglwin, &OpenglWidget::fpschanged, mainwidget, &MainWidget::on_fps_changed);
}

void ControlLayer::set_speed()
{
	openglwin->speedset(mainwidget->slider->value());
}

void ControlLayer::initial_time()
{
	GLint standard_time = getDays(1982, 3, 10);
	QString date = now_time->date().toString("yyyy/MM/dd");
	GLint year = date.mid(0, 4).toInt();
	GLint month = date.mid(5, 2).toInt();
	GLint day = date.mid(8, 2).toInt();
	GLint now_time = getDays(year, month, day);
	GLint delta = (now_time - standard_time) * 24;
	openglwin->timeset(delta);
}

void ControlLayer::set_times()
{
	GLint standard_time = getDays(1982, 3, 10);
	QString date = mainwidget->date_time->date().toString("yyyy/MM/dd");
	GLint year = date.mid(0, 4).toInt();
	GLint month = date.mid(5, 2).toInt();
	GLint day = date.mid(8, 2).toInt();
	GLint select_time = getDays(year, month, day);
	GLint delta = (select_time - standard_time) * 24;
	openglwin->timeset(delta);
}

GLboolean ControlLayer::isLeapYear(GLint year)
{
	return((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}


GLint ControlLayer::getDays(GLint year, GLint month, GLint day)
{
	int m[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (isLeapYear(year))
		m[2]++;
	int result = 0;
	for (int i = 1; i < year; i++)
	{
		result += 365;
		if (isLeapYear(i))
			result++;
	}
	for (int i = 1; i < month; i++)
	{
		result += m[i];
	}
	result += day;

	return result;
}