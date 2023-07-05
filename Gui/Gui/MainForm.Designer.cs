namespace Gui
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            menuStrip = new MenuStrip();
            fileToolStripMenuItem = new ToolStripMenuItem();
            importFilesToolStripMenuItem = new ToolStripMenuItem();
            importFoldersToolStripMenuItem = new ToolStripMenuItem();
            settingsToolStripMenuItem = new ToolStripMenuItem();
            toolStrip = new ToolStrip();
            toolStripButtonImportFiles = new ToolStripButton();
            toolStripButtonImportFolders = new ToolStripButton();
            toolStripButtonStartOneShot = new ToolStripButton();
            toolStripButtonRTCorrelator = new ToolStripButton();
            toolStripButtonSettings = new ToolStripButton();
            tabControlMain = new TabControl();
            tabPageDataset = new TabPage();
            tabControlDataset = new TabControl();
            tabPage2 = new TabPage();
            dateTimePicker1 = new DateTimePicker();
            tabPage3 = new TabPage();
            menuStrip.SuspendLayout();
            toolStrip.SuspendLayout();
            tabControlMain.SuspendLayout();
            tabPageDataset.SuspendLayout();
            tabPage2.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip
            // 
            menuStrip.ImageScalingSize = new Size(20, 20);
            menuStrip.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, settingsToolStripMenuItem });
            menuStrip.Location = new Point(0, 0);
            menuStrip.Name = "menuStrip";
            menuStrip.Padding = new Padding(7, 3, 0, 3);
            menuStrip.Size = new Size(1031, 30);
            menuStrip.TabIndex = 0;
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { importFilesToolStripMenuItem, importFoldersToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(46, 24);
            fileToolStripMenuItem.Text = "File";
            // 
            // importFilesToolStripMenuItem
            // 
            importFilesToolStripMenuItem.Name = "importFilesToolStripMenuItem";
            importFilesToolStripMenuItem.Size = new Size(187, 26);
            importFilesToolStripMenuItem.Text = "Import files";
            importFilesToolStripMenuItem.Click += ImportFilesToolStripMenuItem_Click;
            // 
            // importFoldersToolStripMenuItem
            // 
            importFoldersToolStripMenuItem.Name = "importFoldersToolStripMenuItem";
            importFoldersToolStripMenuItem.Size = new Size(187, 26);
            importFoldersToolStripMenuItem.Text = "Import folders";
            importFoldersToolStripMenuItem.Click += ImportFoldersToolStripMenuItem_Click;
            // 
            // settingsToolStripMenuItem
            // 
            settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            settingsToolStripMenuItem.Size = new Size(76, 24);
            settingsToolStripMenuItem.Text = "Settings";
            settingsToolStripMenuItem.Click += SettingsToolStripMenuItem_Click;
            // 
            // toolStrip
            // 
            toolStrip.ImageScalingSize = new Size(37, 37);
            toolStrip.Items.AddRange(new ToolStripItem[] { toolStripButtonImportFiles, toolStripButtonImportFolders, toolStripButtonStartOneShot, toolStripButtonRTCorrelator, toolStripButtonSettings });
            toolStrip.Location = new Point(0, 30);
            toolStrip.Name = "toolStrip";
            toolStrip.Size = new Size(1031, 44);
            toolStrip.TabIndex = 1;
            // 
            // toolStripButtonImportFiles
            // 
            toolStripButtonImportFiles.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonImportFiles.Image = Properties.Resources.add_file_icon_6;
            toolStripButtonImportFiles.ImageTransparentColor = Color.Magenta;
            toolStripButtonImportFiles.Name = "toolStripButtonImportFiles";
            toolStripButtonImportFiles.Size = new Size(41, 41);
            toolStripButtonImportFiles.Text = "Import files";
            toolStripButtonImportFiles.Click += ToolStripButtonImportFiles_Click;
            // 
            // toolStripButtonImportFolders
            // 
            toolStripButtonImportFolders.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonImportFolders.Image = Properties.Resources.add_file_icon_10;
            toolStripButtonImportFolders.ImageTransparentColor = Color.Magenta;
            toolStripButtonImportFolders.Name = "toolStripButtonImportFolders";
            toolStripButtonImportFolders.Size = new Size(41, 41);
            toolStripButtonImportFolders.Text = "Import folders";
            toolStripButtonImportFolders.Click += ToolStripButtonImportFolders_Click;
            // 
            // toolStripButtonStartOneShot
            // 
            toolStripButtonStartOneShot.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonStartOneShot.Image = Properties.Resources.compare_xxl;
            toolStripButtonStartOneShot.ImageTransparentColor = Color.Magenta;
            toolStripButtonStartOneShot.Name = "toolStripButtonStartOneShot";
            toolStripButtonStartOneShot.Size = new Size(41, 41);
            toolStripButtonStartOneShot.Text = "One shot";
            // 
            // toolStripButtonRTCorrelator
            // 
            toolStripButtonRTCorrelator.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonRTCorrelator.Image = Properties.Resources.icon_start_2;
            toolStripButtonRTCorrelator.ImageTransparentColor = Color.Magenta;
            toolStripButtonRTCorrelator.Name = "toolStripButtonRTCorrelator";
            toolStripButtonRTCorrelator.Size = new Size(41, 41);
            toolStripButtonRTCorrelator.Text = "Realtime correlation";
            toolStripButtonRTCorrelator.Click += ToolStripButtonRTCorrelator_Click;
            // 
            // toolStripButtonSettings
            // 
            toolStripButtonSettings.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonSettings.Image = Properties.Resources.windows_settings_icon_20;
            toolStripButtonSettings.ImageTransparentColor = Color.Magenta;
            toolStripButtonSettings.Name = "toolStripButtonSettings";
            toolStripButtonSettings.Size = new Size(41, 41);
            toolStripButtonSettings.Text = "Settings";
            toolStripButtonSettings.Click += ToolStripButtonSettings_Click;
            // 
            // tabControlMain
            // 
            tabControlMain.Controls.Add(tabPageDataset);
            tabControlMain.Controls.Add(tabPage2);
            tabControlMain.Controls.Add(tabPage3);
            tabControlMain.Dock = DockStyle.Fill;
            tabControlMain.Location = new Point(0, 74);
            tabControlMain.Margin = new Padding(3, 4, 3, 4);
            tabControlMain.Name = "tabControlMain";
            tabControlMain.SelectedIndex = 0;
            tabControlMain.Size = new Size(1031, 635);
            tabControlMain.TabIndex = 2;
            // 
            // tabPageDataset
            // 
            tabPageDataset.Controls.Add(tabControlDataset);
            tabPageDataset.Location = new Point(4, 29);
            tabPageDataset.Margin = new Padding(3, 4, 3, 4);
            tabPageDataset.Name = "tabPageDataset";
            tabPageDataset.Padding = new Padding(3, 4, 3, 4);
            tabPageDataset.Size = new Size(1023, 602);
            tabPageDataset.TabIndex = 0;
            tabPageDataset.Text = "Dataset";
            tabPageDataset.UseVisualStyleBackColor = true;
            // 
            // tabControlDataset
            // 
            tabControlDataset.Dock = DockStyle.Fill;
            tabControlDataset.Location = new Point(3, 4);
            tabControlDataset.Name = "tabControlDataset";
            tabControlDataset.SelectedIndex = 0;
            tabControlDataset.Size = new Size(1017, 594);
            tabControlDataset.TabIndex = 0;
            // 
            // tabPage2
            // 
            tabPage2.Controls.Add(dateTimePicker1);
            tabPage2.Location = new Point(4, 29);
            tabPage2.Margin = new Padding(3, 4, 3, 4);
            tabPage2.Name = "tabPage2";
            tabPage2.Padding = new Padding(3, 4, 3, 4);
            tabPage2.Size = new Size(1023, 602);
            tabPage2.TabIndex = 1;
            tabPage2.Text = "tabPage2";
            tabPage2.UseVisualStyleBackColor = true;
            // 
            // dateTimePicker1
            // 
            dateTimePicker1.Location = new Point(189, 65);
            dateTimePicker1.Margin = new Padding(3, 4, 3, 4);
            dateTimePicker1.Name = "dateTimePicker1";
            dateTimePicker1.Size = new Size(228, 27);
            dateTimePicker1.TabIndex = 0;
            // 
            // tabPage3
            // 
            tabPage3.Location = new Point(4, 29);
            tabPage3.Margin = new Padding(3, 4, 3, 4);
            tabPage3.Name = "tabPage3";
            tabPage3.Padding = new Padding(3, 4, 3, 4);
            tabPage3.Size = new Size(1023, 602);
            tabPage3.TabIndex = 2;
            tabPage3.Text = "tabPage3";
            tabPage3.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1031, 709);
            Controls.Add(tabControlMain);
            Controls.Add(toolStrip);
            Controls.Add(menuStrip);
            MainMenuStrip = menuStrip;
            Margin = new Padding(3, 4, 3, 4);
            Name = "MainForm";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "MainForm";
            menuStrip.ResumeLayout(false);
            menuStrip.PerformLayout();
            toolStrip.ResumeLayout(false);
            toolStrip.PerformLayout();
            tabControlMain.ResumeLayout(false);
            tabPageDataset.ResumeLayout(false);
            tabPage2.ResumeLayout(false);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip menuStrip;
        private ToolStrip toolStrip;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem importFilesToolStripMenuItem;
        private ToolStripMenuItem importFoldersToolStripMenuItem;
        private ToolStripButton toolStripButtonImportFiles;
        private ToolStripButton toolStripButtonImportFolders;
        private ToolStripMenuItem settingsToolStripMenuItem;
        private TabControl tabControlMain;
        private TabPage tabPageDataset;
        private TabPage tabPage2;
        private DateTimePicker dateTimePicker1;
        private TabPage tabPage3;
        private ToolStripButton toolStripButtonStartOneShot;
        private TabControl tabControlDataset;
        private ToolStripButton toolStripButtonSettings;
        private ToolStripButton toolStripButtonRTCorrelator;
    }
}