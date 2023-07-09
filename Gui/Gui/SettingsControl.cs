using System.Text.Json;

namespace Gui
{
    public partial class SettingsControl : UserControl
    {
        private Control ParentControl { get; set; }

        public SettingsControl(Control parentControl)
        {
            InitializeComponent();
            ParentControl = parentControl;
            Dock = DockStyle.Fill;
            splitContainer1.SplitterDistance = splitContainer1.Height - 100;
            splitContainer2.SplitterDistance = splitContainer2.Width / 2;

            AddSetting<DataGridViewComboBoxCell>("Theme", new string[] { "Light", "Dark" }, false, Settings.Get().Theme);
            AddSetting<DataGridViewComboBoxCell>("Number of lines to show in dataset", new string[] { "10", "100", "1000", "10000", "100000" }, false, Settings.Get().NumberOfLinesToShowInDataset.ToString());
            AddSetting<DataGridViewTextBoxCell>("Number of domain columns", null, false, Settings.Get().DomainSize);
            AddSetting<DataGridViewCheckBoxCell>("Compute Polynomial fit", null, false, Settings.Get().ComputePolyFit);
            AddSetting<DataGridViewCheckBoxCell>("Compute FFT", null, false, Settings.Get().ComputeFFT);
            AddSetting<DataGridViewCheckBoxCell>("Compute FFT peaks", null, false, Settings.Get().ComputeFFTPeaks);
            AddSetting<DataGridViewCheckBoxCell>("Compute FFT peaks migration", null, false, Settings.Get().ComputeFFTPeaksMigration);
        }

        private void AddSetting<T>(string settingName, IEnumerable<object>? settings, bool readOnly, object value) where T : DataGridViewCell, new()
        {
            if (settings != null && !settings.Contains(value))
                throw new Exception("Setting " + value + " is not contained in settings {" + string.Join(", ", settings) + "}");

            DataGridViewCell customCell = new T();
            if (typeof(T) == typeof(DataGridViewComboBoxCell))
                ((DataGridViewComboBoxCell)customCell).DataSource = settings;
            customCell.Value = value;
            customCell.Style.SelectionBackColor = Color.Transparent;
            DataGridViewCell cell = new DataGridViewTextBoxCell();
            cell.Value = settingName;
            DataGridViewRow row = new();
            row.Cells.Add(cell);
            row.Cells.Add(customCell);
            cell.ReadOnly = true;
            customCell.ReadOnly = readOnly;
            dataGridViewSettings.Rows.Add(row);
        }

        private void ButtonSaveSettings_Click(object sender, EventArgs e)
        {
            //List<Control> result = ParentControl.GetSelfAndChildrenRecursive().ToList();
            //List<Color> backColors = result.Select(x => x.BackColor).ToList();
            //backColors.AddRange(result.Where(x => x is DataGridView).Select(x => (DataGridView)x).Select(x => x.BackgroundColor));
            ////TODO add other Controls
            //backColors = backColors.Distinct().ToList();

            //List<Color> foreColors = result.Select(x => x.ForeColor).ToList();
            ////TODO add other Controls
            //foreColors = foreColors.Distinct().ToList();

            //result.ForEach(x => x.BackColor = Color.AliceBlue);
            //result.ForEach(x => x.ForeColor = Color.Red);
            //ParentControl.Refresh();
        }

        private void ButtonRestoreDefault_Click(object sender, EventArgs e)
        {

        }
    }

    public class Settings
    {
        private static Settings? _instance = null;

        public string Theme { get; private set; }
        public int NumberOfLinesToShowInDataset { get; private set; }
        public int DomainSize { get; private set; }
        public bool ComputePolyFit { get; private set; }
        public bool ComputeFFT { get; private set; }
        public bool ComputeFFTPeaks { get; private set; }
        public bool ComputeFFTPeaksMigration { get; private set; }

        private Settings()
        {
            if (File.Exists("settings.corr"))
            {
                string settings = File.ReadAllText("settings.corr");
                Settings? setts = JsonSerializer.Deserialize<Settings>(File.ReadAllText(settings));
                if (setts != null)
                {
                    Theme = setts.Theme;
                    NumberOfLinesToShowInDataset = setts.NumberOfLinesToShowInDataset;
                }
                else
                    Default();
            }
            else
                Default();
        }

        private void Default()
        {
            Theme = "Light";
            NumberOfLinesToShowInDataset = 100;
            DomainSize = 1;
            ComputePolyFit = true;
            ComputeFFT = true;
            ComputeFFTPeaks = true;
            ComputeFFTPeaksMigration = true;
        }

        public static Settings Get()
        {
            _instance ??= new Settings();
            return _instance;
        }
    }
}
