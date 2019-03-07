
#include <QtWidgets/QApplication>
#include <GUIMainWindow.h>
#include <Tests.h>

int main(int argc, char *argv[])
{
	//runTests();
	Service serv = Service("activities.txt");
	QApplication a(argc, argv);
	MainWindowGUI mainWindow(serv);
	mainWindow.show();
	return a.exec();
}