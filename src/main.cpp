#include "application.hpp"

int main() {
	try {
		Application app;

	} catch (std::exception &e) {
		std::cerr<<"Application error! "<<e.what()<<std::endl;
		return -1;
	}

	//app.render_models();

	return 0;
}
