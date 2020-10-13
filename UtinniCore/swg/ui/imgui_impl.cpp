#include "imgui_impl.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "ImGuizmo/ImGuizmo.h"

#include <vector>

#include "swg/graphics/graphics.h"
#include "swg/misc/direct_input.h"
#include "swg/scene/ground_scene.h"
#include "swg/misc/network.h"
#include "command_parser.h"

#pragma comment(lib, "imgui/lib/imgui.lib")

using namespace utinni;
using namespace swg::math;

namespace imgui_impl
{

static std::vector<void(*)()> renderCallbacks;

bool enableUi;

void enableInternalUi(bool enable)
{
	 enableUi = enable;
}

WNDPROC originalWndProcHandler = nullptr;
IMGUI_API LRESULT hkWndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	 ImGuiIO& io = ImGui::GetIO();
	 switch (msg)
	 {
	 case WM_LBUTTONDOWN:
		  io.MouseDown[0] = true;
		  break;
	 case WM_LBUTTONUP:
		  io.MouseDown[0] = false;
		  break;
	 case WM_RBUTTONDOWN:
		  io.MouseDown[1] = true;
		  break;
	 case WM_RBUTTONUP:
		  io.MouseDown[1] = false;
		  break;
	 case WM_MBUTTONDOWN:
		  io.MouseDown[2] = true;
		  break;
	 case WM_MBUTTONUP:
		  io.MouseDown[2] = false;
		  break;
	 case WM_MOUSEWHEEL:
		  io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		  break;
	 case WM_MOUSEMOVE:
		  io.MousePos.x = (signed short)(lParam);
		  io.MousePos.y = (signed short)(lParam >> 16);
		  break;
	 case WM_KEYDOWN:
		  if (wParam < 256)
				io.KeysDown[wParam] = 1;
		  break;
	 case WM_KEYUP:
		  if (wParam < 256)
				io.KeysDown[wParam] = 0;
		  break;
	 case WM_CHAR:
		  // You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		  if (wParam > 0 && wParam < 0x10000)
				io.AddInputCharacter((unsigned short)wParam);
		  break;
	 }

	 return CallWindowProc(originalWndProcHandler, hwnd, msg, wParam, lParam);
}

bool isSetup = false;
 void setup(IDirect3DDevice9* pDevice)
 {
	  if (isSetup)
			return;

	  D3DDEVICE_CREATION_PARAMETERS cParam;

	  pDevice->GetCreationParameters(&cParam);

	  IMGUI_CHECKVERSION();
	  ImGui::CreateContext();
	  ImGui_ImplWin32_Init(cParam.hFocusWindow);
	  ImGui_ImplDX9_Init(pDevice);

	  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	  ImGui::GetIO().WantCaptureKeyboard = true;
	  ImGui::GetIO().WantCaptureMouse = true;
	  ImGui::GetIO().WantTextInput = true;
	  originalWndProcHandler = (WNDPROC)SetWindowLongPtr(cParam.hFocusWindow, GWL_WNDPROC, (LONG)hkWndProcHandler);

	  ImGui::GetIO().Fonts->AddFontFromFileTTF("C:/Windows/Fonts/micross.ttf", 14);

	  ImGuiStyle& style = ImGui::GetStyle();
	  style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	  style.Colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	  style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	  style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.48f, 0.80f, 1.00f); //ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f); //ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	  style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f); //ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	  style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	  style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.59f);
	  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f); //ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	  style.Colors[ImGuiCol_Button] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f); //ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f); //ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f); //ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	  style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.48f, 0.80f, 1.00f); //ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f); //ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	  style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);

	  style.WindowRounding = 0.f;
	  style.FramePadding = ImVec2(4, 1);
	  style.ScrollbarSize = 10.f;
	  style.ScrollbarRounding = 0.f;
	  style.GrabMinSize = 5.f;

	  isSetup = true;
 }

 static bool imguiHasHover = false;
 bool gameInputSuspended = false;
 void render()
 {
	  if (isSetup)
	  {
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			if (enableUi)
			{
				 ImGui::Begin("Tests", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse); // ImVec2(250, 300), 0.9f,  ImGuiWindowFlags_NoResize |
				 {
					  if (ImGui::Button("Test"))
					  {
							//WorldSnapshot::createAddNode("object/tangible/furniture/elegant/shared_chair_s01.iff", utinni::Game::getPlayer()->objectToParent);

							CommandParser::CommandData cmdData;

							//auto tit = swg_new<CommandParser>(cmdData, nullptr);

							//auto tit = swg_new<CommandParser>();
					  }
				 }

				 for (const auto& func : renderCallbacks) // ToDo add an additional callback to host controls in the future main ImGui window
				 {
					  func();
				 }
			}

			imgui_gizmo::draw();

			imguiHasHover = ImGui::IsAnyWindowHovered();
			if (imguiHasHover && !gameInputSuspended)
			{
				 gameInputSuspended = true;
				 DirectInput::suspend();
				 Graphics::showMouseCursor(false);
				 SetCursor(LoadCursor(nullptr, IDC_ARROW));
			}
			else if (!imguiHasHover && gameInputSuspended)
			{
				 gameInputSuspended = false;
				 DirectInput::resume();
				 Graphics::showMouseCursor(true);
				 SetCursor(nullptr);
			}

			ImGui::End();

			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	  }
 }

