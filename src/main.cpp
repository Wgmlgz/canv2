
// #include <emscripten.h>
// #include <emscripten/bind.h>
// #include <emscripten/html5.h>

// #include <memory>
// #include <string>

#include <iostream>
/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */
// #include "./helloworld.cpp"

int sus(
	// int argc, char **argv
	)
{
	// ExampleHelloWorld hi("a", "b", "c");
	
	return 2;
}

// int main(int _argc, const char* const* _argv)
// {
// 	using namespace entry;
// 	return s_ctx.run(_argc, _argv);
// }


int da() {
  return 2;
}

// int main() {
// 	std::cout << "sus" << std::endl;
// }
// using namespace emscripten;
// EMSCRIPTEN_BINDINGS(my_module) {
//   // class_<CanvasApp>("CanvasApp")
//   //     .constructor<std::string>()
//   //     .function("EventLoopCallback", &CanvasApp::EventLoopCallback);
//   function("da", &da);
//   function("sus", &sus);
//   // function("EventLoopCallback", &EventLoopCallback);
// }