#include "Polycode.h"
#include "PolycodeView.h"
#include "CurrentApp.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("~Current~");
	CurrentApp *app = new CurrentApp(view);
	while(app->Update()) {}
	return 0;
}
