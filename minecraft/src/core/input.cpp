#include "core/input.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "core/application.h"
#include "core/log.h"

namespace Minecraft
{

    bool Input::is_key_down(int keycode)
    {
        GLFWwindow* window = Application::get()->get_window()->get_window_handle();
        
        if (glfwGetKey(window, keycode) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    bool Input::is_mouse_button_down(int button)
    {
        GLFWwindow* window = Application::get()->get_window()->get_window_handle();
        
        if (glfwGetMouseButton(window, button) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    float Input::get_mouse_x()
    {
        GLFWwindow* window = Application::get()->get_window()->get_window_handle();

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return (float)xpos;
    }
    float Input::get_mouse_y()
    {
        GLFWwindow* window = Application::get()->get_window()->get_window_handle();

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return (float)ypos;
    }

    const glm::vec2 Input::get_mouse_pos()
    {
        GLFWwindow* window = Application::get()->get_window()->get_window_handle();

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return glm::vec2(xpos, ypos);
    }

    void Input::toggle_cursor()
    {
        int value = glfwGetInputMode(Application::get()->get_window()->get_window_handle(), GLFW_CURSOR);

        switch (value)
        {
        case GLFW_CURSOR_NORMAL:
            glfwSetInputMode(Application::get()->get_window()->get_window_handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        case GLFW_CURSOR_DISABLED:
            glfwSetInputMode(Application::get()->get_window()->get_window_handle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        }
    }
}