void addRenderCallback(void(*func)())
 {
	  renderCallbacks.emplace_back(func);
 }

bool isInternalUiHovered()
{
	 return imguiHasHover;
}

}

static std::vector<void(*)()> onGizmoPositionChangedCallbacks;
static std::vector<void(*)()> onGizmoRotationChangedCallbacks;

namespace imgui_gizmo
{
static bool recentPositionChange = false;
static bool recentRotationChange = false;
bool enabled = false;
bool gizmoHasMouseHover = false;

Object* object = nullptr;

static ImGuizmo::OPERATION operationMode(ImGuizmo::TRANSLATE);
static bool useSnap = false;

void enable(Object* obj)
{
	 object = obj;
	 enabled = true;
}

void disable()
{
	 enabled = false;
	 object = nullptr;
}

bool isEnabled()
{
	 return enabled;
}

bool hasRecentPositionChange()
{
	 return recentPositionChange;
}

bool hasRecentRotationChange()
{
	 return recentRotationChange;
}

bool hasMouseHover()
{
	 return gizmoHasMouseHover;
}

void addOnPositionChangedCallback(void(*func)())
{
	 onGizmoPositionChangedCallbacks.emplace_back(func);
}

void addOnRotationChangedCallback(void(*func)())
{
	 onGizmoRotationChangedCallbacks.emplace_back(func);
}

void toggleOperationMode()
{
    if (operationMode != ImGuizmo::TRANSLATE)
    {
        operationMode = ImGuizmo::TRANSLATE;
    }
	 else
	 {
        operationMode = ImGuizmo::ROTATE;
    }
}

void toggleSnap()
{
	 useSnap = !useSnap;
}

void editTransform(const float* cameraView, float* cameraProjection, float* matrix)
{
	 static ImGuizmo::MODE currentGizmoMode(ImGuizmo::LOCAL);
	 static float snap[3] = { 1.f, 1.f, 1.f };
	 static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	 static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	 static bool boundSizing = false;
	 static bool boundSizingSnap = false;

	 ImGuizmo::Manipulate(cameraView, cameraProjection, operationMode, currentGizmoMode, matrix, nullptr, useSnap ? &snap[0] : nullptr, boundSizing ? bounds : nullptr, boundSizingSnap ? boundsSnap : nullptr);
}

void draw()
{
	 if (GroundScene::get() == nullptr || object == nullptr || !enabled)
	 {
		  return;
	 }

	 if (!ImGui::IsAnyMouseDown())
	 {
		  if (recentPositionChange)
		  {
				recentPositionChange = false;
		  }

		  if (recentRotationChange)
		  {
				recentRotationChange = false;
		  }
	 }

	 Camera* camera = GroundScene::get()->getCurrentCamera();

	 // Set up the Matrices for the gizmo
	 Transform w2c;
	 w2c.invert(*camera->getTransform_o2w());
	 const Matrix4x4 view = Matrix4x4(w2c);
	 const Matrix4x4 objectMatrix = Matrix4x4(*object->getTransform_o2w());

	 float* viewMatrix = &Matrix4x4().matrix[0][0];
	 float* projMatrix = &Matrix4x4().matrix[0][0];
	 float* objMatrix = &Matrix4x4().matrix[0][0];

    Matrix4x4::transpose(&view.matrix[0][0], viewMatrix);
    Matrix4x4::transpose(&camera->projectionMatrix.matrix[0][0], projMatrix);
    Matrix4x4::transpose(&objectMatrix.matrix[0][0], objMatrix);

	 // Enable and draw the gizmo
	 ImGuizmo::SetRect(0, 0, Graphics::getCurrentRenderTargetWidth(), Graphics::getCurrentRenderTargetHeight());
	 ImGuizmo::BeginFrame();
	 ImGuizmo::Enable(true);
	 editTransform(viewMatrix, projMatrix, objMatrix);

	 gizmoHasMouseHover = ImGuizmo::IsOver();

	 // Pass the updated matrix back to the object
	 float* updatedObjMatrix = &Matrix4x4().matrix[0][0];
	 Matrix4x4::transpose(objMatrix, updatedObjMatrix);

	 Transform oldTransform = Transform(*object->getTransform_o2w());
	 Vector oldPos = oldTransform.getPosition();
	 object->setTransform_o2w(*(Transform*)updatedObjMatrix);
	 object->positionAndRotationChanged(false, oldPos);

	 if (oldPos != object->getTransform_o2w()->getPosition())
	 {
		  for (const auto& func : onGizmoPositionChangedCallbacks)
		  {
				func();
		  }
		  recentPositionChange = true;
	 }

	 if (!object->getTransform_o2w()->isRotationEqual(oldTransform))
	 {
		  for (const auto& func : onGizmoRotationChangedCallbacks)
		  {
				func();
		  }
		  recentRotationChange = true;
	 }
}
}
