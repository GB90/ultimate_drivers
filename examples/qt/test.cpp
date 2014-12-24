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
	// app.setFont(QFont("simsun"));
	
	
	QFont font;
    font.setPointSize(12);
    font.setFamily(("wenquanyi"));
    font.setBold(false);
	app.setFont(font);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
	QWidget* pWidget = new QWidget;
	QLabel label(pWidget);
	// pWidget.showMaximized();
	
	pWidget->showMaximized();
	label.setText(QObject::tr("浙江创维欢迎您!"));
	QPushButton* btn = new QPushButton(QObject::tr("close!"), pWidget);
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(&label);
	layout->addWidget(btn);
	pWidget->setLayout(layout);
	pWidget->show();
	return app.exec();
}
