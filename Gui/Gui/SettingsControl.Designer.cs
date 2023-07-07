namespace Gui
{
    partial class SettingsControl
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
            dataGridViewSettings = new DataGridView();
            ColumnProperty = new DataGridViewTextBoxColumn();
            ColumnValue = new DataGridViewComboBoxColumn();
            splitContainer1 = new SplitContainer();
            splitContainer2 = new SplitContainer();
            buttonSaveSettings = new Button();
            buttonRestoreDefault = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridViewSettings).BeginInit();
            ((System.ComponentModel.ISupportInitialize)splitContainer1).BeginInit();
            splitContainer1.Panel1.SuspendLayout();
            splitContainer1.Panel2.SuspendLayout();
            splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer2).BeginInit();
            splitContainer2.Panel1.SuspendLayout();
            splitContainer2.Panel2.SuspendLayout();
            splitContainer2.SuspendLayout();
            SuspendLayout();
            // 
            // dataGridViewSettings
            // 
            dataGridViewSettings.AllowUserToAddRows = false;
            dataGridViewSettings.AllowUserToDeleteRows = false;
            dataGridViewSettings.AllowUserToResizeColumns = false;
            dataGridViewSettings.AllowUserToResizeRows = false;
            dataGridViewSettings.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewSettings.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewSettings.Columns.AddRange(new DataGridViewColumn[] { ColumnProperty, ColumnValue });
            dataGridViewSettings.Dock = DockStyle.Fill;
            dataGridViewSettings.Location = new Point(0, 0);
            dataGridViewSettings.Margin = new Padding(4, 5, 4, 5);
            dataGridViewSettings.MultiSelect = false;
            dataGridViewSettings.Name = "dataGridViewSettings";
            dataGridViewSettings.RowHeadersWidth = 62;
            dataGridViewSettings.RowTemplate.Height = 25;
            dataGridViewSettings.Size = new Size(940, 722);
            dataGridViewSettings.TabIndex = 1;
            // 
            // ColumnProperty
            // 
            ColumnProperty.HeaderText = "Property";
            ColumnProperty.MinimumWidth = 8;
            ColumnProperty.Name = "ColumnProperty";
            // 
            // ColumnValue
            // 
            ColumnValue.HeaderText = "Value";
            ColumnValue.MinimumWidth = 8;
            ColumnValue.Name = "ColumnValue";
            ColumnValue.Resizable = DataGridViewTriState.True;
            ColumnValue.SortMode = DataGridViewColumnSortMode.Automatic;
            // 
            // splitContainer1
            // 
            splitContainer1.Dock = DockStyle.Fill;
            splitContainer1.IsSplitterFixed = true;
            splitContainer1.Location = new Point(0, 0);
            splitContainer1.Margin = new Padding(4, 5, 4, 5);
            splitContainer1.Name = "splitContainer1";
            splitContainer1.Orientation = Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            splitContainer1.Panel1.Controls.Add(dataGridViewSettings);
            // 
            // splitContainer1.Panel2
            // 
            splitContainer1.Panel2.Controls.Add(splitContainer2);
            splitContainer1.Size = new Size(940, 969);
            splitContainer1.SplitterDistance = 722;
            splitContainer1.SplitterWidth = 7;
            splitContainer1.TabIndex = 2;
            // 
            // splitContainer2
            // 
            splitContainer2.Dock = DockStyle.Fill;
            splitContainer2.IsSplitterFixed = true;
            splitContainer2.Location = new Point(0, 0);
            splitContainer2.Margin = new Padding(4, 5, 4, 5);
            splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            splitContainer2.Panel1.Controls.Add(buttonSaveSettings);
            // 
            // splitContainer2.Panel2
            // 
            splitContainer2.Panel2.Controls.Add(buttonRestoreDefault);
            splitContainer2.Size = new Size(940, 240);
            splitContainer2.SplitterDistance = 428;
            splitContainer2.SplitterWidth = 6;
            splitContainer2.TabIndex = 0;
            // 
            // buttonSaveSettings
            // 
            buttonSaveSettings.Dock = DockStyle.Fill;
            buttonSaveSettings.Location = new Point(0, 0);
            buttonSaveSettings.Margin = new Padding(4, 5, 4, 5);
            buttonSaveSettings.Name = "buttonSaveSettings";
            buttonSaveSettings.Size = new Size(428, 240);
            buttonSaveSettings.TabIndex = 0;
            buttonSaveSettings.Text = "Save";
            buttonSaveSettings.UseVisualStyleBackColor = true;
            buttonSaveSettings.Click += ButtonSaveSettings_Click;
            // 
            // buttonRestoreDefault
            // 
            buttonRestoreDefault.Dock = DockStyle.Fill;
            buttonRestoreDefault.Location = new Point(0, 0);
            buttonRestoreDefault.Margin = new Padding(4, 5, 4, 5);
            buttonRestoreDefault.Name = "buttonRestoreDefault";
            buttonRestoreDefault.Size = new Size(506, 240);
            buttonRestoreDefault.TabIndex = 0;
            buttonRestoreDefault.Text = "Restore default";
            buttonRestoreDefault.UseVisualStyleBackColor = true;
            buttonRestoreDefault.Click += ButtonRestoreDefault_Click;
            // 
            // SettingsControl
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(splitContainer1);
            Margin = new Padding(4, 5, 4, 5);
            Name = "SettingsControl";
            Size = new Size(940, 969);
            ((System.ComponentModel.ISupportInitialize)dataGridViewSettings).EndInit();
            splitContainer1.Panel1.ResumeLayout(false);
            splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer1).EndInit();
            splitContainer1.ResumeLayout(false);
            splitContainer2.Panel1.ResumeLayout(false);
            splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)splitContainer2).EndInit();
            splitContainer2.ResumeLayout(false);
            ResumeLayout(false);
        }

        #endregion

        private DataGridView dataGridViewSettings;
        private DataGridViewTextBoxColumn ColumnProperty;
        private DataGridViewComboBoxColumn ColumnValue;
        private SplitContainer splitContainer1;
        private SplitContainer splitContainer2;
        private Button buttonSaveSettings;
        private Button buttonRestoreDefault;
    }
}
