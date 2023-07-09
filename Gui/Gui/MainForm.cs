//icon from https://icon-library.com/

using ScottPlot;
using System.Globalization;
using System.Reflection;
using Orientation = System.Windows.Forms.Orientation;

namespace Gui
{
    public partial class MainForm : Form
    {
        private readonly List<SplitContainer> DynamicCreatedSplitContainers = new();
        private readonly List<DataGridView> DynamicCreatedDataGridViewColumnClick = new();
        private readonly List<List<List<double>>> DataSet = new();

        public MainForm()
        {
            InitializeComponent();
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
            DynamicCreatedSplitContainers.ForEach(x => x.SplitterDistance = DynamicCreatedDataGridViewColumnClick[0].RowTemplate.Height * DynamicCreatedDataGridViewColumnClick[0].Rows.Count);
        }

        private void ToolStripButtonStartOneShot_Click(object sender, EventArgs e)
        {

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
            ofd.InitialDirectory = "./";
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK && ofd.FileNames != null)
                LoadDataset(ofd.FileNames);
        }

        private void ImportFolders()
        {
            FolderBrowserDialog fbd = new();
            fbd.ShowHiddenFiles = true;
            fbd.InitialDirectory = "./";
            DialogResult dr = fbd.ShowDialog();
            if (dr == DialogResult.OK && !string.IsNullOrEmpty(fbd.SelectedPath))
                LoadDataset(Directory.GetFiles(fbd.SelectedPath));
        }

