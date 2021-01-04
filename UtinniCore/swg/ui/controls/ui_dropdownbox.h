/**
* MIT License
*
*Copyright(c) 2020 Philip Klatt
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
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

#pragma once
#include "utinni.h"
#include "ui_widget.h"

namespace utinni
{
UTINNI_API class UIDropdownbox : public UIWidget // Size (Excluding base class): 44 (0x2C)
{
public:
	swgptr UIDropdownbox_unkv01;
	swgptr UIDropdownbox_unkv02;
	swgptr UIDropdownbox_unkv03;
	swgptr UIDropdownbox_unkv04;
	swgptr UIDropdownbox_unkv05;
	swgptr UIDropdownbox_unkv06;
	swgptr UIDropdownbox_unkv07;
	swgptr UIDropdownbox_unkv08;
	swgptr UIDropdownbox_unkv09;

	UIDropdownbox();
};

}
