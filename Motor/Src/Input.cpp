#include "Input.h"
#include "glew.h"
#include "GLFW/glfw3.h"



Input::Input(GLFWwindow *_contextWindows) {contextWindows = _contextWindows;}


Input::~Input(){}

bool Input::GetKeyDown(KeyBoard _keyBoard)
{
	return CheckKeyPress(_keyBoard, GLFW_REPEAT);
}

bool Input::GetKey(KeyBoard _keyBoard)
{
	return CheckKeyPress(_keyBoard, GLFW_PRESS);
}

bool Input::GetKeyUp(KeyBoard _keyBoard)
{
	return CheckKeyPress(_keyBoard, GLFW_RELEASE);
}
void Input::SetContextWindows(GLFWwindow *_contextWindows)
{
	contextWindows = _contextWindows;
}
bool Input::CheckKeyPress(KeyBoard _keyBoard, unsigned int type)
{
	return (glfwGetKey(contextWindows, _keyBoard) == type);
}


























/*switch (_keyBoard)
	{
	case KeyBoard::A:
		return (glfwGetKey(contextWindow, GLFW_KEY_A) == type);
		break;
	case KeyBoard::B:
		return (glfwGetKey(contextWindow, GLFW_KEY_B) == type);
		break;
	case KeyBoard::C:
		return (glfwGetKey(contextWindow, GLFW_KEY_C) == type);
		break;
	case KeyBoard::D:
		return (glfwGetKey(contextWindow, GLFW_KEY_D) == type);
		break;
	case KeyBoard::E:
		return (glfwGetKey(contextWindow, GLFW_KEY_E) == type);
		break;
	case KeyBoard::F:
		return (glfwGetKey(contextWindow, GLFW_KEY_F) == type);
		break;
	case KeyBoard::G:
		return (glfwGetKey(contextWindow, GLFW_KEY_G) == type);
		break;
	case KeyBoard::H:
		return (glfwGetKey(contextWindow, GLFW_KEY_H) == type);
		break;
	case KeyBoard::I:
		return (glfwGetKey(contextWindow, GLFW_KEY_I) == type);
		break;
	case KeyBoard::J:
		return (glfwGetKey(contextWindow, GLFW_KEY_J) == type);
		break;
	case KeyBoard::K:
		return (glfwGetKey(contextWindow, GLFW_KEY_K) == type);
		break;
	case KeyBoard::L:
		return (glfwGetKey(contextWindow, GLFW_KEY_L) == type);
		break;
	case KeyBoard::M:
		return (glfwGetKey(contextWindow, GLFW_KEY_M) == type);
		break;
	case KeyBoard::N:
		return (glfwGetKey(contextWindow, GLFW_KEY_N) == type);
		break;
	case KeyBoard::O:
		return (glfwGetKey(contextWindow, GLFW_KEY_O) == type);
		break;
	case KeyBoard::P:
		break;
	case KeyBoard::Q:
		break;
	case KeyBoard::R:
		break;
	case KeyBoard::S:
		break;
	case KeyBoard::T:
		break;
	case KeyBoard::U:
		break;
	case KeyBoard::V:
		break;
	case KeyBoard::W:
		break;
	case KeyBoard::X:
		break;
	case KeyBoard::Y:
		break;
	case KeyBoard::Z:
		break;
	case KeyBoard::One:
		break;
	case KeyBoard::Two:
		break;
	case KeyBoard::Three:
		break;
	case KeyBoard::Four:
		break;
	case KeyBoard::Five:
		break;
	case KeyBoard::Six:
		break;
	case KeyBoard::Seven:
		break;
	case KeyBoard::Eight:
		break;
	case KeyBoard::Nine:
		break;
	case KeyBoard::Space:
		break;
	case KeyBoard::Apostrophe:
		break;
	case KeyBoard::Comma:
		break;
	case KeyBoard::Minus:
		break;
	case KeyBoard::Point:
		break;
	case KeyBoard::Slash:
		break;
	case KeyBoard::Semicolon:
		break;
	case KeyBoard::Equal:
		break;
	case KeyBoard::LeftBracket:
		break;
	case KeyBoard::Backslash:
		break;
	case KeyBoard::RightBracket:
		break;
	case KeyBoard::GraveAccent:
		break;
	case KeyBoard::Escape:
		break;
	case KeyBoard::Enter:
		break;
	case KeyBoard::Tab:
		break;
	case KeyBoard::Backspace:
		break;
	case KeyBoard::Insert:
		break;
	case KeyBoard::Supr:
		break;
	case KeyBoard::RightArrow:
		break;
	case KeyBoard::LeftArrow:
		break;
	case KeyBoard::DownArrow:
		break;
	case KeyBoard::UpArrow:
		break;
	case KeyBoard::Page_up:
		break;
	case KeyBoard::Page_down:
		break;
	case KeyBoard::Home:
		break;
	case KeyBoard::End:
		break;
	case KeyBoard::CapsLock:
		break;
	case KeyBoard::ScrollLock:
		break;
	case KeyBoard::NumLock:
		break;
	case KeyBoard::PrintScreen:
		break;
	case KeyBoard::Pause:
		break;
	case KeyBoard::F1:
		break;
	case KeyBoard::F2:
		break;
	case KeyBoard::F3:
		break;
	case KeyBoard::F4:
		break;
	case KeyBoard::F5:
		break;
	case KeyBoard::F6:
		break;
	case KeyBoard::F7:
		break;
	case KeyBoard::F8:
		break;
	case KeyBoard::F9:
		break;
	case KeyBoard::F10:
		break;
	case KeyBoard::F11:
		break;
	case KeyBoard::F12:
		break;
	case KeyBoard::F13:
		break;
	case KeyBoard::F14:
		break;
	case KeyBoard::F15:
		break;
	case KeyBoard::F16:
		break;
	case KeyBoard::F17:
		break;
	case KeyBoard::F18:
		break;
	case KeyBoard::F19:
		break;
	case KeyBoard::F20:
		break;
	case KeyBoard::F21:
		break;
	case KeyBoard::F22:
		break;
	case KeyBoard::F23:
		break;
	case KeyBoard::F24:
		break;
	case KeyBoard::F25:
		break;
	case KeyBoard::KeyPad_0:
		break;
	case KeyBoard::KeyPad_1:
		break;
	case KeyBoard::KeyPad_2:
		break;
	case KeyBoard::KeyPad_3:
		break;
	case KeyBoard::KeyPad_4:
		break;
	case KeyBoard::KeyPad_5:
		break;
	case KeyBoard::KeyPad_6:
		break;
	case KeyBoard::KeyPad_7:
		break;
	case KeyBoard::KeyPad_8:
		break;
	case KeyBoard::KeyPad_9:
		break;
	case KeyBoard::KeyPadDecimal:
		break;
	case KeyBoard::KeyPadDivide:
		break;
	case KeyBoard::KeyPadMultiply:
		break;
	case KeyBoard::KeyPadSubtract:
		break;
	case KeyBoard::KeyPadAdd:
		break;
	case KeyBoard::KeyPadEnter:
		break;
	case KeyBoard::KeypadEqual:
		break;
	case KeyBoard::LeftShift:
		break;
	case KeyBoard::LeftControl:
		break;
	case KeyBoard::LeftAlt:
		break;
	case KeyBoard::LeftSuper:
		break;
	case KeyBoard::RightShift:
		break;
	case KeyBoard::RightControl:
		break;
	case KeyBoard::RightAlt:
		break;
	case KeyBoard::RightSuper:
		break;
	case KeyBoard::Menu:
		break;
	case KeyBoard::MouseButton1:
		break;
	case KeyBoard::MouseButton2:
		break;
	case KeyBoard::MouseButton3:
		break;
	case KeyBoard::MouseButton4:
		break;
	case KeyBoard::MouseButton5:
		break;
	case KeyBoard::MouseButton6:
		break;
	case KeyBoard::MouseButton7:
		break;
	case KeyBoard::MouseButtonLast:
		break;
	case KeyBoard::MouseButtonLeft:
		break;
	case KeyBoard::MouseButtonMiddle:
		break;
	default:
		return false;
		break;
	}
	*/

