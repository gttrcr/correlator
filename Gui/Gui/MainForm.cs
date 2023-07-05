//icon from https://icon-library.com/

namespace Gui
{
    public partial class MainForm : Form
    {
        private readonly List<SplitContainer> DynamicCreatedSplitContainers = new();
        private readonly List<DataGridView> DynamicCreatedDataGridViewColumnClick = new();

        public MainForm()
        {
            InitializeComponent();
            //tabPage3.Controls.Clear();
            //tabPage3.Controls.Add(new SettingsControl(this));
            SizeChanged += MainForm_SizeChanged;
        }

        #region PRIVATE HANDLERS

        private void ImportFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ImportFiles();
        }

        private void ImportFoldersToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ImportFolders();
        }

        private void ToolStripButtonImportFiles_Click(object sender, EventArgs e)
        {
            ImportFiles();
        }

        private void ToolStripButtonImportFolders_Click(object sender, EventArgs e)
        {
            ImportFolders();
        }

        private void SettingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ShowSettingsForm();
        }

        private void ToolStripButtonSettings_Click(object sender, EventArgs e)
        {
            ShowSettingsForm();
        }

        private void MainForm_SizeChanged(object? sender, EventArgs e)
        {
            DynamicCreatedSplitContainers.ForEach(x => x.SplitterDistance = DynamicCreatedDataGridViewColumnClick[0].RowTemplate.Height);
        }

        private void ToolStripButtonRTCorrelator_Click(object sender, EventArgs e)
        {
            toolStripButtonRTCorrelator.Image = Properties.Resources.stop_button_icon_19;
        }

        #endregion PRIVATE HANDLER

        #region PRIVATE METHODS

        private void ImportFiles()
        {
            OpenFileDialog ofd = new();
            ofd.Multiselect = true;
            ofd.ShowHiddenFiles = true;
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK && ofd.FileNames != null)
                LoadDataset(ofd.FileNames);
        }

        private void ImportFolders()
        {
            FolderBrowserDialog fbd = new();
            fbd.ShowHiddenFiles = true;
            DialogResult dr = fbd.ShowDialog();
            if (dr == DialogResult.OK && !string.IsNullOrEmpty(fbd.SelectedPath))
                LoadDataset(Directory.GetFiles(fbd.SelectedPath));
        }

        private void LoadDataset(string[] files)
        {
            tabControlDataset.Controls.Clear();
            for (int i = 0; i < files.Length; i++)
            {
                TabPage tabPage = new();
                tabControlDataset.Controls.Add(tabPage);
                tabPage.Text = files[i].Last(20, true);

                SplitContainer splitContainer = new();
                DynamicCreatedSplitContainers.Add(splitContainer);
                tabPage.Controls.Add(splitContainer);
                splitContainer.Orientation = Orientation.Horizontal;
                splitContainer.Dock = DockStyle.Fill;
                splitContainer.IsSplitterFixed = true;
                splitContainer.SplitterDistance = 25;

                DataGridView dataGridView = new();
                splitContainer.Panel2.Controls.Add(dataGridView);
                dataGridView.Dock = DockStyle.Fill;
                dataGridView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridView.AllowUserToAddRows = false;
                dataGridView.AllowUserToDeleteRows = false;
                dataGridView.AllowUserToOrderColumns = false;

                DataGridView dataGridViewColumnClick = new();
                DynamicCreatedDataGridViewColumnClick.Add(dataGridViewColumnClick);
                splitContainer.Panel1.Controls.Add(dataGridViewColumnClick);
                splitContainer.SplitterDistance = dataGridViewColumnClick.RowTemplate.Height;
                dataGridViewColumnClick.ColumnHeadersVisible = false;
                dataGridViewColumnClick.Dock = DockStyle.Fill;
                dataGridViewColumnClick.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridViewColumnClick.AllowUserToAddRows = false;
                dataGridViewColumnClick.AllowUserToDeleteRows = false;
                dataGridViewColumnClick.AllowUserToOrderColumns = false;
                dataGridViewColumnClick.AllowUserToResizeColumns = false;
                dataGridViewColumnClick.AllowUserToResizeRows = false;
                dataGridViewColumnClick.RowsDefaultCellStyle.SelectionBackColor = Color.Transparent;

                List<List<string>> values = ReadCSV(files[i]);
                int maxColsNumber = values.Select(x => x.Count).Max();
                for (int column = 0; column < maxColsNumber; column++)
                {
                    dataGridView.Columns.Add(column.ToString(), column.ToString());

                    DataGridViewCheckBoxColumn doWork = new();
                    dataGridViewColumnClick.Columns.Add(doWork);
                }

                dataGridViewColumnClick.AddRow<DataGridViewCheckBoxCell>(Enumerable.Repeat(false, maxColsNumber).Cast<object>(), false);
                for (int row = 0; row < Settings.Get().NumberOfLinesToShowInDataset; row++)
                    dataGridView.AddRow<DataGridViewTextBoxCell>(values[row].Cast<object>(), true);
            }
        }

        private void ShowSettingsForm()
        {
            Form form = new();
            form.Controls.Add(new SettingsControl(this));
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Size = new Size(800, 300);
            form.ShowDialog();
        }

        private static List<List<string>> ReadCSV(string file)
        {
            List<List<string>> ret = new();
            string[] lines = File.ReadAllLines(file);
            for (int i = 0; i < lines.Length; i++)
            {
                List<string> values = lines[i].Split(new string[] { ",", ";" }, StringSplitOptions.None).ToList();
                ret.Add(values);
            }

            return ret;
        }

        #endregion PRIVATE METHODS
    }
}