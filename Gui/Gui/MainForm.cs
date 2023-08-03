using Common;
using Newtonsoft.Json;
using ScottPlot;
using ScottPlot.Plottable;
using System.Globalization;
using System.IO;
using static Gui.MainFormStatic;
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
            Processing correlator = new();
            correlator.AddProcessByPlatform(PlatformID.Win32NT, "./lib/correlator.exe");
            correlator.AddProcessByPlatform(PlatformID.Unix, "./lib/correlator");

            int selectedIndex = tabControlMain.SelectedIndex;
            tabControlMain.RemoveTabPageAndTabControl(AnalysisWork.Polyfit);
            tabControlMain.RemoveTabPageAndTabControl(AnalysisWork.FFT);
            tabControlMain.RemoveTabPageAndTabControl(AnalysisWork.FFTPeaks);
            tabControlMain.RemoveTabPageAndTabControl(AnalysisWork.FFTPeaksMigration);

            if (SettingsControl.Get().ComputePolyFit)
                correlator.AddArgument("--polyfit");

            if (SettingsControl.Get().ComputeFFT)
                correlator.AddArgument("--fft");

            if (SettingsControl.Get().ComputeFFTPeaks)
                correlator.AddArgument("--fftp");

            if (SettingsControl.Get().ComputeFFTPeaksMigration)
                correlator.AddArgument("--fftpm");

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
                    plot.Plot.AddScatter(Dataset[selectedTab].Select(x => x[0]).ToArray(), Dataset[selectedTab].Select(x => x[columnIndex]).ToArray(), GiveAGoodColor());
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
                        ReleaseAGoodColor();
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
                        ReleaseAGoodColor(((ScatterPlot)(plot.Plot.GetPlottables()[plottablesIndex])).Color);
                        plot.Plot.RemoveAt(plottablesIndex);
                        button.Value = "Add";
                    }
                    else
                    {
                        plot.Plot.AddScatter(Dataset[selectedTab].Select(x => x[0]).ToArray(), Dataset[selectedTab].Select(x => x[columnIndex]).ToArray(), GiveAGoodColor());
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
            ofd.InitialDirectory = "./";
            DialogResult dr = ofd.ShowDialog();
            if (dr == DialogResult.OK && ofd.FileNames != null)
                LoadDataset(ofd.FileNames);
        }

        private void LoadFolders()
        {
            FolderBrowserDialog fbd = new();
            fbd.InitialDirectory = "./";
            DialogResult dr = fbd.ShowDialog();
            if (dr == DialogResult.OK && !string.IsNullOrEmpty(fbd.SelectedPath))
                LoadDataset(Directory.EnumerateFiles(fbd.SelectedPath, "*.csv", SearchOption.AllDirectories).ToArray());
        }

        private void LoadDataset(string[] files)
        {
            Dataset.Clear();
            tabControlMain.Controls.Clear();
            SettingsControl.Get().InputFiles = new();

            TabPage tabPageDataset = new();
            ProgrammaticCreatedTabControlDataset = new();
            tabControlMain.AddTabPageAndTabControl(ref tabPageDataset, "Dataset", ref ProgrammaticCreatedTabControlDataset);

            for (int i = 0; i < files.Length; i++)
            {
                //read csv file
                CSVReader<double> csv = new(files[i], true);
                if (csv.Parsable)
                    Dataset.Add(csv.TData);
                else if (MessageBox.Show("The content of the dataset in " + files[i] + " is not parsable into double. Continue?",
                            "Correlator", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                    continue;

                SettingsControl.Get().InputFiles?.Add(files[i]);

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
                int maxColsNumber = csv.Data.Select(x => x.Count).Max();
                for (int column = 0; column < maxColsNumber; column++)
                    dataGridViewData.Columns.Add(csv.Title[column], csv.Title[column]);

                //add rows
                int numberOfLinesToShowInDataset = Convert.ToInt32(SettingsControl.Get().NumberOfLinesToShowInDataset?.Item1);
                for (int row = 0; row < numberOfLinesToShowInDataset && row < csv.TData.Count; row++)
                    dataGridViewData.AddRow<DataGridViewTextBoxCell>(csv.TData[row].Cast<object>().ToList(), true);

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
                if (csv.Parsable)
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
                string[] files = obj.output.ToObject<string[]>();
                files = files.Select(x => Path.Combine(SettingsControl.Get().OutputFolder, work, x)).ToArray();

                TabPage tabPageResults = new();
                TabControl tabControl = new();
                tabControlMain.AddTabPageAndTabControl(ref tabPageResults, work, ref ProgrammaticCreatedTabControlDataset);

                for (int i = 0; i < files.Length; i++)
                {
                    //read csv file
                    CSVReader<string> csv = new(files[i], true);
                    //if (csv.Parsable)
                    //    Dataset.Add(csv.TData);
                    //else if (MessageBox.Show("The content of the dataset in " + files[i] + " is not parsable into double. Continue?",
                    //            "Correlator", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                    //    continue;

                    //SettingsControl.Get().InputFiles?.Add(files[i]);

                    //create the tab page
                    TabPage tabPage = new();
                    ProgrammaticCreatedTabControlDataset.Controls.Add(tabPage);
                    tabPage.Text = files[i].Last(20, true);

                    //add a SplitContainer to the tab page
                    //SplitContainer splitContainer = new();
                    //ProgrammaticCreatedSplitContainers.Add(splitContainer);
                    //tabPage.Controls.Add(splitContainer);
                    //splitContainer.Orientation = Orientation.Horizontal;
                    //splitContainer.Dock = DockStyle.Fill;
                    //splitContainer.IsSplitterFixed = true;

                    //in the lower panel (Panel2) of the SplitContainer add the datagridview with data
                    DataGridView dataGridViewData = new();
                    //splitContainer.Panel2.Controls.Add(dataGridViewData);
                    tabPage.Controls.Add(dataGridViewData); //this is the alternative of the previous line (no splitContainer)
                    dataGridViewData.Dock = DockStyle.Fill;
                    dataGridViewData.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                    dataGridViewData.AllowUserToAddRows = false;
                    dataGridViewData.AllowUserToDeleteRows = false;
                    dataGridViewData.AllowUserToOrderColumns = false;

                    //add columns
                    int maxColsNumber = csv.Data.Select(x => x.Count).Max();
                    for (int column = 0; column < maxColsNumber; column++)
                        dataGridViewData.Columns.Add(csv.Title[column], csv.Title[column]);

                    //add rows
                    int numberOfLinesToShowInDataset = Convert.ToInt32(SettingsControl.Get().NumberOfLinesToShowInDataset?.Item1);
                    for (int row = 0; row < numberOfLinesToShowInDataset && row < csv.TData.Count; row++)
                        dataGridViewData.AddRow<DataGridViewTextBoxCell>(csv.TData[row].Cast<object>().ToList(), true);

                    ////in the upper panel (Panel1) of the SplitContainer add the datagridview with plottablesIndex manager
                    //DataGridView dataGridViewColumnManager = new();
                    //ProgrammaticCreatedDataGridViewColumnClick.Add(dataGridViewColumnManager);
                    //splitContainer.Panel1.Controls.Add(dataGridViewColumnManager);
                    //dataGridViewColumnManager.ColumnHeadersVisible = false;
                    //dataGridViewColumnManager.Dock = DockStyle.Fill;
                    //dataGridViewColumnManager.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
                    //dataGridViewColumnManager.AllowUserToAddRows = false;
                    //dataGridViewColumnManager.AllowUserToDeleteRows = false;
                    //dataGridViewColumnManager.AllowUserToOrderColumns = false;
                    //dataGridViewColumnManager.AllowUserToResizeColumns = false;
                    //dataGridViewColumnManager.AllowUserToResizeRows = false;
                    //dataGridViewColumnManager.RowsDefaultCellStyle.SelectionBackColor = Color.Transparent;

                    ////add columns
                    //for (int column = 0; column < maxColsNumber; column++)
                    //    dataGridViewColumnManager.Columns.Add(new DataGridViewColumn());

                    ////add row with checkboxes
                    //List<object> listOfCheckboxes = Enumerable.Repeat(true, SettingsControl.Get().DomainSize).Cast<object>().ToList();
                    //listOfCheckboxes.AddRange(Enumerable.Repeat(false, maxColsNumber - SettingsControl.Get().DomainSize).Cast<object>());
                    //dataGridViewColumnManager.AddRow<DataGridViewCheckBoxCell>(listOfCheckboxes, false);

                    ////add row with buttons
                    //List<object> listOfButtonValues = Enumerable.Repeat(string.Empty, SettingsControl.Get().DomainSize).Cast<object>().ToList();
                    //listOfButtonValues.AddRange(Enumerable.Repeat("Add", maxColsNumber - SettingsControl.Get().DomainSize).Cast<object>());
                    //List<bool> listOfButtonReadonly = Enumerable.Repeat(true, SettingsControl.Get().DomainSize).ToList();
                    //listOfButtonReadonly.AddRange(Enumerable.Repeat(false, maxColsNumber - SettingsControl.Get().DomainSize));
                    //dataGridViewColumnManager.AddRow<DataGridViewButtonCell>(listOfButtonValues, listOfButtonReadonly);
                    //if (csv.Parsable)
                    //    dataGridViewColumnManager.CellContentClick += DataGridViewColumnManager_CellContentClick;

                    //splitContainer.SplitterDistance = dataGridViewColumnManager.RowTemplate.Height * dataGridViewColumnManager.Rows.Count;
                }
            }
        }

        #endregion PRIVATE METHODS
    }
}