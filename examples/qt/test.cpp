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
    font.setPointSize(12);
    font.setFamily(("wenquanyi"));
    font.setBold(false);
	app.setFont(font);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	
	QWidget* pWidget = new QWidget;
	pWidget->showMaximized();
	pWidget->setWindowFlags(Qt::FramelessWindowHint);

	QLabel* label = new QLabel(QObject::tr("浙江创维 按键键值："), pWidget);
	QLabel* label_key = new QLabel(QObject::tr("0"), pWidget);
	QPushButton* btn1 = new QPushButton(QObject::tr("close"), pWidget);
	QPushButton* btn2 = new QPushButton(QObject::tr("open"), pWidget);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(&label);
	layout->addWidget(&label_key);
	layout->addWidget(btn1);
	layout->addWidget(btn2);
	pWidget->setLayout(layout);
	QObject::connect(btn,SIGNAL(clicked()), pWidget, SLOT(close()));
	pWidget->show();

	label_key.setText(QObject::tr("0"));
	return app.exec();
}
