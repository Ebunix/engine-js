#include "corejs.h"

int main(int argc, char* argv[]) {
    corejs::init(argv[0]);
    corejs::run("console.log('Hello, World'); console.count();");
    corejs::destroy();

    return 0;
}