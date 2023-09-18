using Common;

namespace Gui
{
    public partial class MainForm : Form
    {
        Processing processing;

        public MainForm()
        {
            InitializeComponent();
            FormBorderStyle = FormBorderStyle.FixedSingle;
            MinimizeBox = false;
            MaximizeBox = false;
            splitContainer.SplitterDistance = splitContainer.Height / 2;
            textBoxLoadedProcess.Text = Directory.GetCurrentDirectory();
            textBoxLoadedFolder.Text = Directory.GetCurrentDirectory();
            textBoxOutputFolder.Text = Directory.GetCurrentDirectory() + "out_correlator";
            richTextBoxLoadedFiles.Lines = Directory.EnumerateFiles(textBoxLoadedProcess.Text, "*", SearchOption.AllDirectories).ToArray();
            processing = new();

            checkBoxPolyfitEnable.CheckStateChanged += delegate { groupBoxPolyfit.Enabled = checkBoxPolyfitEnable.Checked; };
        }

        private void ToolStripButtonLoadFiles_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new();
            ofd.Multiselect = true;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                processing.AddArgument("-i", string.Join(" ", ofd.FileNames));
                List<string> allLines = richTextBoxLoadedFiles.Lines.ToList();
                allLines.AddRange(ofd.FileNames);
                richTextBoxLoadedFiles.Lines = allLines.ToArray();
            }
        }

        private void ToolStripButtonLoadFolder_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new();
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                string[] files = Directory.GetFiles(fbd.SelectedPath, "*", SearchOption.AllDirectories);
                textBoxLoadedFolder.Text = fbd.SelectedPath;
                processing.AddArgument("-i", string.Join(" ", files));
                richTextBoxLoadedFiles.Lines = files;
            }
        }

        private void ToolStripButtonLoadProcess_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new();
            ofd.Multiselect = false;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                processing.AddProcessByPlatform(Environment.OSVersion.Platform, ofd.FileName);
                textBoxLoadedProcess.Text = ofd.FileName;
            }
        }

        private void ToolStripButtonCancel_Click(object sender, EventArgs e)
        {
            processing = new();
            textBoxLoadedProcess.Text = string.Empty;
            textBoxLoadedFolder.Text = string.Empty;
            richTextBoxLoadedFiles.Clear();
        }

        private void ToolStripButtonStart_Click(object sender, EventArgs e)
        {
            processing.Invoke();
        }
    }
}