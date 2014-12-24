#include<QtGui/QApplication>
#include<QtGui/QWidget>
#include<QtGui/QLabel>
#include<QtCore/QTextCodec>
#include<QtGui/QPushButton>
#include<QtGui/QVBoxLayout>
#include<QFont>

int main(int argc,char* argv[])
{
	QApplication app(argc, argv);
	
	QFont font;
    font.setPointSize(16);
    font.setFamily(("wenquanyi"));
    font.setBold(false);
	app.setFont(font);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QWidget* pWidget = new QWidget;
	QLabel label(pWidget);
	
	pWidget->showMaximized();
	label.setWindowFlags(Qt::FramelessWindowHint);
	label.setText(QObject::tr("浙江创维欢迎您！"));
	QPushButton* btn = new QPushButton(QObject::tr("close"), pWidget);
	QPushButton* btn1 = new QPushButton(QObject::tr("open"), pWidget);
	QPushButton* btn2 = new QPushButton(QObject::tr("ioctl"), pWidget);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(&label);
	layout->addWidget(btn);
	layout->addWidget(btn1);
	layout->addWidget(btn2);
	pWidget->setLayout(layout);
	QObject::connect(btn,SIGNAL(clicked()), pWidget, SLOT(close()));
	pWidget->show();
	return app.exec();
}
