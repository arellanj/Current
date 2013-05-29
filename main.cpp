#include "Polycode.h"
#include "PolycodeView.h"
#include "CurrentApp.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("HellPolycode!");
	HelloPolycodeApp *app = new HelloPolycodeApp(view);
	while(app->Update()) {}
	return 0;
}
