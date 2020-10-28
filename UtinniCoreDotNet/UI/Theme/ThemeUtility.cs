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
    public static class ThemeUtility
    {
        private static int recolorRange = 15;
        public static Bitmap UpdateImageColor(Bitmap image, Color oldColor, Color newColor)
        {
            Bitmap result = new Bitmap(image);
            for (int y = 0; y < result.Height; y++)
            {
                for (int x = 0; x < result.Width; x++)
                {
                    Color c = result.GetPixel(x, y);
                    if (c.R >= oldColor.R - recolorRange && c.R <= oldColor.R + recolorRange &&
                        c.G >= oldColor.G - recolorRange && c.G <= oldColor.G + recolorRange &&
                        c.B >= oldColor.B - recolorRange && c.R <= oldColor.B + recolorRange)
                    {
                        int rDelta = c.R - oldColor.R;
                        int gDelta = c.G - oldColor.G;
                        int bDelta = c.B - oldColor.B;

                        int newR = ClampColor(newColor.R + rDelta, newColor.R);
                        int newG = ClampColor(newColor.G + gDelta, newColor.G);
                        int newB = ClampColor(newColor.B + bDelta, newColor.B);


                        result.SetPixel(x, y, Color.FromArgb(c.A, newR, newG, newB));
                    }
                }
            }

            return result;
        }

        public static int ClampColor(int value, int max = 255)
        {
            return (value <= 0) ? 0 : (value >= max) ? max : value;
        }

        public static Color ScaleColor(Color color, float scalar)
        {
            return Color.FromArgb(ClampColor((int)(color.R * scalar)), ClampColor((int)(color.G * scalar)), ClampColor((int)(color.B * scalar)));
        }

    }
}
