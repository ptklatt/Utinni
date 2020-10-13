using System.Drawing;

namespace UtinniCoreDotNet.UI.Theme
{
    public static class ThemeUtility
    {
        private static int recolorRange = 5;
        public static Bitmap UpdateImageColor(Bitmap image, Color oldColor, Color newColor)
        {
            Bitmap result = new Bitmap(image);
            for (int y = 0; y < image.Height; y++)
            {
                for (int x = 0; x < image.Width; x++)
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
