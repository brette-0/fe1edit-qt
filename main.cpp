#include "editor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QApplication::setApplicationName("fe1edit");
    QApplication::setOrganizationName("brette-0");
    QApplication::setApplicationVersion("0.1");

    Editor editor;
    editor.show();
    return QApplication::exec();
}
