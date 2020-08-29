namespace ExampleEditorPlugin
{
    partial class ExampleEditorPlugin
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnRemoveWsNode = new System.Windows.Forms.Button();
            this.btnAddWsNode = new System.Windows.Forms.Button();
            this.lblWsNodeFunctionsExample = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnRemoveWsNode
            // 
            this.btnRemoveWsNode.Location = new System.Drawing.Point(6, 47);
            this.btnRemoveWsNode.Name = "btnRemoveWsNode";
            this.btnRemoveWsNode.Size = new System.Drawing.Size(75, 23);
            this.btnRemoveWsNode.TabIndex = 1;
            this.btnRemoveWsNode.Text = "Remove";
            this.btnRemoveWsNode.UseVisualStyleBackColor = true;
            this.btnRemoveWsNode.Click += new System.EventHandler(this.btnRemoveWsNode_Click);
            // 
            // btnAddWsNode
            // 
            this.btnAddWsNode.Location = new System.Drawing.Point(6, 18);
            this.btnAddWsNode.Name = "btnAddWsNode";
            this.btnAddWsNode.Size = new System.Drawing.Size(75, 23);
            this.btnAddWsNode.TabIndex = 2;
            this.btnAddWsNode.Text = "Add";
            this.btnAddWsNode.UseVisualStyleBackColor = true;
            this.btnAddWsNode.Click += new System.EventHandler(this.btnAddWsNode_Click);
            // 
            // lblWsNodeFunctionsExample
            // 
            this.lblWsNodeFunctionsExample.AutoSize = true;
            this.lblWsNodeFunctionsExample.Location = new System.Drawing.Point(5, 2);
            this.lblWsNodeFunctionsExample.Name = "lblWsNodeFunctionsExample";
            this.lblWsNodeFunctionsExample.Size = new System.Drawing.Size(161, 13);
            this.lblWsNodeFunctionsExample.TabIndex = 3;
            this.lblWsNodeFunctionsExample.Text = "World Snapshot Node Functions";
            // 
            // ExampleEditorPlugin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.lblWsNodeFunctionsExample);
            this.Controls.Add(this.btnAddWsNode);
            this.Controls.Add(this.btnRemoveWsNode);
            this.Name = "ExampleEditorPlugin";
            this.Size = new System.Drawing.Size(434, 155);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnRemoveWsNode;
        private System.Windows.Forms.Button btnAddWsNode;
        private System.Windows.Forms.Label lblWsNodeFunctionsExample;
    }
}
