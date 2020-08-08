#include <iostream>
#include <sstream>

#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

int main(int argc, char *argv[]) {

    std::string url = "https://www.kusss.jku.at";

    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(url));

        std::cout << request << std::endl;

        std::cout << curlpp::options::Url(url) << std::endl;

        return EXIT_SUCCESS;
    }
    catch (curlpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_FAILURE;
}