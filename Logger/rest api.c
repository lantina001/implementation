#include <restinio/all.hpp>
int main()
{
	restinio::run(
		restinio::on_this_thread()
		.port(8080)
		.address("localhost")
		.request_handler([](auto req) {
		return req->create_response().set_body("Hello, World!").done();
	}));
	return 0;
}

CURRENT_STRUCT(HTTPAPITestObject) {
	CURRENT_FIELD(number, int32_t);
	CURRENT_FIELD(text, std::string);
	CURRENT_FIELD(array, std::vector<int>);
	CURRENT_DEFAULT_CONSTRUCTOR(HTTPAPITestObject)
		: number(42), text("text"), array({ 1, 2, 3 }) {}
};

TEST(HTTPAPI, RespondsWithObject) {
	const auto scope = HTTP(FLAGS_net_api_test_port).Register(
		"/responds_with_object",
		[](Request r) {
		r(HTTPAPITestObject(),
			HTTPResponseCode.OK,
			Headers({ {"foo", "bar"} }));
	});
	const string url =
		Printf("http://localhost:%d/responds_with_object",
			FLAGS_net_api_test_port);
	const auto response = HTTP(GET(url));
	EXPECT_EQ(200, static_cast<int>(response.code));
	EXPECT_EQ("{\"number\":42,\"text\":\"text\",\"array\":[1,2,3]}\n",
		response.body);
	EXPECT_EQ(url, response.url);
}