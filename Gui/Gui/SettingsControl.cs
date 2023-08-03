using System.Text.Json;

namespace Gui
{
    public partial class SettingsControl : UserControl
    {
        public delegate void CloseDelegate();
        public CloseDelegate CloseCallback { get; set; }

        //private Control ParentControl { get; set; }
        private static Settings? Settings { get; set; }

        private static Settings LoadSettings()
        {
            Settings settings;
            if (File.Exists("settings.corr"))
                settings = JsonSerializer.Deserialize<Settings>(File.ReadAllText("settings.corr")) ?? Default();
            else
                settings = Default();

            return settings;
        }

        public SettingsControl(Control parentControl)
        {
            InitializeComponent();
            //ParentControl = parentControl;
            Dock = DockStyle.Fill;
            splitContainer1.SplitterDistance = splitContainer1.Height - 100;
            splitContainer2.SplitterDistance = splitContainer2.Width / 2;

            LoadSettingsTable();
        }

        public static Settings Get()
        {
            Settings ??= LoadSettings();

            return Settings;
        }

        private void InsertOrUpdateSetting<T>(string settingName, object? settings) where T : DataGridViewCell, new()
        {
            if (settings == null)
                return;

            object? cellValue = null;
            DataGridViewCell customCell = new T();
            if (settings is Tuple<string, List<string>> tupleSetting)
            {
                if (tupleSetting != null && !tupleSetting.Item2.Contains(tupleSetting.Item1))
                    throw new Exception("Setting " + tupleSetting.Item1 + " is not contained in settings {" + string.Join(", ", tupleSetting.Item2) + "}");

                if (typeof(T) == typeof(DataGridViewComboBoxCell))
                    ((DataGridViewComboBoxCell)customCell).DataSource = tupleSetting?.Item2;
                cellValue = tupleSetting?.Item1;
            }
            else if (settings is bool boolSetting)
                cellValue = boolSetting;
            else if (settings is int intSetting)
                cellValue = intSetting;
            else if (settings is List<string> listSetting)
                cellValue = string.Join(", ", listSetting);
            else if (settings is string stringSetting)
                cellValue = stringSetting;

            DataGridViewRow? row = dataGridViewSettings.Rows.Cast<DataGridViewRow>().FirstOrDefault(x => x.Cells[0].Value.Equals(settingName));
            DataGridViewCell? cell = row?.Cells[1];
            if (cell != null)
                cell.Value = cellValue;
            else
            {
                customCell.Value = cellValue;
                customCell.Style.SelectionBackColor = Color.Transparent;
                DataGridViewTextBoxCell settingNameCell = new();
                settingNameCell.Value = settingName;
                DataGridViewRow newRow = new();
                newRow.Cells.Add(settingNameCell);
                newRow.Cells.Add(customCell);
                settingNameCell.ReadOnly = true;
                //customCell.ReadOnly = readOnly;
                dataGridViewSettings.Rows.Add(newRow);
            }
        }

        private void LoadSettingsTable()
        {
            InsertOrUpdateSetting<DataGridViewComboBoxCell>("Theme", Get().Theme);
            InsertOrUpdateSetting<DataGridViewComboBoxCell>("Number of lines to show in dataset", Get().NumberOfLinesToShowInDataset);
            InsertOrUpdateSetting<DataGridViewTextBoxCell>("Number of domain columns", Get().DomainSize);
            InsertOrUpdateSetting<DataGridViewCheckBoxCell>("Compute Polynomial fit", Get().ComputePolyFit);
            InsertOrUpdateSetting<DataGridViewCheckBoxCell>("Compute FFT", Get().ComputeFFT);
            InsertOrUpdateSetting<DataGridViewCheckBoxCell>("Compute FFT peaks", Get().ComputeFFTPeaks);
            InsertOrUpdateSetting<DataGridViewCheckBoxCell>("Compute FFT peaks migration", Get().ComputeFFTPeaksMigration);
            InsertOrUpdateSetting<DataGridViewCheckBoxCell>("Compute FFT peaks migration", Get().ComputeFFTPeaksMigration);
            InsertOrUpdateSetting<DataGridViewTextBoxCell>("Polyfit max degree", Get().PolyfitMaxDegree);
            InsertOrUpdateSetting<DataGridViewTextBoxCell>("Input", Get().InputFiles);
            InsertOrUpdateSetting<DataGridViewTextBoxCell>("Output", Get().OutputFolder);

        }

        private void ButtonSaveSettings_Click(object sender, EventArgs e)
        {
            int rowIndex = 0;
            Get().Theme = new Tuple<string, List<string>>(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value.ToString() ?? string.Empty, Get().Theme.Item2);
            Get().NumberOfLinesToShowInDataset = new Tuple<string, List<string>>(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value.ToString() ?? string.Empty, Get().NumberOfLinesToShowInDataset.Item2);
            Get().DomainSize = Convert.ToInt32(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value.ToString());
            Get().ComputePolyFit = (bool)(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value);
            Get().ComputeFFT = (bool)(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value);
            Get().ComputeFFTPeaks = (bool)(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value);
            Get().ComputeFFTPeaksMigration = (bool)(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value);
            Get().PolyfitMaxDegree = Convert.ToInt32(dataGridViewSettings.Rows[rowIndex++].Cells[1].Value);

            File.WriteAllText("settings.corr", JsonSerializer.Serialize(Settings));
            CloseCallback?.Invoke();
        }

        private void ButtonRestoreDefault_Click(object sender, EventArgs e)
        {
            Settings = Default();
            LoadSettingsTable();
        }

        private static Settings Default()
        {
            return new()
            {
                Theme = new Tuple<string, List<string>>("Light", new List<string>() { "Light", "Dark" }),
                NumberOfLinesToShowInDataset = new Tuple<string, List<string>>("100", new List<string>() { "10", "100", "1000", "10000" }),
                DomainSize = 1,
                ComputePolyFit = true,
                ComputeFFT = true,
                ComputeFFTPeaks = true,
                ComputeFFTPeaksMigration = true,
                PolyfitMaxDegree = 10,
                InputFiles = new List<string>() { "." },
                OutputFolder = "out_correlator"
            };
        }
    }

    public class Settings
    {
        public Tuple<string, List<string>>? Theme { get; set; }
        public Tuple<string, List<string>>? NumberOfLinesToShowInDataset { get; set; }
        public int DomainSize { get; set; }
        public bool ComputePolyFit { get; set; }
        public bool ComputeFFT { get; set; }
        public bool ComputeFFTPeaks { get; set; }
        public bool ComputeFFTPeaksMigration { get; set; }
        public int PolyfitMaxDegree { get; set; }
        public List<string>? InputFiles { get; set; }
        public string? OutputFolder { get; set; }
    }
}
