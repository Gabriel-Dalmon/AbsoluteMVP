#include "pch.h"
//#include "System.h"
#include "EventManager.h"

template<typename Key, typename Value>
std::ostream& operator << (std::ostream& os, std::map<Key, Value>& map)
{
	os << "{\n";
	for (const auto& pair : map)
	{
		os << "\t{" << pair.first << " => " << pair.second << "}\n";
	}
	os << "}";

	return os;
}

void EventManager::Init()
{
	m_InputList = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		VK_BACK, VK_TAB, VK_RETURN, VK_ESCAPE, VK_SPACE, VK_PRIOR, VK_NEXT, VK_END, VK_HOME, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN,
		VK_INSERT, VK_DELETE, VK_OEM_PLUS, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_COMMA, VK_OEM_1, VK_OEM_2, VK_OEM_3,
		VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7,
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
		VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE
	};

	m_CodeToEventNamePressed = {
		{'A', EventName::KEY_A_PRESSED},
		{'B', EventName::KEY_B_PRESSED},
		{'C', EventName::KEY_C_PRESSED},
		{'D', EventName::KEY_D_PRESSED},
		{'E', EventName::KEY_E_PRESSED},
		{'F', EventName::KEY_F_PRESSED},
		{'G', EventName::KEY_G_PRESSED},
		{'H', EventName::KEY_H_PRESSED},
		{'I', EventName::KEY_I_PRESSED},
		{'J', EventName::KEY_J_PRESSED},
		{'K', EventName::KEY_K_PRESSED},
		{'M', EventName::KEY_M_PRESSED},
		{'N', EventName::KEY_N_PRESSED},
		{'L', EventName::KEY_L_PRESSED},
		{'O', EventName::KEY_O_PRESSED},
		{'P', EventName::KEY_P_PRESSED},
		{'Q', EventName::KEY_Q_PRESSED},
		{'R', EventName::KEY_R_PRESSED},
		{'S', EventName::KEY_S_PRESSED},
		{'T', EventName::KEY_T_PRESSED},
		{'U', EventName::KEY_U_PRESSED},
		{'V', EventName::KEY_V_PRESSED},
		{'W', EventName::KEY_W_PRESSED},
		{'X', EventName::KEY_X_PRESSED},
		{'Y', EventName::KEY_Y_PRESSED},
		{'Z', EventName::KEY_Z_PRESSED},

		{'0', EventName::KEY_0_PRESSED},
		{'1', EventName::KEY_1_PRESSED},
		{'2', EventName::KEY_2_PRESSED},
		{'3', EventName::KEY_3_PRESSED},
		{'4', EventName::KEY_4_PRESSED},
		{'5', EventName::KEY_5_PRESSED},
		{'6', EventName::KEY_6_PRESSED},
		{'7', EventName::KEY_7_PRESSED},
		{'8', EventName::KEY_8_PRESSED},
		{'9', EventName::KEY_9_PRESSED},

		{VK_NUMPAD0, EventName::KEY_NUMPAD_0_PRESSED},
		{VK_NUMPAD1, EventName::KEY_NUMPAD_1_PRESSED},
		{VK_NUMPAD2, EventName::KEY_NUMPAD_2_PRESSED},
		{VK_NUMPAD3, EventName::KEY_NUMPAD_3_PRESSED},
		{VK_NUMPAD4, EventName::KEY_NUMPAD_4_PRESSED},
		{VK_NUMPAD5, EventName::KEY_NUMPAD_5_PRESSED},
		{VK_NUMPAD6, EventName::KEY_NUMPAD_6_PRESSED},
		{VK_NUMPAD7, EventName::KEY_NUMPAD_7_PRESSED},
		{VK_NUMPAD8, EventName::KEY_NUMPAD_8_PRESSED},
		{VK_NUMPAD9, EventName::KEY_NUMPAD_9_PRESSED},

		{VK_F1, EventName::KEY_F1_PRESSED},
		{VK_F2, EventName::KEY_F2_PRESSED},
		{VK_F3, EventName::KEY_F3_PRESSED},
		{VK_F4, EventName::KEY_F4_PRESSED},
		{VK_F5, EventName::KEY_F5_PRESSED},
		{VK_F6, EventName::KEY_F6_PRESSED},
		{VK_F7, EventName::KEY_F7_PRESSED},
		{VK_F8, EventName::KEY_F8_PRESSED},
		{VK_F9, EventName::KEY_F9_PRESSED},
		{VK_F10, EventName::KEY_F10_PRESSED},
		{VK_F11, EventName::KEY_F11_PRESSED},
		{VK_F12, EventName::KEY_F12_PRESSED},

		{VK_TAB, EventName::KEY_TAB_PRESSED},
		{VK_RETURN, EventName::KEY_ENTER_PRESSED},
		{VK_LSHIFT, EventName::KEY_LSHIFT_PRESSED},
		{VK_RSHIFT, EventName::KEY_RSHIFT_PRESSED},
		{VK_LCONTROL, EventName::KEY_LCTRL_PRESSED},
		{VK_RCONTROL, EventName::KEY_RCTRL_PRESSED},
		{VK_LMENU, EventName::KEY_LALT_PRESSED},
		{VK_RMENU, EventName::KEY_RALT_PRESSED},
		{VK_SPACE, EventName::KEY_SPACE_PRESSED},
		{VK_ESCAPE, EventName::KEY_ESCAPE_PRESSED},
		{VK_BACK, EventName::KEY_BACKSPACE_PRESSED},
		{VK_LWIN, EventName::KEY_LSYSTEM_PRESSED},
		{VK_RWIN, EventName::KEY_RSYSTEM_PRESSED},
		{VK_OEM_4, EventName::KEY_LBRACKET_PRESSED},
		{VK_OEM_6, EventName::KEY_RBRACKET_PRESSED},
		{VK_OEM_1, EventName::KEY_SEMICOLON_PRESSED},
		{VK_OEM_COMMA, EventName::KEY_COMMA_PRESSED},
		{VK_OEM_PERIOD, EventName::KEY_PERIOD_PRESSED},
		{VK_OEM_7, EventName::KEY_APOSTROPHE_PRESSED},
		{VK_OEM_5, EventName::KEY_SLASH_PRESSED},
		{VK_OEM_5, EventName::KEY_BACKSLASH_PRESSED},
		{VK_OEM_3, EventName::KEY_GRAVE_PRESSED},
		{0xE8, EventName::KEY_EQUAL_PRESSED},
		{VK_OEM_PLUS, EventName::KEY_ADD_PRESSED},
		{VK_OEM_MINUS, EventName::KEY_SUBTRACT_PRESSED},
		{VK_DIVIDE, EventName::KEY_DIVIDE_PRESSED},
		{VK_MULTIPLY, EventName::KEY_MULTIPLY_PRESSED},
		{0xE8, EventName::KEY_MENU_PRESSED},
		{0xE8, EventName::KEY_HYPHEN_PRESSED},
		{VK_CAPITAL, EventName::KEY_CAPS_LOCK_PRESSED},
		{VK_INSERT, EventName::KEY_INSERT_PRESSED},
		{VK_PAUSE, EventName::KEY_PAUSE_PRESSED},
		{VK_DELETE, EventName::KEY_DELETE_PRESSED},
		{VK_HOME, EventName::KEY_HOME_PRESSED},
		{VK_END, EventName::KEY_END_PRESSED},
		{VK_PRIOR, EventName::KEY_PAGE_UP_PRESSED},
		{VK_NEXT, EventName::KEY_PAGE_DOWN_PRESSED},
		{VK_UP, EventName::KEY_ARROW_UP_PRESSED},
		{VK_DOWN, EventName::KEY_ARROW_DOWN_PRESSED},
		{VK_LEFT, EventName::KEY_ARROW_LEFT_PRESSED},
		{VK_RIGHT, EventName::KEY_ARROW_RIGHT_PRESSED},
	};

	m_CodeToEventNameReleased = {
		{'A', EventName::KEY_A_RELEASED},
		{'B', EventName::KEY_B_RELEASED},
		{'C', EventName::KEY_C_RELEASED},
		{'D', EventName::KEY_D_RELEASED},
		{'E', EventName::KEY_E_RELEASED},
		{'F', EventName::KEY_F_RELEASED},
		{'G', EventName::KEY_G_RELEASED},
		{'H', EventName::KEY_H_RELEASED},
		{'I', EventName::KEY_I_RELEASED},
		{'J', EventName::KEY_J_RELEASED},
		{'K', EventName::KEY_K_RELEASED},
		{'M', EventName::KEY_M_RELEASED},
		{'N', EventName::KEY_N_RELEASED},
		{'L', EventName::KEY_L_RELEASED},
		{'O', EventName::KEY_O_RELEASED},
		{'P', EventName::KEY_P_RELEASED},
		{'Q', EventName::KEY_Q_RELEASED},
		{'R', EventName::KEY_R_RELEASED},
		{'S', EventName::KEY_S_RELEASED},
		{'T', EventName::KEY_T_RELEASED},
		{'U', EventName::KEY_U_RELEASED},
		{'V', EventName::KEY_V_RELEASED},
		{'W', EventName::KEY_W_RELEASED},
		{'X', EventName::KEY_X_RELEASED},
		{'Y', EventName::KEY_Y_RELEASED},
		{'Z', EventName::KEY_Z_RELEASED},

		{'0', EventName::KEY_0_RELEASED},
		{'1', EventName::KEY_1_RELEASED},
		{'2', EventName::KEY_2_RELEASED},
		{'3', EventName::KEY_3_RELEASED},
		{'4', EventName::KEY_4_RELEASED},
		{'5', EventName::KEY_5_RELEASED},
		{'6', EventName::KEY_6_RELEASED},
		{'7', EventName::KEY_7_RELEASED},
		{'8', EventName::KEY_8_RELEASED},
		{'9', EventName::KEY_9_RELEASED},

		{VK_NUMPAD0, EventName::KEY_NUMPAD_0_RELEASED},
		{VK_NUMPAD1, EventName::KEY_NUMPAD_1_RELEASED},
		{VK_NUMPAD2, EventName::KEY_NUMPAD_2_RELEASED},
		{VK_NUMPAD3, EventName::KEY_NUMPAD_3_RELEASED},
		{VK_NUMPAD4, EventName::KEY_NUMPAD_4_RELEASED},
		{VK_NUMPAD5, EventName::KEY_NUMPAD_5_RELEASED},
		{VK_NUMPAD6, EventName::KEY_NUMPAD_6_RELEASED},
		{VK_NUMPAD7, EventName::KEY_NUMPAD_7_RELEASED},
		{VK_NUMPAD8, EventName::KEY_NUMPAD_8_RELEASED},
		{VK_NUMPAD9, EventName::KEY_NUMPAD_9_RELEASED},

		{VK_F1, EventName::KEY_F1_RELEASED},
		{VK_F2, EventName::KEY_F2_RELEASED},
		{VK_F3, EventName::KEY_F3_RELEASED},
		{VK_F4, EventName::KEY_F4_RELEASED},
		{VK_F5, EventName::KEY_F5_RELEASED},
		{VK_F6, EventName::KEY_F6_RELEASED},
		{VK_F7, EventName::KEY_F7_RELEASED},
		{VK_F8, EventName::KEY_F8_RELEASED},
		{VK_F9, EventName::KEY_F9_RELEASED},
		{VK_F10, EventName::KEY_F10_RELEASED},
		{VK_F11, EventName::KEY_F11_RELEASED},
		{VK_F12, EventName::KEY_F12_RELEASED},

		{VK_TAB, EventName::KEY_TAB_RELEASED},
		{VK_RETURN, EventName::KEY_ENTER_RELEASED},
		{VK_LSHIFT, EventName::KEY_LSHIFT_RELEASED},
		{VK_RSHIFT, EventName::KEY_RSHIFT_RELEASED},
		{VK_LCONTROL, EventName::KEY_LCTRL_RELEASED},
		{VK_RCONTROL, EventName::KEY_RCTRL_RELEASED},
		{VK_LMENU, EventName::KEY_LALT_RELEASED},
		{VK_RMENU, EventName::KEY_RALT_RELEASED},
		{VK_SPACE, EventName::KEY_SPACE_RELEASED},
		{VK_ESCAPE, EventName::KEY_ESCAPE_RELEASED},
		{VK_BACK, EventName::KEY_BACKSPACE_RELEASED},
		{VK_LWIN, EventName::KEY_LSYSTEM_RELEASED},
		{VK_RWIN, EventName::KEY_RSYSTEM_RELEASED},
		{VK_OEM_4, EventName::KEY_LBRACKET_RELEASED},
		{VK_OEM_6, EventName::KEY_RBRACKET_RELEASED},
		{VK_OEM_1, EventName::KEY_SEMICOLON_RELEASED},
		{VK_OEM_COMMA, EventName::KEY_COMMA_RELEASED},
		{VK_OEM_PERIOD, EventName::KEY_PERIOD_RELEASED},
		{VK_OEM_7, EventName::KEY_APOSTROPHE_RELEASED},
		{VK_OEM_5, EventName::KEY_SLASH_RELEASED},
		{VK_OEM_5, EventName::KEY_BACKSLASH_RELEASED},
		{VK_OEM_3, EventName::KEY_GRAVE_RELEASED},
		{0xE8, EventName::KEY_EQUAL_RELEASED},
		{VK_OEM_PLUS, EventName::KEY_ADD_RELEASED},
		{VK_OEM_MINUS, EventName::KEY_SUBTRACT_RELEASED},
		{VK_DIVIDE, EventName::KEY_DIVIDE_RELEASED},
		{VK_MULTIPLY, EventName::KEY_MULTIPLY_RELEASED},
		{0xE8, EventName::KEY_MENU_RELEASED},
		{0xE8, EventName::KEY_HYPHEN_RELEASED},
		{VK_CAPITAL, EventName::KEY_CAPS_LOCK_RELEASED},
		{VK_INSERT, EventName::KEY_INSERT_RELEASED},
		{VK_PAUSE, EventName::KEY_PAUSE_RELEASED},
		{VK_DELETE, EventName::KEY_DELETE_RELEASED},
		{VK_HOME, EventName::KEY_HOME_RELEASED},
		{VK_END, EventName::KEY_END_RELEASED},
		{VK_PRIOR, EventName::KEY_PAGE_UP_RELEASED},
		{VK_NEXT, EventName::KEY_PAGE_DOWN_RELEASED},
		{VK_UP, EventName::KEY_ARROW_UP_RELEASED},
		{VK_DOWN, EventName::KEY_ARROW_DOWN_RELEASED},
		{VK_LEFT, EventName::KEY_ARROW_LEFT_RELEASED},
		{VK_RIGHT, EventName::KEY_ARROW_RIGHT_RELEASED},
	};

	for (auto& pair : m_CodeToEventNameReleased)
	{
		m_EventPressControl.insert({ pair.second, 0 });
	}
}

void EventManager::HandleEvents()
{
	for (int i = 0; i < m_InputList.size(); i++)
	{
		SHORT keyState = GetAsyncKeyState(m_InputList[i]);
		if (keyState & 0x1)
		{
			for (auto& pair : m_CodeToEventNamePressed)
			{
				if (pair.first == m_InputList[i] && m_EventPressControl[pair.second] == 0)
				{
					for (int j = 0; j < eventCallbacksMap[pair.second].size(); j++)
					{
						eventCallbacksMap[pair.second][i]->execute();
						if (m_EventPressControl[pair.second] == 0)
						{
							m_EventPressControl[pair.second] = 1;
						}
						break;
					}
				}
			}
		}
		else if (!(keyState & 0x800))
		{
			for (auto& pair : m_EventPressControl)
			{
				if (pair.second == 1)
				{
					pair.second = 0;
					for (int j = 0; j < eventCallbacksMap[pair.first].size(); j++)
					{
						eventCallbacksMap[pair.first][j]->execute();
					}
				}
			}
		}
	}
}

void EventManager::OnKeyPressed(int key)
{
	std::cout << "Key pressed: " << key << std::endl;
}

void EventManager::OnKeyReleased(int key)
{
	std::cout << "Key released: " << key << std::endl;
}
