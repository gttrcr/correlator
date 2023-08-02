//icon from https://icon-library.com/

using Common;
using Newtonsoft.Json;
using ScottPlot;
using ScottPlot.Plottable;
using System.Globalization;
using System.Security.Cryptography;
using Orientation = System.Windows.Forms.Orientation;

namespace Gui
{
    public partial class MainForm : Form
    {
        private readonly List<SplitContainer> ProgrammaticCreatedSplitContainers = new();
        private readonly List<DataGridView> ProgrammaticCreatedDataGridViewColumnClick = new();
        private readonly List<List<List<double>>> Dataset = new();
        private TabControl ProgrammaticCreatedTabControlDataset = new();
        private Form? PlotForm = null;

        public MainForm()
        {
            InitializeComponent();
            SizeChanged += MainForm_SizeChanged;
            toolStripButtonRTCorrelation.Tag = false;
            toolStripLabelWhatToDo.Text = "Load a dataset or start real time correlation";
            toolStripButtonStartOneShot.Enabled = false;

            new Thread(new ThreadStart(() =>
            {
                while (true)
                {
                    Thread.Sleep(1000);
                    GC.Collect();
                }
            }))
            { IsBackground = true }.Start();
        }

        #region PRIVATE HANDLERS

        private void LoadFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LoadFiles();
        }

