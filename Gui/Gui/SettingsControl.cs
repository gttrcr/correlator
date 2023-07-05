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

            AddSetting("Number of lines to show in dataset", new string[] { "10", "100", "1000", "10000", "100000" }, false, Settings.Get().NumberOfLinesToShowInDataset.ToString());
            AddSetting("Theme", new string[] { "Light", "Dark" }, false, Settings.Get().Theme);
        }

        private void AddSetting(string settingName, string[] settings, bool readOnly, string value)
        {
            if (!settings.Contains(value))
                throw new Exception("Setting " + value + " is not contained in settings {" + string.Join(", ", settings) + "}");

            DataGridViewComboBoxCell comboBoxCell = new();
            comboBoxCell.DataSource = settings;
            comboBoxCell.Value = value;
            DataGridViewCell cell = new DataGridViewTextBoxCell();
            cell.Value = settingName;
            DataGridViewRow row = new();
            row.Cells.Add(cell);
            row.Cells.Add(comboBoxCell);
            cell.ReadOnly = true;
            comboBoxCell.ReadOnly = readOnly;
            dataGridViewSettings.Rows.Add(row);
        }

        private void ButtonSaveSettings_Click(object sender, EventArgs e)
        {
            List<Control> result = ParentControl.GetSelfAndChildrenRecursive().ToList();
            List<Color> backColors = result.Select(x => x.BackColor).ToList();
            backColors.AddRange(result.Where(x => x is DataGridView).Select(x => (DataGridView)x).Select(x => x.BackgroundColor));
            //TODO add other Controls
            backColors = backColors.Distinct().ToList();

            List<Color> foreColors = result.Select(x => x.ForeColor).ToList();
            //TODO add other Controls
            foreColors = foreColors.Distinct().ToList();

            result.ForEach(x => x.BackColor = Color.AliceBlue);
            result.ForEach(x => x.ForeColor = Color.Red);
            ParentControl.Refresh();
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
        }

        public static Settings Get()
        {
            _instance ??= new Settings();
            return _instance;
        }
    }
}
