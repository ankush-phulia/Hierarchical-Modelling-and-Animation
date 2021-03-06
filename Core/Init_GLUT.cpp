// GlutInit.cpp
#include "Init_GLUT.h"

using namespace Core::Init;

Core::IListener* Init_GLUT::listener = NULL;
Core::WindowInfo Init_GLUT::windowInformation;

void Init_GLUT::Init(const Core::WindowInfo& windowInfo,
                     const Core::FramebufferInfo& framebufferInfo, int argc,
                     char** argv) {
    glutInit(&argc, argv);
    windowInformation = windowInfo;

    glutInitDisplayMode(framebufferInfo.flags);
    glutInitWindowPosition(windowInfo.position_x, windowInfo.position_y);
    glutInitWindowSize(windowInfo.width, windowInfo.height);

    glutCreateWindow(windowInfo.name.c_str());
    std::cout << "GLUT:initialized" << std::endl;

    glutIdleFunc(IdleCallback);
    glutCloseFunc(CloseCallback);
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutKeyboardFunc(&KeyboardCallback);

    Core::Init::Init_GLEW::Init();

    // cleanup
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    PrintOpenGLInfo(windowInfo);
}

void Init_GLUT::Run() {
    std::cout << "GLUT:\t Start Running  " << std::endl;
    glutMainLoop();
}

void Init_GLUT::Close() {
    std::cout << "GLUT:\t Finished" << std::endl;
    glutLeaveMainLoop();
}

void Init_GLUT::IdleCallback(void) { glutPostRedisplay(); }

void Init_GLUT::DisplayCallback() {
    if (listener) {
        listener->NotifyBeginFrame();
        listener->NotifyDisplayFrame();
        glutSwapBuffers();
        listener->NotifyEndFrame();
    }
}

void Init_GLUT::ReshapeCallback(int width, int height) {
    if (windowInformation.isReshapable) {
        if (listener) {
            listener->NotifyReshape(width, height, windowInformation.width,
                                    windowInformation.height);
        }
        windowInformation.width = width;
        windowInformation.height = height;
    }
}

void Init_GLUT::CloseCallback() { Close(); }

void Init_GLUT::EnterFullscreen() { glutFullScreen(); }

void Init_GLUT::ExitFullscreen() { glutLeaveFullScreen(); }

void Init_GLUT::KeyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            listener->insect.x -= 10.0;
            std::cout << listener->insect.x << "," << listener->insect.z
                      << "\n";
            break;
        case 'd':
            listener->insect.x += 10.0;
            std::cout << listener->insect.x << "," << listener->insect.z
                      << "\n";
            break;
        case 'w':
            listener->insect.z -= 10.0;
            std::cout << listener->insect.x << "," << listener->insect.z
                      << "\n";
            break;
        case 's':
            listener->insect.z += 10.0;
            std::cout << listener->insect.x << "," << listener->insect.z
                      << "\n";
            break;
        case 27:
            exit(0);
    }
}

void Init_GLUT::PrintOpenGLInfo(const Core::WindowInfo& windowInfo) {
    const unsigned char* renderer = glGetString(GL_RENDERER);
    const unsigned char* vendor = glGetString(GL_VENDOR);
    const unsigned char* version = glGetString(GL_VERSION);

    std::cout << "*************************************************************"
                 "******************"
              << std::endl;

    std::cout << "GLUT:\tVendor : " << vendor << std::endl;
    std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
    std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
    std::cout << "GLUT:\tInitial window is '" << windowInfo.name
              << "', with dimensions (" << windowInfo.width << "X"
              << windowInfo.height;
    std::cout << ") starts at (" << windowInfo.position_x << "X"
              << windowInfo.position_y;
    std::cout << ") and " << ((windowInfo.isReshapable) ? "is" : "is not ")
              << " redimensionable" << std::endl;
    std::cout << "GLUT:\tInitial Framebuffer contains double buffers for"
              << std::endl;

    std::cout
        << "*****************************************************************"
        << std::endl;
}

void Init_GLUT::SetListener(Core::IListener* const& iListener) {
    listener = iListener;
}
