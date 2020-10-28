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

using System.Drawing;

namespace UtinniCoreDotNet.UI.Theme
{
    public static class Colors
    {
        public enum Themes
        {
            Custom,
            Dark,
            Light
        }

        public static Themes Theme = Themes.Dark;

        public const float DisabledScalar = 0.8f;
        public const float HighlightScalar = 1.25f;
        public const float PressedScalar = 1.5f;

        public static Color Primary()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(40, 40, 40);
            }

            return Color.FromArgb(238, 238, 238);
        }

        public static Color PrimaryHighlight()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(64, 64, 64);
            }

            return Color.FromArgb(238, 238, 238);
        }

        public static Color PrimaryShadow()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(25, 25, 25);
            }

            return Color.FromArgb(238, 238, 238);
        }


        public static Color Secondary()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(0, 122, 204);
            }

            return Color.FromArgb(0, 122, 204);
        }

        public static Color SecondaryHighlight()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(238, 238, 238);
            }

            return Color.FromArgb(238, 238, 238);
        }

        public static Color SecondaryShadow()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(238, 238, 238);
            }

            return Color.FromArgb(238, 238, 238);
        }

        public static Color Font()
        {
            if (Theme == Themes.Dark)
            {
                return Color.WhiteSmoke;
            }

            return Color.FromArgb(238, 238, 238);
        }

        public static Color FontDisabled()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(100, 100, 100);
            }

            return Color.FromArgb(100, 100, 100);
        }

        public static Color ControlBorder()
        {
            if (Theme == Themes.Dark)
            {
                return Color.FromArgb(100, 100, 100);
            }

            return Color.FromArgb(100, 100, 100);
        }

    }
}
