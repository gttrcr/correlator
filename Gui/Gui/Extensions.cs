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

        public static void AddRow<T>(this DataGridView dataGridView, IEnumerable<object> columns, bool readOnly) where T : DataGridViewCell, new()
        {
            DataGridViewRow dataGridViewRow = new();
            dataGridViewRow.ReadOnly = true;
            for (int column = 0; column < columns.Count(); column++)
            {
                DataGridViewCell cell = new T();
                cell.Value = columns.ElementAt(column);
                dataGridViewRow.Cells.Add(cell);
                cell.ReadOnly = readOnly;
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
    }
}
