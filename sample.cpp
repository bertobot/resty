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


int main() {
	
	Resty rest(8080, 1);

	rest.GET("/helloworld", helloworld);

	rest.GET("/json", json);

	rest.GET("/big", h1);

	

	rest.run();

	return 0;
}

