#include "Resty.h"

void helloworld(const Request &request, Response &response) {
	response.write("hello world!", "text/plain");
}

void json(const Request &request, Response &response) {
	response.write("{ \"key\" : \"value\" }", "application/json");
}

void h1(const Request &request, Response &response) {
	response.write("<h1>Hello!</h1>");
}

void hw2(const Request &request, Response &response) {
	std::string msg = "hello, ";

	response.write(msg + request.getParameter("world") );
}

void bye(const Request &request, Response &response) {
	std::stringstream ss;

	ss << "bye, " << request.getParameter("first") << ", " << request.getParameter("second");

	response.write(ss.str() );
}


int main() {
	
	Resty rest(8080, 1);

	rest.GET("/helloworld", helloworld);

	rest.GET("/json", json);

	rest.GET("/big", h1);

	rest.GET("/hello/:world", hw2);

	rest.GET("/bye/:first/:second", bye);

	

	rest.run();

	return 0;
}

