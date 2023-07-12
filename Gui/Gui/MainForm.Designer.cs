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
            loadFilesToolStripMenuItem = new ToolStripMenuItem();
            loadFoldersToolStripMenuItem = new ToolStripMenuItem();
            settingsToolStripMenuItem = new ToolStripMenuItem();
            toolStrip = new ToolStrip();
            toolStripButtonLoadFiles = new ToolStripButton();
            toolStripButtonLoadFolders = new ToolStripButton();
            toolStripButtonStartOneShot = new ToolStripButton();
            toolStripButtonRTCorrelation = new ToolStripButton();
            toolStripButtonSettings = new ToolStripButton();
            toolStripButtonInfo = new ToolStripButton();
            toolStripLabelWhatToDo = new ToolStripLabel();
            tabControlMain = new TabControl();
            menuStrip.SuspendLayout();
            toolStrip.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip
            // 
            menuStrip.ImageScalingSize = new Size(20, 20);
            menuStrip.Items.AddRange(new ToolStripItem[] { fileToolStripMenuItem, settingsToolStripMenuItem });
            menuStrip.Location = new Point(0, 0);
            menuStrip.Name = "menuStrip";
            menuStrip.Size = new Size(902, 24);
            menuStrip.TabIndex = 0;
            // 
            // fileToolStripMenuItem
            // 
            fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { loadFilesToolStripMenuItem, loadFoldersToolStripMenuItem });
            fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            fileToolStripMenuItem.Size = new Size(37, 20);
            fileToolStripMenuItem.Text = "File";
            // 
            // loadFilesToolStripMenuItem
            // 
            loadFilesToolStripMenuItem.Name = "loadFilesToolStripMenuItem";
            loadFilesToolStripMenuItem.Size = new Size(180, 22);
            loadFilesToolStripMenuItem.Text = "Load files";
            loadFilesToolStripMenuItem.Click += LoadFilesToolStripMenuItem_Click;
            // 
            // loadFoldersToolStripMenuItem
            // 
            loadFoldersToolStripMenuItem.Name = "loadFoldersToolStripMenuItem";
            loadFoldersToolStripMenuItem.Size = new Size(180, 22);
            loadFoldersToolStripMenuItem.Text = "Load folder";
            loadFoldersToolStripMenuItem.Click += LoadFoldersToolStripMenuItem_Click;
            // 
            // settingsToolStripMenuItem
            // 
            settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            settingsToolStripMenuItem.Size = new Size(61, 20);
            settingsToolStripMenuItem.Text = "Settings";
            settingsToolStripMenuItem.Click += SettingsToolStripMenuItem_Click;
            // 
            // toolStrip
            // 
            toolStrip.ImageScalingSize = new Size(37, 37);
            toolStrip.Items.AddRange(new ToolStripItem[] { toolStripButtonLoadFiles, toolStripButtonLoadFolders, toolStripButtonStartOneShot, toolStripButtonRTCorrelation, toolStripButtonSettings, toolStripButtonInfo, toolStripLabelWhatToDo });
            toolStrip.Location = new Point(0, 24);
            toolStrip.Name = "toolStrip";
            toolStrip.Size = new Size(902, 44);
            toolStrip.TabIndex = 1;
            // 
            // toolStripButtonLoadFiles
            // 
            toolStripButtonLoadFiles.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonLoadFiles.Image = Properties.Resources.add_file_icon_6;
            toolStripButtonLoadFiles.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoadFiles.Name = "toolStripButtonLoadFiles";
            toolStripButtonLoadFiles.Size = new Size(41, 41);
            toolStripButtonLoadFiles.Text = "Load files";
            toolStripButtonLoadFiles.Click += ToolStripButtonLoadFiles_Click;
            // 
            // toolStripButtonLoadFolders
            // 
            toolStripButtonLoadFolders.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonLoadFolders.Image = Properties.Resources.add_file_icon_10;
            toolStripButtonLoadFolders.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoadFolders.Name = "toolStripButtonLoadFolders";
            toolStripButtonLoadFolders.Size = new Size(41, 41);
            toolStripButtonLoadFolders.Text = "Load folders";
            toolStripButtonLoadFolders.Click += ToolStripButtonLoadFolders_Click;
            // 
            // toolStripButtonStartOneShot
            // 
            toolStripButtonStartOneShot.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonStartOneShot.Image = Properties.Resources.compare_xxl;
            toolStripButtonStartOneShot.ImageTransparentColor = Color.Magenta;
            toolStripButtonStartOneShot.Name = "toolStripButtonStartOneShot";
            toolStripButtonStartOneShot.Size = new Size(41, 41);
            toolStripButtonStartOneShot.Text = "One shot";
            toolStripButtonStartOneShot.Click += ToolStripButtonStartOneShot_Click;
            // 
            // toolStripButtonRTCorrelation
            // 
            toolStripButtonRTCorrelation.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonRTCorrelation.Image = Properties.Resources.icon_start_2;
            toolStripButtonRTCorrelation.ImageTransparentColor = Color.Magenta;
            toolStripButtonRTCorrelation.Name = "toolStripButtonRTCorrelation";
            toolStripButtonRTCorrelation.Size = new Size(41, 41);
            toolStripButtonRTCorrelation.Tag = "";
            toolStripButtonRTCorrelation.Text = "Real time correlation";
            toolStripButtonRTCorrelation.Click += ToolStripButtonRTCorrelation_Click;
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
            // toolStripButtonInfo
            // 
            toolStripButtonInfo.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonInfo.Image = Properties.Resources.info_icon_svg_5;
            toolStripButtonInfo.ImageTransparentColor = Color.Magenta;
            toolStripButtonInfo.Name = "toolStripButtonInfo";
            toolStripButtonInfo.Size = new Size(41, 41);
            toolStripButtonInfo.Text = "Info";
            // 
            // toolStripLabelWhatToDo
            // 
            toolStripLabelWhatToDo.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripLabelWhatToDo.Name = "toolStripLabelWhatToDo";
            toolStripLabelWhatToDo.Size = new Size(71, 41);
            toolStripLabelWhatToDo.Text = "What to do?";
            // 
            // tabControlMain
            // 
            tabControlMain.Dock = DockStyle.Fill;
            tabControlMain.Location = new Point(0, 68);
            tabControlMain.Name = "tabControlMain";
            tabControlMain.SelectedIndex = 0;
            tabControlMain.Size = new Size(902, 464);
            tabControlMain.TabIndex = 2;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(902, 532);
            Controls.Add(tabControlMain);
            Controls.Add(toolStrip);
            Controls.Add(menuStrip);
            MainMenuStrip = menuStrip;
            Name = "MainForm";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "MainForm";
            menuStrip.ResumeLayout(false);
            menuStrip.PerformLayout();
            toolStrip.ResumeLayout(false);
            toolStrip.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip menuStrip;
        private ToolStrip toolStrip;
        private ToolStripMenuItem fileToolStripMenuItem;
        private ToolStripMenuItem loadFilesToolStripMenuItem;
        private ToolStripMenuItem loadFoldersToolStripMenuItem;
        private ToolStripButton toolStripButtonLoadFiles;
        private ToolStripButton toolStripButtonLoadFolders;
        private ToolStripMenuItem settingsToolStripMenuItem;
        private TabControl tabControlMain;
        private ToolStripButton toolStripButtonStartOneShot;
        private ToolStripButton toolStripButtonSettings;
        private ToolStripButton toolStripButtonRTCorrelation;
        private ToolStripButton toolStripButtonInfo;
        private ToolStripLabel toolStripLabelWhatToDo;
    }
}