#include "Application.hpp"

int main() {
	try {
		Application app;

		app.render_models();

	} catch (std::exception &e) {
		std::cerr<<"Application error! "<<e.what()<<std::endl;
		return -1;
	}


	return 0;
}
