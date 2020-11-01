//
// Created by AICDG on 2020/11/1.
//

#include <pybind11/embed.h>
#include <iostream>

int main()
{
    using namespace pybind11::literals;

    pybind11::scoped_interpreter guard{};

    // ###
    pybind11::print("Hello world");

    // ###
    pybind11::exec(R"(
        kwargs = dict(name="World", number=42)
        message = "Hello, {name}! The answer is {number}".format(**kwargs)
        print(message)
    )");

    // ###
    auto kwargs = pybind11::dict("name"_a="World", "number"_a=42);
    auto message = "Hello, {name}! The answer is {number}"_s.format(**kwargs);
    pybind11::print(message);

    // ###
    auto locals = pybind11::dict("name"_a="World", "number"_a=42);
    pybind11::exec(R"(
        message = "Hello, {name}! The answer is {number}".format(**locals())
    )", pybind11::globals(), locals);

    auto message2 = locals["message"].cast<std::string>();
    std::cout << message2 << std::endl;

    // ###
    pybind11::module sys = pybind11::module::import("sys");
    pybind11::print(sys.attr("path"));
}
