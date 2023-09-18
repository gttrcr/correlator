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
            toolStrip = new ToolStrip();
            toolStripButtonLoadProcess = new ToolStripButton();
            toolStripButtonLoadFolder = new ToolStripButton();
            toolStripButtonLoadFiles = new ToolStripButton();
            toolStripButtonStart = new ToolStripButton();
            toolStripButtonOutputFolder = new ToolStripButton();
            toolStripButtonCancel = new ToolStripButton();
            splitContainer = new SplitContainer();
            tabControl = new TabControl();
            tabPagePolyfit = new TabPage();
            groupBoxPolyfit = new GroupBox();
            checkBoxPolyfitEnable = new CheckBox();
            tabPageFFT = new TabPage();
            groupBoxFFT = new GroupBox();
            checkBoxFFTEnable = new CheckBox();
            tabPageFFTPeaks = new TabPage();
            groupBoxFFTPeaks = new GroupBox();
            dataGridView1 = new DataGridView();
            textBox1 = new TextBox();
            checkBoxFFTPeaksEnable = new CheckBox();
            label4 = new Label();
            textBoxOutputFolder = new TextBox();
            label3 = new Label();
            textBoxLoadedProcess = new TextBox();
            richTextBoxLoadedFiles = new RichTextBox();
            label2 = new Label();
            label1 = new Label();
            textBoxLoadedFolder = new TextBox();
            toolStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer).BeginInit();
            splitContainer.Panel1.SuspendLayout();
            splitContainer.Panel2.SuspendLayout();
            splitContainer.SuspendLayout();
            tabControl.SuspendLayout();
            tabPagePolyfit.SuspendLayout();
            tabPageFFT.SuspendLayout();
            tabPageFFTPeaks.SuspendLayout();
            groupBoxFFTPeaks.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // toolStrip
            // 
            toolStrip.ImageScalingSize = new Size(50, 50);
            toolStrip.Items.AddRange(new ToolStripItem[] { toolStripButtonLoadProcess, toolStripButtonLoadFolder, toolStripButtonLoadFiles, toolStripButtonStart, toolStripButtonOutputFolder, toolStripButtonCancel });
            toolStrip.Location = new Point(0, 0);
            toolStrip.Name = "toolStrip";
            toolStrip.Size = new Size(1118, 59);
            toolStrip.TabIndex = 0;
            toolStrip.Text = "toolStrip";
            // 
            // toolStripButtonLoadProcess
            // 
            toolStripButtonLoadProcess.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonLoadProcess.Image = Properties.Resources.deployed_code_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonLoadProcess.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoadProcess.Name = "toolStripButtonLoadProcess";
            toolStripButtonLoadProcess.Size = new Size(54, 54);
            toolStripButtonLoadProcess.Text = "Load process";
            toolStripButtonLoadProcess.Click += ToolStripButtonLoadProcess_Click;
            // 
            // toolStripButtonLoadFolder
            // 
            toolStripButtonLoadFolder.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonLoadFolder.Image = Properties.Resources.create_new_folder_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonLoadFolder.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoadFolder.Name = "toolStripButtonLoadFolder";
            toolStripButtonLoadFolder.Size = new Size(54, 54);
            toolStripButtonLoadFolder.Text = "Load folder";
            toolStripButtonLoadFolder.Click += ToolStripButtonLoadFolder_Click;
            // 
            // toolStripButtonLoadFiles
            // 
            toolStripButtonLoadFiles.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonLoadFiles.Image = Properties.Resources.note_add_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonLoadFiles.ImageTransparentColor = Color.Magenta;
            toolStripButtonLoadFiles.Name = "toolStripButtonLoadFiles";
            toolStripButtonLoadFiles.Size = new Size(54, 54);
            toolStripButtonLoadFiles.Text = "Load files";
            toolStripButtonLoadFiles.Click += ToolStripButtonLoadFiles_Click;
            // 
            // toolStripButtonStart
            // 
            toolStripButtonStart.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonStart.Image = Properties.Resources.start_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonStart.ImageTransparentColor = Color.Magenta;
            toolStripButtonStart.Name = "toolStripButtonStart";
            toolStripButtonStart.Size = new Size(54, 54);
            toolStripButtonStart.Text = "Start";
            toolStripButtonStart.Click += ToolStripButtonStart_Click;
            // 
            // toolStripButtonOutputFolder
            // 
            toolStripButtonOutputFolder.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonOutputFolder.Image = Properties.Resources.output_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonOutputFolder.ImageTransparentColor = Color.Magenta;
            toolStripButtonOutputFolder.Name = "toolStripButtonOutputFolder";
            toolStripButtonOutputFolder.Size = new Size(54, 54);
            toolStripButtonOutputFolder.Text = "Set output folder";
            // 
            // toolStripButtonCancel
            // 
            toolStripButtonCancel.DisplayStyle = ToolStripItemDisplayStyle.Image;
            toolStripButtonCancel.Image = Properties.Resources.cancel_FILL0_wght400_GRAD0_opsz24;
            toolStripButtonCancel.ImageTransparentColor = Color.Magenta;
            toolStripButtonCancel.Name = "toolStripButtonCancel";
            toolStripButtonCancel.Size = new Size(54, 54);
            toolStripButtonCancel.Text = "Cancel";
            toolStripButtonCancel.Click += ToolStripButtonCancel_Click;
            // 
            // splitContainer
            // 
            splitContainer.BorderStyle = BorderStyle.Fixed3D;
            splitContainer.Dock = DockStyle.Fill;
            splitContainer.Location = new Point(0, 59);
            splitContainer.Name = "splitContainer";
            splitContainer.Orientation = Orientation.Horizontal;
            // 
            // splitContainer.Panel1
            // 
            splitContainer.Panel1.Controls.Add(tabControl);
            // 
            // splitContainer.Panel2
            // 
            splitContainer.Panel2.Controls.Add(label4);
            splitContainer.Panel2.Controls.Add(textBoxOutputFolder);
            splitContainer.Panel2.Controls.Add(label3);
            splitContainer.Panel2.Controls.Add(textBoxLoadedProcess);
            splitContainer.Panel2.Controls.Add(richTextBoxLoadedFiles);
            splitContainer.Panel2.Controls.Add(label2);
            splitContainer.Panel2.Controls.Add(label1);
            splitContainer.Panel2.Controls.Add(textBoxLoadedFolder);
            splitContainer.Size = new Size(1118, 1240);
            splitContainer.SplitterDistance = 568;
            splitContainer.TabIndex = 1;
            // 
            // tabControl
            // 
            tabControl.Controls.Add(tabPagePolyfit);
            tabControl.Controls.Add(tabPageFFT);
            tabControl.Controls.Add(tabPageFFTPeaks);
            tabControl.Dock = DockStyle.Fill;
            tabControl.Location = new Point(0, 0);
            tabControl.Name = "tabControl";
            tabControl.SelectedIndex = 0;
            tabControl.Size = new Size(1114, 564);
            tabControl.TabIndex = 0;
            // 
            // tabPagePolyfit
            // 
            tabPagePolyfit.Controls.Add(groupBoxPolyfit);
            tabPagePolyfit.Controls.Add(checkBoxPolyfitEnable);
            tabPagePolyfit.Location = new Point(4, 34);
            tabPagePolyfit.Name = "tabPagePolyfit";
            tabPagePolyfit.Padding = new Padding(3);
            tabPagePolyfit.Size = new Size(1106, 526);
            tabPagePolyfit.TabIndex = 0;
            tabPagePolyfit.Text = "Polyfit";
            tabPagePolyfit.UseVisualStyleBackColor = true;
            // 
            // groupBoxPolyfit
            // 
            groupBoxPolyfit.Dock = DockStyle.Fill;
            groupBoxPolyfit.Location = new Point(3, 32);
            groupBoxPolyfit.Name = "groupBoxPolyfit";
            groupBoxPolyfit.Size = new Size(1100, 491);
            groupBoxPolyfit.TabIndex = 10;
            groupBoxPolyfit.TabStop = false;
            // 
            // checkBoxPolyfitEnable
            // 
            checkBoxPolyfitEnable.AutoSize = true;
            checkBoxPolyfitEnable.Checked = true;
            checkBoxPolyfitEnable.CheckState = CheckState.Checked;
            checkBoxPolyfitEnable.Dock = DockStyle.Top;
            checkBoxPolyfitEnable.Location = new Point(3, 3);
            checkBoxPolyfitEnable.Name = "checkBoxPolyfitEnable";
            checkBoxPolyfitEnable.Size = new Size(1100, 29);
            checkBoxPolyfitEnable.TabIndex = 9;
            checkBoxPolyfitEnable.Text = "Enable";
            checkBoxPolyfitEnable.UseVisualStyleBackColor = true;
            // 
            // tabPageFFT
            // 
            tabPageFFT.Controls.Add(groupBoxFFT);
            tabPageFFT.Controls.Add(checkBoxFFTEnable);
            tabPageFFT.Location = new Point(4, 34);
            tabPageFFT.Name = "tabPageFFT";
            tabPageFFT.Padding = new Padding(3);
            tabPageFFT.Size = new Size(1106, 526);
            tabPageFFT.TabIndex = 1;
            tabPageFFT.Text = "FFT";
            tabPageFFT.UseVisualStyleBackColor = true;
            // 
            // groupBoxFFT
            // 
            groupBoxFFT.Dock = DockStyle.Fill;
            groupBoxFFT.Location = new Point(3, 32);
            groupBoxFFT.Name = "groupBoxFFT";
            groupBoxFFT.Size = new Size(1100, 491);
            groupBoxFFT.TabIndex = 12;
            groupBoxFFT.TabStop = false;
            // 
            // checkBoxFFTEnable
            // 
            checkBoxFFTEnable.AutoSize = true;
            checkBoxFFTEnable.Checked = true;
            checkBoxFFTEnable.CheckState = CheckState.Checked;
            checkBoxFFTEnable.Dock = DockStyle.Top;
            checkBoxFFTEnable.Location = new Point(3, 3);
            checkBoxFFTEnable.Name = "checkBoxFFTEnable";
            checkBoxFFTEnable.Size = new Size(1100, 29);
            checkBoxFFTEnable.TabIndex = 11;
            checkBoxFFTEnable.Text = "Enable";
            checkBoxFFTEnable.UseVisualStyleBackColor = true;
            // 
            // tabPageFFTPeaks
            // 
            tabPageFFTPeaks.Controls.Add(groupBoxFFTPeaks);
            tabPageFFTPeaks.Controls.Add(checkBoxFFTPeaksEnable);
            tabPageFFTPeaks.Location = new Point(4, 34);
            tabPageFFTPeaks.Name = "tabPageFFTPeaks";
            tabPageFFTPeaks.Padding = new Padding(3);
            tabPageFFTPeaks.Size = new Size(1106, 526);
            tabPageFFTPeaks.TabIndex = 2;
            tabPageFFTPeaks.Text = "FFT Peaks";
            tabPageFFTPeaks.UseVisualStyleBackColor = true;
            // 
            // groupBoxFFTPeaks
            // 
            groupBoxFFTPeaks.Controls.Add(dataGridView1);
            groupBoxFFTPeaks.Controls.Add(textBox1);
            groupBoxFFTPeaks.Dock = DockStyle.Fill;
            groupBoxFFTPeaks.Location = new Point(3, 32);
            groupBoxFFTPeaks.Name = "groupBoxFFTPeaks";
            groupBoxFFTPeaks.Size = new Size(1100, 491);
            groupBoxFFTPeaks.TabIndex = 12;
            groupBoxFFTPeaks.TabStop = false;
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(410, 105);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 62;
            dataGridView1.Size = new Size(360, 225);
            dataGridView1.TabIndex = 1;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(90, 69);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(150, 31);
            textBox1.TabIndex = 0;
            // 
            // checkBoxFFTPeaksEnable
            // 
            checkBoxFFTPeaksEnable.AutoSize = true;
            checkBoxFFTPeaksEnable.Checked = true;
            checkBoxFFTPeaksEnable.CheckState = CheckState.Checked;
            checkBoxFFTPeaksEnable.Dock = DockStyle.Top;
            checkBoxFFTPeaksEnable.Location = new Point(3, 3);
            checkBoxFFTPeaksEnable.Name = "checkBoxFFTPeaksEnable";
            checkBoxFFTPeaksEnable.Size = new Size(1100, 29);
            checkBoxFFTPeaksEnable.TabIndex = 11;
            checkBoxFFTPeaksEnable.Text = "Enable";
            checkBoxFFTPeaksEnable.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(10, 186);
            label4.Name = "label4";
            label4.Size = new Size(121, 25);
            label4.TabIndex = 8;
            label4.Text = "Output folder";
            // 
            // textBoxOutputFolder
            // 
            textBoxOutputFolder.Location = new Point(10, 214);
            textBoxOutputFolder.Name = "textBoxOutputFolder";
            textBoxOutputFolder.ReadOnly = true;
            textBoxOutputFolder.Size = new Size(864, 31);
            textBoxOutputFolder.TabIndex = 7;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(10, 22);
            label3.Name = "label3";
            label3.Size = new Size(137, 25);
            label3.TabIndex = 6;
            label3.Text = "Loaded process";
            // 
            // textBoxLoadedProcess
            // 
            textBoxLoadedProcess.Location = new Point(10, 50);
            textBoxLoadedProcess.Name = "textBoxLoadedProcess";
            textBoxLoadedProcess.ReadOnly = true;
            textBoxLoadedProcess.Size = new Size(864, 31);
            textBoxLoadedProcess.TabIndex = 5;
            // 
            // richTextBoxLoadedFiles
            // 
            richTextBoxLoadedFiles.Location = new Point(10, 296);
            richTextBoxLoadedFiles.Name = "richTextBoxLoadedFiles";
            richTextBoxLoadedFiles.ReadOnly = true;
            richTextBoxLoadedFiles.Size = new Size(864, 223);
            richTextBoxLoadedFiles.TabIndex = 4;
            richTextBoxLoadedFiles.Text = "";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(10, 268);
            label2.Name = "label2";
            label2.Size = new Size(107, 25);
            label2.TabIndex = 3;
            label2.Text = "Loaded files";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(10, 104);
            label1.Name = "label1";
            label1.Size = new Size(123, 25);
            label1.TabIndex = 1;
            label1.Text = "Loaded folder";
            // 
            // textBoxLoadedFolder
            // 
            textBoxLoadedFolder.Location = new Point(10, 132);
            textBoxLoadedFolder.Name = "textBoxLoadedFolder";
            textBoxLoadedFolder.ReadOnly = true;
            textBoxLoadedFolder.Size = new Size(864, 31);
            textBoxLoadedFolder.TabIndex = 0;
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1118, 1299);
            Controls.Add(splitContainer);
            Controls.Add(toolStrip);
            Margin = new Padding(4, 5, 4, 5);
            Name = "MainForm";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Correlator GUI";
            toolStrip.ResumeLayout(false);
            toolStrip.PerformLayout();
            splitContainer.Panel1.ResumeLayout(false);
            splitContainer.Panel2.ResumeLayout(false);
            splitContainer.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)splitContainer).EndInit();
            splitContainer.ResumeLayout(false);
            tabControl.ResumeLayout(false);
            tabPagePolyfit.ResumeLayout(false);
            tabPagePolyfit.PerformLayout();
            tabPageFFT.ResumeLayout(false);
            tabPageFFT.PerformLayout();
            tabPageFFTPeaks.ResumeLayout(false);
            tabPageFFTPeaks.PerformLayout();
            groupBoxFFTPeaks.ResumeLayout(false);
            groupBoxFFTPeaks.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ToolStrip toolStrip;
        private ToolStripButton toolStripButtonLoadFolder;
        private ToolStripButton toolStripButtonLoadFiles;
        private ToolStripButton toolStripButtonLoadProcess;
        private SplitContainer splitContainer;
        private TabControl tabControl;
        private TabPage tabPagePolyfit;
        private TabPage tabPageFFT;
        private TabPage tabPageFFTPeaks;
        private Label label3;
        private TextBox textBoxLoadedProcess;
        private RichTextBox richTextBoxLoadedFiles;
        private Label label2;
        private Label label1;
        private TextBox textBoxLoadedFolder;
        private ToolStripButton toolStripButtonCancel;
        private ToolStripButton toolStripButtonStart;
        private ToolStripButton toolStripButtonOutputFolder;
        private Label label4;
        private TextBox textBoxOutputFolder;
        private CheckBox checkBoxPolyfitEnable;
        private GroupBox groupBoxPolyfit;
        private GroupBox groupBoxFFT;
        private CheckBox checkBoxFFTEnable;
        private GroupBox groupBoxFFTPeaks;
        private CheckBox checkBoxFFTPeaksEnable;
        private TextBox textBox1;
        private DataGridView dataGridView1;
    }
}