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

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using UtinniCoreDotNet.UI.Theme;

namespace UtinniCoreDotNet.UI.Controls
{
    public class UtinniSlider : Control
    {
        public event EventHandler ValueChanged;
        private void OnValueChanged()
        {
            if (ValueChanged != null)
            {
                ValueChanged(this, EventArgs.Empty);
            }
        }

        private float sliderValue = 0;
        public float Value
        {
            get { return sliderValue; }
            set
            {
                sliderValue = Math.Min(Math.Max(value, Minimum), Maximum);
                UpdateTogglePos();
                OnValueChanged();
                Invalidate();
            }
        }

        private float sliderMin;
        public float Minimum
        {
            get { return sliderMin; }
            set
            {
                sliderMin = Math.Min(value, Maximum);
                if (sliderValue < sliderMin)
                {
                    sliderValue = sliderMin;
                    if (ValueChanged != null)
                    {
                        ValueChanged(this, new EventArgs());
                    }
                }
                Invalidate();
            }
        }

        private float sliderMax = 100;
        public float Maximum 
        {
            get { return sliderMax; }
            set
            {
                sliderMax = Math.Max(value, Minimum);
                if (sliderValue > sliderMax)
                {
                    sliderValue = sliderMax;
                    if (ValueChanged != null)
                    {
                        ValueChanged(this, new EventArgs());
                    }
                }
                Invalidate();
            }
        }

        [Description("Draw Outline"), Category("Data")]
        public bool DrawOutline { get; set; } = false;
        private Pen outlinePen;

        public bool IsHovered;
        public bool IsPressed;

        private const int toggleWidth = 5;
        private int toggleX;
        private int sliderOffset;

        private int textLength;

        private SolidBrush foreColorBrush;

        private SolidBrush primaryBrush;
        private SolidBrush hoverPrimaryHighlightBrush;
        private SolidBrush pressedPrimaryBrush;
        private SolidBrush disabledPrimaryBrush;

        private SolidBrush secondaryBrush;
        private SolidBrush hoverSecondaryHighlightBrush;
        private SolidBrush pressedSecondaryBrush;
        private SolidBrush disabledSecondaryBrush;

        public UtinniSlider()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.ResizeRedraw | ControlStyles.Selectable |
                     ControlStyles.SupportsTransparentBackColor | ControlStyles.UserMouse | ControlStyles.UserPaint, true);

            base.Size = new Size(150, 20);
            base.MaximumSize = new Size(100000, 20);

            SetBackColors();
            foreColorBrush = new SolidBrush(Colors.Font());
        }

        public void SetBackColors()
        {
            Color primaryColor = Colors.PrimaryHighlight();
            primaryBrush = new SolidBrush(primaryColor);
            hoverPrimaryHighlightBrush = new SolidBrush(ThemeUtility.ScaleColor(primaryColor, Colors.HighlightScalar));
            pressedPrimaryBrush = new SolidBrush(ThemeUtility.ScaleColor(primaryColor, Colors.PressedScalar));
            disabledPrimaryBrush = new SolidBrush(ThemeUtility.ScaleColor(Colors.Primary(), Colors.DisabledScalar));

            Color secondaryColor = Colors.Secondary();
            secondaryBrush = new SolidBrush(secondaryColor);
            hoverSecondaryHighlightBrush = new SolidBrush(ThemeUtility.ScaleColor(secondaryColor, Colors.HighlightScalar));
            pressedSecondaryBrush = new SolidBrush(ThemeUtility.ScaleColor(secondaryColor, Colors.PressedScalar));
            disabledSecondaryBrush = new SolidBrush(ThemeUtility.ScaleColor(secondaryColor, Colors.DisabledScalar));

            outlinePen = new Pen(Colors.ControlBorder(), 1);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            e.Graphics.Clear(Colors.Primary());

            sliderOffset = textLength + 3;

            // Draw the main box
            if (IsHovered && !IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(hoverSecondaryHighlightBrush, sliderOffset, 0, toggleX, Height);
                e.Graphics.FillRectangle(hoverPrimaryHighlightBrush, toggleX + sliderOffset, 0, Width - sliderOffset, Height);
            }
            else if (IsHovered && IsPressed && Enabled)
            {
                e.Graphics.FillRectangle(pressedSecondaryBrush, sliderOffset, 0, toggleX, Height);
                e.Graphics.FillRectangle(pressedPrimaryBrush, toggleX + sliderOffset, 0, Width - sliderOffset, Height);
            }
            else if (!Enabled)
            {
                e.Graphics.FillRectangle(disabledSecondaryBrush, sliderOffset, 0, toggleX, Height);
                e.Graphics.FillRectangle(disabledPrimaryBrush, toggleX + sliderOffset, 0, Width - sliderOffset, Height);
            }
            else
            {
                e.Graphics.FillRectangle(secondaryBrush, sliderOffset, 0, toggleX, Height);
                e.Graphics.FillRectangle(primaryBrush, toggleX + sliderOffset, 0, Width - sliderOffset, Height);
            }

            // Draw the outline
            if (DrawOutline)
            {
                e.Graphics.DrawRectangle(outlinePen, sliderOffset, 0, Width - sliderOffset - 1, Height - 1);
            }

            OnPaintForeground(e);
        }

        protected virtual void OnPaintForeground(PaintEventArgs e)
        {
            // Draw the toggle
            e.Graphics.FillRectangle(foreColorBrush, toggleX + sliderOffset, 0, toggleWidth, 20);

            // Draw the Text
            Rectangle textRect = new Rectangle(0, 0, textLength, ClientRectangle.Height);
            TextRenderer.DrawText(e.Graphics, Text, Font, textRect, ForeColor);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            IsPressed = true;
            Invalidate();

            if (e.Button == MouseButtons.Left)
            {
                UpdateValueByPos(e.X);
            }

            base.OnMouseDown(e);
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            IsPressed = false;
            Invalidate();

            base.OnMouseUp(e);
        }

        protected override void OnMouseEnter(EventArgs e)
        {
            IsHovered = true;
            Invalidate();

            base.OnMouseEnter(e);
        }

        protected override void OnMouseLeave(EventArgs e)
        {
            IsHovered = false;
            Invalidate();

            base.OnMouseLeave(e);
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            if (IsPressed && e.Button == MouseButtons.Left && (e.X >= sliderOffset && e.X <= Width))
            {
                UpdateValueByPos(e.X);
            }
        }

        private void UpdateValueByPos(int x)
        {
            float increment = (Maximum - Minimum) / (Width - sliderOffset);
            Value = (x - sliderOffset) * increment + Minimum;
        }

        private void UpdateTogglePos()
        {
            toggleX = (int)(((Value - Minimum) * (Width - sliderOffset - toggleWidth)) / (Maximum - Minimum));
        }

        protected override void OnEnabledChanged(EventArgs e)
        {
            base.OnEnabledChanged(e);

            if (Enabled)
            {
                ForeColor = Colors.Font();
            }
            else
            {
                ForeColor = Colors.FontDisabled();
            }
        }

        protected override void OnTextChanged(EventArgs e)
        {
            base.OnTextChanged(e);
            UpdateWidth();
        }

        private void UpdateWidth()
        {
            Size size = TextRenderer.MeasureText(Text, Font);
            textLength = size.Width;
            sliderOffset = 3 + size.Width;
        }

    }
}