        private void LoadFoldersToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LoadFolders();
        }

        private void ToolStripButtonLoadFiles_Click(object sender, EventArgs e)
        {
            LoadFiles();
        }

        private void ToolStripButtonLoadFolders_Click(object sender, EventArgs e)
        {
            LoadFolders();
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
            ProgrammaticCreatedSplitContainers.ForEach(x => x.SplitterDistance = ProgrammaticCreatedDataGridViewColumnClick[0].RowTemplate.Height * ProgrammaticCreatedDataGridViewColumnClick[0].Rows.Count);
            Refresh();
        }

        private void ToolStripButtonStartOneShot_Click(object sender, EventArgs e)
        {
            Common.Processing correlator = new();
            correlator.AddProcessByPlatform(PlatformID.Win32NT, "./lib/correlator.exe");
            correlator.AddProcessByPlatform(PlatformID.Unix, "./lib/correlator");

            int selectedIndex = tabControlMain.SelectedIndex;
            tabControlMain.RemoveTabPageAndTabControl("Polyfit");
            tabControlMain.RemoveTabPageAndTabControl("FFT");
            tabControlMain.RemoveTabPageAndTabControl("FFT peaks");
            tabControlMain.RemoveTabPageAndTabControl("FFT peaks migration");

            if (SettingsControl.Get().ComputePolyFit)
            {
                TabPage tabPage = new();
                TabControl tabControl = new();
                tabControlMain.AddTabPageAndTabControl(ref tabPage, "Polyfit", ref tabControl);
                correlator.AddArgument("--polyfit");
            }

            if (SettingsControl.Get().ComputeFFT)
            {
                TabPage tabPage = new();
                TabControl tabControl = new();
                tabControlMain.AddTabPageAndTabControl(ref tabPage, "FFT", ref tabControl);
                correlator.AddArgument("--fft");
            }

            if (SettingsControl.Get().ComputeFFTPeaks)
            {
                TabPage tabPage = new();
                TabControl tabControl = new();
                tabControlMain.AddTabPageAndTabControl(ref tabPage, "FFT peaks", ref tabControl);
                correlator.AddArgument("--fftp");
            }

            if (SettingsControl.Get().ComputeFFTPeaksMigration)
            {
                TabPage tabPage = new();
                TabControl tabControl = new();
                tabControlMain.AddTabPageAndTabControl(ref tabPage, "FFT peaks migration", ref tabControl);
                correlator.AddArgument("--fftpm");
            }

            correlator.AddArgument("-f", SettingsControl.Get().PolyfitMaxDegree);
            correlator.AddArgument("-i", SettingsControl.Get().InputFiles);
            correlator.AddArgument("-o", SettingsControl.Get().OutputFolder);

            if (correlator.Invoke())
                RetrieveResults();

            tabControlMain.SelectedIndex = selectedIndex;
        }

        private void ToolStripButtonRTCorrelation_Click(object sender, EventArgs e)
        {
            bool correlate = !(bool)(((ToolStripButton)sender).Tag);
            ((ToolStripButton)sender).Tag = correlate;
            if (correlate)
                toolStripButtonRTCorrelation.Image = Properties.Resources.stop_button_icon_19;
            else
                toolStripButtonRTCorrelation.Image = Properties.Resources.icon_start_2;
        }

        private void DataGridViewColumnManager_CellContentClick(object? sender, DataGridViewCellEventArgs e)
        {
            if (sender == null)
                return;

            int rowIndex = e.RowIndex;
            int columnIndex = e.ColumnIndex;
            if (((DataGridView)sender).Rows[rowIndex].Cells[columnIndex] is DataGridViewButtonCell button && columnIndex >= SettingsControl.Get().DomainSize)
            {
                int selectedTab = ProgrammaticCreatedTabControlDataset.SelectedIndex;
                if (PlotForm == null || PlotForm.Controls == null || PlotForm.Controls.Count == 0)
                {
                    FormsPlot plot = new() { Dock = DockStyle.Fill };
                    plot.Plot.AddScatter(Dataset[selectedTab].Select(x => x[0]).ToArray(), Dataset[selectedTab].Select(x => x[columnIndex]).ToArray(), MainFormStatic.GiveAGoodColor());
                    //plot.Plot.Title(titles[columnIndex]);
                    button.Value = "Remove";
                    plot.Refresh();

                    PlotForm = new();
                    PlotForm.Controls.Add(plot);
                    PlotForm.StartPosition = FormStartPosition.CenterScreen;
                    PlotForm.Size = new Size(800, 500);
                    PlotForm.Show();
                    PlotForm.FormClosed += (object? s, FormClosedEventArgs ev) =>
                    {
                        List<SplitContainer> allDataGridViews = ProgrammaticCreatedTabControlDataset.TabPages.Cast<TabPage>().ToList()  //get all tab control dataset
                            .Select(x => x.Controls.Cast<Control>()).SelectMany(x => x) //get all controls
                            .Where(x => x is SplitContainer).Cast<SplitContainer>().ToList(); //get all SplitContainer
                        List<DataGridView> allPanel1DataGridView = allDataGridViews.Select(x => x.Panel1.Controls.Cast<Control>()).SelectMany(x => x) //get all controls in Panel1
                            .Where(x => x is DataGridView).Cast<DataGridView>().ToList(); //get all DataGridView in Panel1
                        allPanel1DataGridView.ForEach(x => x.Rows[1].Cells.Cast<DataGridViewButtonCell>().Where(x => x.Value.Equals("Remove")).ToList().ForEach(x => x.Value = "Add"));
                        MainFormStatic.ReleaseAGoodColor();
                    };
                }
                else
                {
                    FormsPlot plot = (FormsPlot)PlotForm.Controls.Cast<Control>().Last();
                    int plottablesIndex = 0;
                    bool found = false;
                    while (plottablesIndex < plot.Plot.GetPlottables().Length)
                    {
                        found = ((ScatterPlot)(plot.Plot.GetPlottables()[plottablesIndex])).Ys.SequenceEqual(Dataset[selectedTab].Select(x => x[columnIndex]));
                        if (found)
                            break;
                        plottablesIndex++;
                    }

                    if (found)
                    {
                        MainFormStatic.ReleaseAGoodColor(((ScatterPlot)(plot.Plot.GetPlottables()[plottablesIndex])).Color);
                        plot.Plot.RemoveAt(plottablesIndex);
                        button.Value = "Add";
                    }
                    else
                    {
                        plot.Plot.AddScatter(Dataset[selectedTab].Select(x => x[0]).ToArray(), Dataset[selectedTab].Select(x => x[columnIndex]).ToArray(), MainFormStatic.GiveAGoodColor());
                        button.Value = "Remove";
                    }

                    if (plot.Plot.GetPlottables().Length == 0)
                    {
                        PlotForm.Close();
                        PlotForm.Dispose();
                        PlotForm = null;
                    }
                    else
                        plot.Refresh();
                }
            }
        }

        #endregion PRIVATE HANDLER

        #region PRIVATE METHODS

        private void LoadFiles()
        {
            OpenFileDialog ofd = new();
            ofd.Multiselect = true;
            //ofd.ShowHiddenFiles = true;
            ofd.InitialDirectory = "./";
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK && ofd.FileNames != null)
                LoadDataset(ofd.FileNames);
        }

        private void LoadFolders()
        {
            FolderBrowserDialog fbd = new();
            //fbd.ShowHiddenFiles = true;
            fbd.InitialDirectory = "./";
            DialogResult dr = fbd.ShowDialog();
            if (dr == DialogResult.OK && !string.IsNullOrEmpty(fbd.SelectedPath))
                LoadDataset(Directory.GetFiles(fbd.SelectedPath));
        }

        private void LoadDataset(string[] files)
        {
            Dataset.Clear();
            tabControlMain.Controls.Clear();
            SettingsControl.Get().InputFiles = files.ToList();

            TabPage tabPageDataset = new();
            ProgrammaticCreatedTabControlDataset = new();
            tabControlMain.AddTabPageAndTabControl(ref tabPageDataset, "Dataset", ref ProgrammaticCreatedTabControlDataset);

            for (int i = 0; i < files.Length; i++)
            {
                //read csv file
                List<List<string>> values = MainFormStatic.ReadCSV(files[i]);
                int maxColsNumber = values.Select(x => x.Count).Max();

                //check if there are some parsable values
                bool parsable = true;
                bool maybeTitle = false;
                for (int row = 0; row < Convert.ToInt32(SettingsControl.Get().NumberOfLinesToShowInDataset?.Item1) && (parsable || maybeTitle); row++)
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
                    Dataset.Add(values.Select(x => x.Select(y => double.Parse(y.Replace(".", CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator.ToString()))).ToList()).ToList());

                //create the tab page
                TabPage tabPage = new();
                ProgrammaticCreatedTabControlDataset.Controls.Add(tabPage);
                tabPage.Text = files[i].Last(20, true);

                //add a SplitContainer to the tab page
                SplitContainer splitContainer = new();
                ProgrammaticCreatedSplitContainers.Add(splitContainer);
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
                for (int row = 0; row < Convert.ToInt32(SettingsControl.Get().NumberOfLinesToShowInDataset?.Item1); row++)
                    dataGridViewData.AddRow<DataGridViewTextBoxCell>(values[row].Cast<object>().ToList(), true);

                //in the upper panel (Panel1) of the SplitContainer add the datagridview with plottablesIndex manager
                DataGridView dataGridViewColumnManager = new();
                ProgrammaticCreatedDataGridViewColumnClick.Add(dataGridViewColumnManager);
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
                List<object> listOfCheckboxes = Enumerable.Repeat(true, SettingsControl.Get().DomainSize).Cast<object>().ToList();
                listOfCheckboxes.AddRange(Enumerable.Repeat(false, maxColsNumber - SettingsControl.Get().DomainSize).Cast<object>());
                dataGridViewColumnManager.AddRow<DataGridViewCheckBoxCell>(listOfCheckboxes, false);

                //add row with buttons
                List<object> listOfButtonValues = Enumerable.Repeat(string.Empty, SettingsControl.Get().DomainSize).Cast<object>().ToList();
                listOfButtonValues.AddRange(Enumerable.Repeat("Add", maxColsNumber - SettingsControl.Get().DomainSize).Cast<object>());
                List<bool> listOfButtonReadonly = Enumerable.Repeat(true, SettingsControl.Get().DomainSize).ToList();
                listOfButtonReadonly.AddRange(Enumerable.Repeat(false, maxColsNumber - SettingsControl.Get().DomainSize));
                dataGridViewColumnManager.AddRow<DataGridViewButtonCell>(listOfButtonValues, listOfButtonReadonly);
                if (parsable)
                    dataGridViewColumnManager.CellContentClick += DataGridViewColumnManager_CellContentClick;

                splitContainer.SplitterDistance = dataGridViewColumnManager.RowTemplate.Height * dataGridViewColumnManager.Rows.Count;
            }

            toolStripButtonStartOneShot.Enabled = true;
            toolStripLabelWhatToDo.Text = "Start processing one shot";
        }

        private void ShowSettingsForm()
        {
            Form form = new();
            form.Controls.Add(new SettingsControl(this) { CloseCallback = form.Close });
            form.StartPosition = FormStartPosition.CenterScreen;
            form.Size = new Size(800, 500);
            form.ShowDialog();
        }

        private void RetrieveResults()
        {
            string resultPath = Path.Combine(SettingsControl.Get().OutputFolder, "result.json");
            if (!File.Exists(resultPath))
                return;

            var resultObj = JsonConvert.DeserializeObject<dynamic>(File.ReadAllText(resultPath));
            foreach (var obj in resultObj.analysis)
            {
                string work = obj.work;
                List<string> outputs = obj.outputs.ToObject<List<string>>();
                outputs = outputs.Select(x => Path.Combine(SettingsControl.Get().OutputFolder, work, x)).ToList();
                CSVReader<string> csvContent = new CSVReader<string>(outputs[0], true);
                List<string> degrees = csvContent["degree"];
            }
        }

        #endregion PRIVATE METHODS
    }
}