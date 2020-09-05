using System.Drawing;

namespace UtinniUiDotNet
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
                return Color.FromArgb(238, 238, 238);
            }
            return Color.FromArgb(238, 238, 238);
        }
    }
}
