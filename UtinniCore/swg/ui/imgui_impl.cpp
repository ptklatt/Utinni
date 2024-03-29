/**
 * MIT License
 *
 * Copyright (c) 2020 Philip Klatt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

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
#include "swg/misc/config.h"
#include "command_parser.h"
#include "cui_io.h"
#include "swg/graphics/directx9.h"
#include "swg/game/game.h"
#include "swg/scene/render_world.h"

#pragma comment(lib, "imgui/lib/imgui.lib")

using namespace utinni;
using namespace swg::math;

namespace imgui_impl
{

static std::vector<void(*)()> renderCallbacks;

bool enableUi;
bool rendering;

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


 int GetWidth()
 {
	  return Graphics::getCurrentRenderTargetWidth() / 3;
 }

 int GetHeight()
 {
	  return Graphics::getCurrentRenderTargetHeight() / 3;
 }

 void DrawDepthWindow()
 {
	  auto depthTex = directX::getDepthTexture();
	  if (depthTex == nullptr || depthTex->getTextureColor() == nullptr || utinni::Game::getPlayer() == nullptr)
			return;

	  ImVec2 size2(GetWidth() + 5, GetHeight() + 31);
	  ImGui::SetNextWindowSize(size2);
	  if (ImGui::Begin("Depth", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoCollapse))
	  {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			const ImVec2 pos = ImGui::GetCursorScreenPos();
			const ImVec2 posMax(pos.x + GetWidth(), pos.y + GetHeight());

			ImGui::SetNextWindowSize(size2);
			ImGui::BeginChild("GameWindow");

			ImGui::GetWindowDrawList()->AddImage((void*)depthTex->getTextureDepth(), pos, posMax);

			ImGui::EndChild();

			ImGui::SetWindowSize(size2);
			ImGui::PopStyleVar();
	  }
 }

 void DrawColorWindow()
 {
	  auto colorTex = directX::getDepthTexture();
	  if (colorTex == nullptr || colorTex->getTextureColor() == nullptr || utinni::Game::getPlayer() == nullptr)
			return;

	  ImVec2 size2(GetWidth() + 5, GetHeight() + 31);
	  ImGui::SetNextWindowSize(size2);
	  if (ImGui::Begin("Color", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoCollapse))
	  {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			const ImVec2 pos = ImGui::GetCursorScreenPos();
			const ImVec2 posMax(pos.x + GetWidth(), pos.y + GetHeight());

			ImGui::SetNextWindowSize(size2);
			ImGui::BeginChild("GameWindow");
			ImGui::GetWindowDrawList()->AddImage((void*)colorTex->getTextureColor(), pos, posMax);
			ImGui::EndChild();

			ImGui::SetWindowSize(size2);
			ImGui::PopStyleVar();
	  }
 }


 static bool imguiHasHover = false;
 bool gameInputSuspended = false;
 void render()
 {
	  if (isSetup)
	  {
			rendering = true;
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			static bool showDepthWindow = false;
			static bool showColorWindow = false;
			if (!enableUi)
			{
				 ImGui::Begin("Tests", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse); // ImVec2(250, 300), 0.9f,  ImGuiWindowFlags_NoResize |
				 {
					  if (ImGui::Button("Test"))
					  {
							//CuiMediatorFactory::activate("Testzzz");
					  }

					  auto depthTex = directX::getDepthTexture();
					  if (depthTex != nullptr)
					  {
							if (ImGui::Checkbox("Show Depth Window", &showDepthWindow)) {  }
							if (ImGui::Checkbox("Show Color Window", &showColorWindow)) {  }

							int stage = depthTex->getStage();
							if (ImGui::SliderInt("Stage", &stage, 0, 11)) { depthTex->setStage(stage); }
					  }
				 }

				 for (const auto& func : renderCallbacks) // ToDo add an additional callback to host controls in the future main ImGui window
				 {
					  func();
				 }
			}

			if (showDepthWindow)
			{
				 DrawDepthWindow();
			}

			if (showColorWindow)
			{
				 DrawColorWindow();
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
			rendering = false;
	  }
 }

bool isRendering()
{
	 return rendering;
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

static std::vector<void(*)()> onGizmoEnabledCallbacks;
static std::vector<void(*)()> onGizmoDisabledCallbacks;
static std::vector<void(*)()> onGizmoPositionChangedCallbacks;
static std::vector<void(*)()> onGizmoRotationChangedCallbacks;

namespace imgui_gizmo
{
bool enabled = false;
bool gizmoHasMouseHover = false;
bool wasUsed = false;

static Transform originalTransform;
static Object* object = nullptr;

static ImGuizmo::MODE gizmoMode(ImGuizmo::MODE::LOCAL);
static ImGuizmo::OPERATION operationMode(ImGuizmo::TRANSLATE);

static bool useSnap = false;
static float snap[3] = { 1, 1, 1 };

void enable(Object* obj)
{
	 object = obj;
	 enabled = true;

	 for (const auto& func : onGizmoEnabledCallbacks)
	 {
		  func();
	 }
}

void disable()
{
	 enabled = false;
	 object = nullptr;

	 for (const auto& func : onGizmoDisabledCallbacks)
	 {
		  func();
	 }

	 // Ensure it's set to false in case the gizmo is disabled with mouse hovered
	 gizmoHasMouseHover = false;
}

bool isEnabled()
{
	 return enabled;
}

bool hasMouseHover()
{
	 return gizmoHasMouseHover;
}

void addOnEnabledCallback(void(*func)())
{
	 onGizmoEnabledCallbacks.emplace_back(func);
}

void addOnDisabledCallback(void(*func)())
{
	 onGizmoDisabledCallbacks.emplace_back(func);
}

void addOnPositionChangedCallback(void(*func)())
{
	 onGizmoPositionChangedCallbacks.emplace_back(func);
}

void addOnRotationChangedCallback(void(*func)())
{
	 onGizmoRotationChangedCallbacks.emplace_back(func);
}

void toggleGizmoMode()
{
	 if (gizmoMode != ImGuizmo::MODE::LOCAL)
	 {
		  gizmoMode = ImGuizmo::MODE::LOCAL;
	 }
	 else
	 {
		  gizmoMode = ImGuizmo::MODE::WORLD;
	 }
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

void setGizmoModeToWorld()
{
	 gizmoMode = ImGuizmo::MODE::WORLD;
}

void setGizmoModeToLocal()
{
	 gizmoMode = ImGuizmo::MODE::LOCAL;
}

bool isGizmoModeToLocal()
{
	 return gizmoMode == ImGuizmo::MODE::LOCAL;
}

bool isGizmoModeToWorld()
{
	 return gizmoMode == ImGuizmo::MODE::WORLD;
}

void setOperationModeToTranslate()
{
	 operationMode = ImGuizmo::TRANSLATE;
}

void setOperationModeToRotate()
{
	 operationMode = ImGuizmo::ROTATE;
}

bool isOperationModeTransform()
{
	 return operationMode == ImGuizmo::TRANSLATE;
}

bool isOperationModeRotate()
{
	 return operationMode == ImGuizmo::ROTATE;
}

void toggleSnap()
{
	 useSnap = !useSnap;
}

void enableSnap(bool value)
{
	 useSnap = value;
}

bool isSnapOn()
{
	 return useSnap;
}

void setSnapSize(float value)
{
	 snap[0] = value;
	 snap[1] = value;
	 snap[2] = value;
}

void editTransform(const float* cameraView, float* cameraProjection, float* matrix)
{
	 static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	 static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	 static bool boundSizing = false;
	 static bool boundSizingSnap = false;

	 ImGuizmo::Manipulate(cameraView, cameraProjection, operationMode, gizmoMode, matrix, nullptr, useSnap ? &snap[0] : nullptr, boundSizing ? bounds : nullptr, boundSizingSnap ? boundsSnap : nullptr);
}

void draw()
{
	 if (GroundScene::get() == nullptr || object == nullptr || !enabled)
	 {
		  return;
	 }

	 Camera* camera = GroundScene::get()->getCurrentCamera();

	 // Set up the matrices for the gizmo
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

	 if (ImGuizmo::IsUsing())
	 {
		  // If the mouse went up or it's the initial use, store the original transform
		  if (!wasUsed)
		  {
				originalTransform = Transform(*object->getTransform_o2w());
		  }

		  if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Escape)))
		  {
				object->setTransform_o2w(originalTransform);
				Vector originalPos = originalTransform.getPosition();
				object->positionAndRotationChanged(false, originalPos);
				wasUsed = false;
				ImGuizmo::Enable(false);
				ImGuizmo::Enable(true);
				return;
		  }

		  // Pass the updated matrix back to the object
		  float* updatedObjMatrix = &Matrix4x4().matrix[0][0];
		  Matrix4x4::transpose(objMatrix, updatedObjMatrix);

		  Transform previousTransform = Transform(*object->getTransform_o2w());
		  object->setTransform_o2w(*(Transform*)updatedObjMatrix);
		  Vector oldPos = previousTransform.getPosition();
		  object->positionAndRotationChanged(false, oldPos);

		  wasUsed = true;
	 }
	 else
	 {
		  // If there the gizmo was used and there was a change, notify the callbacks
		  if (wasUsed)
		  {
				if (originalTransform.getPosition() != object->getTransform_o2w()->getPosition())
				{
					 for (const auto& func : onGizmoPositionChangedCallbacks)
					 {
						  func();
					 }
				}

				if (!object->getTransform_o2w()->isRotationEqual(originalTransform))
				{
					 for (const auto& func : onGizmoRotationChangedCallbacks)
					 {
						  func();
					 }
				}
		  }
		  wasUsed = false;
	 }
}
}
