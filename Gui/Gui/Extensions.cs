namespace Gui
{
    public static class Extensions
    {
        public static string Last(this string str, int last, bool addSubstringIndication = false)
        {
            string tmp = addSubstringIndication ? "..." : string.Empty;
            if (str.Length > last)
                tmp += str[^last..];
            else
                tmp = str;

            return tmp;
        }

        public static void AddRow<T>(this DataGridView dataGridView, List<object> columns, bool readOnly) where T : DataGridViewCell, new()
        {
            dataGridView.AddRow<T>(columns, Enumerable.Repeat(readOnly, columns.Count).ToList());
        }

        public static void AddRow<T>(this DataGridView dataGridView, List<object> columns, List<bool> readOnly) where T : DataGridViewCell, new()
        {
            if (columns.Count != readOnly.Count)
                throw new Exception("columns has size " + columns.Count + " while readonly has size " + readOnly.Count);

            DataGridViewRow dataGridViewRow = new();
            dataGridViewRow.ReadOnly = true;
            for (int column = 0; column < columns.Count; column++)
            {
                DataGridViewCell cell = new T();
                cell.Value = columns.ElementAt(column);
                dataGridViewRow.Cells.Add(cell);
                cell.ReadOnly = readOnly[column];
            }

            dataGridView.Rows.Add(dataGridViewRow);
        }

        public static List<Control> GetSelfAndChildrenRecursive(this Control parent)
        {
            List<Control> controls = new();
            foreach (Control child in parent.Controls)
                controls.AddRange(GetSelfAndChildrenRecursive(child));
            controls.Add(parent);

            return controls;
        }

        public static void AddTabPageAndTabControl(this TabControl tabControlMain, ref TabPage tabPage, string tabPageText, ref TabControl tabControl)
        {
            tabPage = new();
            tabPage.Text = tabPageText;
            tabControlMain.Controls.Add(tabPage);

            tabControl = new();
            tabControl.Dock = DockStyle.Fill;
            tabControl.Controls.Clear();
            tabPage.Controls.Add(tabControl);
        }

        public static void RemoveTabPageAndTabControl(this TabControl tabControlMain, string tabPageText)
        {
            int index = tabControlMain.Controls.Cast<Control>().ToList().FindIndex(x => x.Text.Equals(tabPageText));
            if (index > -1)
                tabControlMain.Controls.RemoveAt(index);
        }
    }
}
