#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_user.h"

namespace ImGui
{
	bool LabellessInputText(const char* label, char* buf, size_t buf_size, float width)
	{
		auto pos = GetCursorPos();
		PushItemWidth(width < 0 ? GetContentRegionAvail().x : width);
		char tmp[32];
		strcpy(tmp, "##");
		strcat(tmp, label);
		bool ret = InputText(tmp, buf, buf_size);
		if (buf[0] == 0 && !IsItemActive())
		{
			pos.x += GetStyle().FramePadding.x;
			SetCursorPos(pos);
			AlignTextToFramePadding();
			TextColored(GetStyle().Colors[ImGuiCol_TextDisabled], "%s", label);
		}
		PopItemWidth();
		return ret;
	}

    // Custom

	void BeginColumnTable(const char* columnsId, ImVec2 size, ColumnHeader* headers, int count, bool border)
	{
       if (count <= 0) return;

       BeginChild(columnsId, size);

       char str_id[256];
       ImFormatString(str_id, IM_ARRAYSIZE(str_id), "col_%s", columnsId);
       Columns(count, str_id, border);

       ImGuiStyle& style = GetStyle();
       float headerOffset = 0.0f;
       for (int i = 0; i < count; i++)
       {
           ColumnHeader& header = headers[i];

           if (!header.IsSetup)
           {
               SetColumnOffset(i, headerOffset);

               const ImVec2 textsize = CalcTextSize(header.Label, nullptr, true);
               const float colSizeX = (textsize.x + 2 * style.ItemSpacing.x);
               if (header.Size < 0) header.Size = colSizeX;

               headerOffset += header.Size;

               header.IsSetup = true;
           }
           else
           {
               if (i < (count - 1))
               {
                   float curOffset = headerOffset;
                   headerOffset = GetColumnOffset(i + 1);
                   header.Size = headerOffset - curOffset;
               }
           }

           Selectable(header.Label);
           if (IsItemClicked() && header.OnClick != nullptr)
           {
               header.OnClick();
           }
           NextColumn();
       }

		Columns(1);
		EndChild();

        // Begin Content
		BeginChild(columnsId); // Needed to exclude column header from table scroll
		BeginChild(columnsId, ImVec2(0, 0), true);
		Columns(count, columnsId, border);

		float contentOffset = 0.0f;
		for (int i = 0; i < count; i++)
		{
			ColumnHeader& header = headers[i];
			SetColumnOffset(i, contentOffset);
			contentOffset += header.Size;
		}
	}

	void EndColumnTable(int count)
	{
		if (count <= 0) return;

		Columns(1);
		EndChild();
		EndChild();
	}

} // namespace ImGui