        private void LoadDataset(string[] files)
        {
            DataSet.Clear();
            tabControlDataset.Controls.Clear();
            for (int i = 0; i < files.Length; i++)
            {
                //read csv file
                List<List<string>> values = ReadCSV(files[i]);
                int maxColsNumber = values.Select(x => x.Count).Max();

                //check if there are some parsable values
                bool parsable = true;
                bool maybeTitle = false;
                for (int row = 0; row < Settings.Get().NumberOfLinesToShowInDataset && (parsable || maybeTitle); row++)
                {
                    parsable &= values[row].TrueForAll(x => double.TryParse(x, out double tmp));
                    if (!parsable)
                    {
                        maybeTitle = row == 0;
                        if (maybeTitle)
                            parsable = true;
                    }
                }

                if (!parsable)
                    if (MessageBox.Show("The content of the dataset in " + files[i] + " is not parsable into numbers. Continue?",
                        "Correlator", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                        continue;

                List<string> titles = Enumerable.Range(0, maxColsNumber).Select(x => x.ToString()).ToList();
                if (parsable && maybeTitle)
                {
                    titles = values[0];
                    values.RemoveAt(0);
                }

                //create the dataset
                if (parsable)
                    DataSet.Add(values.Select(x => x.Select(y => double.Parse(y.Replace(".", CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator.ToString()))).ToList()).ToList());

                //create the tab page
                TabPage tabPage = new();
                tabControlDataset.Controls.Add(tabPage);
                tabPage.Text = files[i].Last(20, true);

                //add a SplitContainer to the tab page
                SplitContainer splitContainer = new();
                DynamicCreatedSplitContainers.Add(splitContainer);
                tabPage.Controls.Add(splitContainer);
                splitContainer.Orientation = Orientation.Horizontal;
                splitContainer.Dock = DockStyle.Fill;
                splitContainer.IsSplitterFixed = true;

                //in the lower panel (Panel2) of the SplitContainer add the datagridview with data
                DataGridView dataGridViewData = new();
                splitContainer.Panel2.Controls.Add(dataGridViewData);
                dataGridViewData.Dock = DockStyle.Fill;
                dataGridViewData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridViewData.AllowUserToAddRows = false;
                dataGridViewData.AllowUserToDeleteRows = false;
                dataGridViewData.AllowUserToOrderColumns = false;

                //add columns
                for (int column = 0; column < maxColsNumber; column++)
                    dataGridViewData.Columns.Add(titles[column], titles[column]);

                //add rows
                for (int row = 0; row < Settings.Get().NumberOfLinesToShowInDataset; row++)
                    dataGridViewData.AddRow<DataGridViewTextBoxCell>(values[row].Cast<object>().ToList(), true);

                //in the upper panel (Panel1) of the SplitContainer add the datagridview with column manager
                DataGridView dataGridViewColumnManager = new();
                DynamicCreatedDataGridViewColumnClick.Add(dataGridViewColumnManager);
                splitContainer.Panel1.Controls.Add(dataGridViewColumnManager);
                dataGridViewColumnManager.ColumnHeadersVisible = false;
                dataGridViewColumnManager.Dock = DockStyle.Fill;
                dataGridViewColumnManager.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                dataGridViewColumnManager.AllowUserToAddRows = false;
                dataGridViewColumnManager.AllowUserToDeleteRows = false;
                dataGridViewColumnManager.AllowUserToOrderColumns = false;
                dataGridViewColumnManager.AllowUserToResizeColumns = false;
                dataGridViewColumnManager.AllowUserToResizeRows = false;
                dataGridViewColumnManager.RowsDefaultCellStyle.SelectionBackColor = Color.Transparent;

                //add columns
                for (int column = 0; column < maxColsNumber; column++)
                    dataGridViewColumnManager.Columns.Add(new DataGridViewColumn());

                //add row with checkboxes
                List<object> listOfCheckboxes = Enumerable.Repeat(true, Settings.Get().DomainSize).Cast<object>().ToList();
                listOfCheckboxes.AddRange(Enumerable.Repeat(false, maxColsNumber - Settings.Get().DomainSize).Cast<object>());
                dataGridViewColumnManager.AddRow<DataGridViewCheckBoxCell>(listOfCheckboxes, false);

                dataGridViewColumnManager.CellPainting += (object? sender, DataGridViewCellPaintingEventArgs e) =>
                {
                    if (e.RowIndex == 1)
                        if (e.ColumnIndex >= Settings.Get().DomainSize)
                        {
                            e.Paint(e.CellBounds, DataGridViewPaintParts.All);

                            int w = (int)(dataGridViewColumnManager.RowTemplate.Height * 0.8); // Properties.Resources.stop_button_icon_19.Width;
                            int h = (int)(dataGridViewColumnManager.RowTemplate.Height * 0.8); // Properties.Resources.stop_button_icon_19.Height;
                            int x = e.CellBounds.Left + (e.CellBounds.Width - w) / 2;
                            int y = e.CellBounds.Top + (e.CellBounds.Height - h) / 2;

                            e.Graphics.DrawImage(Properties.Resources.plot_icon_7, new Rectangle(x, y, w, h));
                            e.Handled = true;
                        }
                };

                //add row with buttons
                List<object> listOfButtonValues = Enumerable.Repeat(string.Empty, Settings.Get().DomainSize).Cast<object>().ToList();
                listOfButtonValues.AddRange(Enumerable.Range(0, maxColsNumber - Settings.Get().DomainSize).Cast<object>());
                List<bool> listOfButtonReadonly = Enumerable.Repeat(true, Settings.Get().DomainSize).ToList();
                listOfButtonReadonly.AddRange(Enumerable.Repeat(false, maxColsNumber - Settings.Get().DomainSize));
                dataGridViewColumnManager.AddRow<DataGridViewButtonCell>(listOfButtonValues, listOfButtonReadonly);
                if (parsable)
                    dataGridViewColumnManager.CellContentClick += (object? sender, DataGridViewCellEventArgs e) =>
                    {
                        if (sender == null)
                            return;

                        DataGridView senderGrid = (DataGridView)sender;
                        int rowIndex = e.RowIndex;
                        int columnIndex = e.ColumnIndex;
                        if (senderGrid.Rows[rowIndex].Cells[columnIndex] is DataGridViewButtonCell && columnIndex >= Settings.Get().DomainSize)
                        {
                            FormsPlot plot = new FormsPlot() { Dock = DockStyle.Fill };
                            plot.Plot.AddScatter(DataSet[0].Select(x => x[0]).ToArray(), DataSet[0].Select(x => x[1]).ToArray());
                            plot.Plot.Title(titles[columnIndex]);
                            plot.Refresh();
                            Form form = new Form();
                            form.Controls.Add(plot);
                            form.StartPosition = FormStartPosition.CenterScreen;
                            form.Size = new Size(800, 500);
                            form.ShowDialog();
                        }
                    };

                splitContainer.SplitterDistance = dataGridViewColumnManager.RowTemplate.Height * dataGridViewColumnManager.Rows.Count;
            }
        }

        private void DataGridViewColumnManager_CellFormatting(object? sender, DataGridViewCellFormattingEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void ShowSettingsForm()
        {
            Form form = new();
            form.Controls.Add(new SettingsControl(this));
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Size = new Size(800, 500);
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